/**
 * @file
 * UnixTransport is an implementation of Transport that listens
 * on an AF_UNIX socket.
 */

/******************************************************************************
 * Copyright AllSeen Alliance. All rights reserved.
 *
 *    Contributed by Qualcomm Connected Experiences, Inc.,
 *    with authorization from the AllSeen Alliance, Inc.
 *    
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *    
 *        http://www.apache.org/licenses/LICENSE-2.0
 *    
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 *    
 *    Pursuant to Section 1 of the License, the work of authorship constituting
 *    a Work and any Contribution incorporated in the Work shall mean only that
 *    Contributor's code submissions authored by that Contributor.  Any rights
 *    granted under the License are conditioned upon acceptance of these
 *    clarifications.
 ******************************************************************************/

#include <errno.h>

#include <qcc/platform.h>
#include <qcc/Socket.h>
#include <qcc/SocketStream.h>
#include <qcc/String.h>
#include <qcc/StringUtil.h>
#include <qcc/Util.h>

#include <alljoyn/BusAttachment.h>

#include "BusInternal.h"
#include "ConfigDB.h"
#include "RemoteEndpoint.h"
#include "Router.h"
#include "DaemonTransport.h"
#ifdef ENABLE_POLICYDB
#include "PolicyDB.h"
#endif

#define QCC_MODULE "ALLJOYN"

using namespace std;
using namespace qcc;

namespace ajn {

const char* DaemonTransport::TransportName = "unix";

class _DaemonEndpoint;
typedef qcc::ManagedObj<_DaemonEndpoint> DaemonEndpoint;

/*
 * An endpoint class to handle the details of authenticating a connection in
 * the Unix Domain Sockets way.
 */
class _DaemonEndpoint : public _RemoteEndpoint {

  public:

    _DaemonEndpoint(DaemonTransport* transport, BusAttachment& bus, bool incoming, const qcc::String connectSpec, SocketFd sock) :
        _RemoteEndpoint(bus, incoming, connectSpec, &stream, DaemonTransport::TransportName),
        m_transport(transport),
        userId(-1),
        groupId(-1),
        processId(-1),
        stream(sock)
    {
    }

    ~_DaemonEndpoint() { }

    /**
     * Set the user id of the endpoint.
     *
     * @param   userId      User ID number.
     */
    void SetUserId(uint32_t userId) { this->userId = userId; }

    /**
     * Set the group id of the endpoint.
     *
     * @param   groupId     Group ID number.
     */
    void SetGroupId(uint32_t groupId) { this->groupId = groupId; }

    /**
     * Set the process id of the endpoint.
     *
     * @param   processId   Process ID number.
     */
    void SetProcessId(uint32_t processId) { this->processId = processId; }

    /**
     * Return the user id of the endpoint.
     *
     * @return  User ID number.
     */
    uint32_t GetUserId() const { return userId; }

    /**
     * Return the group id of the endpoint.
     *
     * @return  Group ID number.
     */
    uint32_t GetGroupId() const { return groupId; }

    /**
     * Return the process id of the endpoint.
     *
     * @return  Process ID number.
     */
    uint32_t GetProcessId() const { return processId; }

    /**
     * Indicates if the endpoint supports reporting UNIX style user, group, and process IDs.
     *
     * @return  'true' if UNIX IDs supported, 'false' if not supported.
     */
    bool SupportsUnixIDs() const { return true; }

    QStatus SetIdleTimeouts(uint32_t& reqIdleTimeout, uint32_t& reqProbeTimeout)
    {
        uint32_t maxIdleProbes = m_transport->m_numHbeatProbes;

        /* If reqProbeTimeout == 0, Make no change to Probe timeout. */
        if (reqProbeTimeout == 0) {
            reqProbeTimeout = _RemoteEndpoint::GetProbeTimeout();
        } else if (reqProbeTimeout > m_transport->m_maxHbeatProbeTimeout) {
            /* Max allowed Probe timeout is m_maxHbeatProbeTimeout */
            reqProbeTimeout = m_transport->m_maxHbeatProbeTimeout;
        }

        /* If reqIdleTimeout == 0, Make no change to Idle timeout. */
        if (reqIdleTimeout == 0) {
            reqIdleTimeout = _RemoteEndpoint::GetIdleTimeout();
        }

        /* Requested link timeout must be >= m_minHbeatIdleTimeout */
        if (reqIdleTimeout < m_transport->m_minHbeatIdleTimeout) {
            reqIdleTimeout = m_transport->m_minHbeatIdleTimeout;
        }

        /* Requested link timeout must be <= m_maxHbeatIdleTimeout */
        if (reqIdleTimeout > m_transport->m_maxHbeatIdleTimeout) {
            reqIdleTimeout = m_transport->m_maxHbeatIdleTimeout;
        }
        return _RemoteEndpoint::SetIdleTimeouts(reqIdleTimeout, reqProbeTimeout, maxIdleProbes);
    }

  private:
    DaemonTransport* m_transport;        /**< The DaemonTransport holding the connection */
    uint32_t userId;
    uint32_t groupId;
    uint32_t processId;
    SocketStream stream;
};

static const int CRED_TIMEOUT = 5000;  /**< Times out credentials exchange to avoid denial of service attack */

static QStatus GetSocketCreds(SocketFd sockFd, uid_t* uid, gid_t* gid, pid_t* pid)
{
    QStatus status = ER_OK;
#if defined(QCC_OS_DARWIN)
    *pid = 0;
    int ret = getpeereid(sockFd, uid, gid);
    if (ret == -1) {
        status = ER_OS_ERROR;
        qcc::Close(sockFd);
    }
#else
    int enableCred = 1;
    int ret = setsockopt(sockFd, SOL_SOCKET, SO_PASSCRED, &enableCred, sizeof(enableCred));
    if (ret == -1) {
        status = ER_OS_ERROR;
        qcc::Close(sockFd);
    }

    if (status == ER_OK) {
        qcc::String authName;
        ssize_t ret;
        char nulbuf = 255;
        struct cmsghdr* cmsg;
        struct iovec iov[] = { { &nulbuf, sizeof(nulbuf) } };
        struct msghdr msg;
        char cbuf[CMSG_SPACE(sizeof(struct ucred))];
        msg.msg_name = NULL;
        msg.msg_namelen = 0;
        msg.msg_iov = iov;
        msg.msg_iovlen = ArraySize(iov);
        msg.msg_flags = 0;
        msg.msg_control = cbuf;
        msg.msg_controllen = CMSG_LEN(sizeof(struct ucred));

        while (true) {
            ret = recvmsg(sockFd, &msg, 0);
            if (ret == -1) {
                if (errno == EWOULDBLOCK) {
                    qcc::Event event(sockFd, qcc::Event::IO_READ);
                    status = Event::Wait(event, CRED_TIMEOUT);
                    if (status != ER_OK) {
                        QCC_LogError(status, ("Credentials exhange timeout"));
                        break;
                    }
                } else {
                    break;
                }
            } else {
                break;
            }
        }

        if ((ret != 1) && (nulbuf != 0)) {
            qcc::Close(sockFd);
            status = ER_READ_ERROR;
        }

        if (status == ER_OK) {
            for (cmsg = CMSG_FIRSTHDR(&msg); cmsg != NULL; cmsg = CMSG_NXTHDR(&msg, cmsg)) {
                if ((cmsg->cmsg_level == SOL_SOCKET) && (cmsg->cmsg_type == SCM_CREDENTIALS)) {
                    struct ucred* cred = reinterpret_cast<struct ucred*>(CMSG_DATA(cmsg));
                    *uid = cred->uid;
                    *gid = cred->gid;
                    *pid = cred->pid;
                    QCC_DbgHLPrintf(("Received UID: %u  GID: %u  PID %u", cred->uid, cred->gid, cred->pid));
                }
            }
        }
    }
#endif

    return status;
}

void* DaemonTransport::Run(void* arg)
{
    SocketFd listenFd = (SocketFd)(ptrdiff_t)arg;
    QStatus status = ER_OK;

    Event listenEvent(listenFd, Event::IO_READ);

    while (!IsStopping()) {
        status = Event::Wait(listenEvent);
        if (status != ER_OK) {
            if (status != ER_STOPPING_THREAD) {
                QCC_LogError(status, ("Event::Wait failed"));
            }
            break;
        }
        SocketFd newSock;

        status = Accept(listenFd, newSock);

        uid_t uid = -1;  // Initialize to suppress compiler warnings.
        gid_t gid = -1;
        pid_t pid = -1;

        if (status == ER_OK) {
            status = GetSocketCreds(newSock, &uid, &gid, &pid);
        }

#ifdef ENABLE_POLICYDB
        PolicyDB policyDB = ConfigDB::GetConfigDB()->GetPolicyDB();
        if (status == ER_OK && !policyDB->OKToConnect(uid, gid)) {
            Close(newSock);
            status = ER_BUS_POLICY_VIOLATION;
        }
#endif

        if (status == ER_OK) {
            qcc::String authName;
            qcc::String redirection;
            static const bool truthiness = true;
            DaemonTransport* trans = this;
            DaemonEndpoint conn = DaemonEndpoint(trans, bus, truthiness, DaemonTransport::TransportName, newSock);

            conn->SetUserId(uid);
            conn->SetGroupId(gid);
            conn->SetProcessId(pid);

            /* Initialized the features for this endpoint */
            conn->GetFeatures().isBusToBus = false;
            conn->GetFeatures().allowRemote = false;
            conn->GetFeatures().handlePassing = true;

            endpointListLock.Lock(MUTEX_CONTEXT);
            endpointList.push_back(RemoteEndpoint::cast(conn));
            endpointListLock.Unlock(MUTEX_CONTEXT);
            status = conn->Establish("EXTERNAL", authName, redirection);
            if (status == ER_OK) {
                conn->SetListener(this);
                status = conn->Start(m_defaultHbeatIdleTimeout, m_defaultHbeatProbeTimeout, m_numHbeatProbes, m_maxHbeatProbeTimeout);
            }
            if (status != ER_OK) {
                QCC_LogError(status, ("Error starting RemoteEndpoint"));
                endpointListLock.Lock(MUTEX_CONTEXT);
                list<RemoteEndpoint>::iterator ei = find(endpointList.begin(), endpointList.end(), RemoteEndpoint::cast(conn));
                if (ei != endpointList.end()) {
                    endpointList.erase(ei);
                }
                endpointListLock.Unlock(MUTEX_CONTEXT);
            }
        } else if (ER_WOULDBLOCK == status || ER_READ_ERROR == status) {
            status = ER_OK;
        }

        if (status != ER_OK) {
            QCC_LogError(status, ("Error accepting new connection. Ignoring..."));
        }

    }

    qcc::Close(listenFd);

    QCC_DbgPrintf(("DaemonTransport::Run is exiting status=%s\n", QCC_StatusText(status)));
    return (void*) status;
}

QStatus DaemonTransport::NormalizeTransportSpec(const char* inSpec, qcc::String& outSpec, map<qcc::String, qcc::String>& argMap) const
{
    QStatus status = ParseArguments(DaemonTransport::TransportName, inSpec, argMap);
    qcc::String path = Trim(argMap["path"]);
    qcc::String abstract = Trim(argMap["abstract"]);
    if (status == ER_OK) {
        outSpec = "unix:";
        if (!path.empty()) {
            outSpec.append("path=");
            outSpec.append(path);
            argMap["_spec"] = path;
        } else if (!abstract.empty()) {
            outSpec.append("abstract=");
            outSpec.append(abstract);
            argMap["_spec"] = qcc::String("@") + abstract;
        } else {
            status = ER_BUS_BAD_TRANSPORT_ARGS;
        }
    }

    return status;
}

static QStatus ListenFd(map<qcc::String, qcc::String>& serverArgs, SocketFd& listenFd)
{
    QStatus status = Socket(QCC_AF_UNIX, QCC_SOCK_STREAM, listenFd);
    if (status != ER_OK) {
        QCC_LogError(status, ("DaemonTransport::ListenFd(): Socket() failed"));
        return status;
    }

    /* Calculate bindAddr */
    qcc::String bindAddr;
    if (status == ER_OK) {
        if (!serverArgs["path"].empty()) {
            bindAddr = serverArgs["path"];
        } else if (!serverArgs["abstract"].empty()) {
            bindAddr = qcc::String("@") + serverArgs["abstract"];
        } else {
            status = ER_BUS_BAD_TRANSPORT_ARGS;
            QCC_LogError(status, ("DaemonTransport::ListenFd(): Invalid listen spec for unix transport"));
            return status;
        }
    }

    /*
     * Bind the socket to the listen address and start listening for incoming
     * connections on it.
     */
    status = Bind(listenFd, bindAddr.c_str());
    if (status != ER_OK) {
        QCC_LogError(status, ("DaemonTransport::ListenFd(): Bind() failed"));
    } else {
        status = qcc::Listen(listenFd, 0);
        if (status == ER_OK) {
            QCC_DbgPrintf(("DaemonTransport::ListenFd(): Listening on %s", bindAddr.c_str()));
        } else {
            QCC_LogError(status, ("DaemonTransport::ListenFd(): Listen failed"));
        }
    }
    return status;
}

QStatus DaemonTransport::StartListen(const char* listenSpec)
{

    if (stopping == true) {
        return ER_BUS_TRANSPORT_NOT_STARTED;
    }
    if (IsRunning()) {
        return ER_BUS_ALREADY_LISTENING;
    }
    /* Normalize the listen spec. */
    QStatus status;
    qcc::String normSpec;
    map<qcc::String, qcc::String> serverArgs;
    status = NormalizeTransportSpec(listenSpec, normSpec, serverArgs);
    if (status != ER_OK) {
        QCC_LogError(status, ("DaemonTransport::StartListen(): Invalid Unix listen spec \"%s\"", listenSpec));
        return status;
    }
    SocketFd listenFd = qcc::INVALID_SOCKET_FD;
    status = ListenFd(serverArgs, listenFd);
    if (status == ER_OK) {
        status = Thread::Start((void*)(intptr_t)listenFd);
    }
    if ((listenFd != qcc::INVALID_SOCKET_FD) && (status != ER_OK)) {
        qcc::Close(listenFd);
    }
    return status;
}

QStatus DaemonTransport::StopListen(const char* listenSpec)
{
    QCC_UNUSED(listenSpec);
    return Thread::Stop();
}

} // namespace ajn
