/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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

#include <alljoyn/gateway/GatewayMgmtApp.h>
#include <alljoyn/gateway/GatewayController.h>
#include <alljoyn/gateway/LogModule.h>
#include <alljoyn/Status.h>
#include "Constants.h"
#include <qcc/Log.h>

using namespace ajn::gwc::gwcConsts;

namespace ajn {
namespace gwc {


QStatus GatewayMgmtApp::init(const qcc::String& gwBusName, ajn::services::AboutClient::AboutData const& aboutData)
{
    m_SessionHandler  = this;
    m_Listener = 0;


    return AnnouncedApp::init(gwBusName, aboutData);
}

GatewayMgmtApp::~GatewayMgmtApp()
{

}

void GatewayMgmtApp::emptyVector()
{
    for (size_t indx = 0; indx < m_InstalledApps.size(); indx++) {
        QStatus status = m_InstalledApps[indx]->release();

        if (status != ER_OK) {
            QCC_LogError(status, ("Could not release object"));
        }
        delete m_InstalledApps[indx];
    }

    m_InstalledApps.clear();
}

QStatus GatewayMgmtApp::retrieveConnectorApps(SessionId sessionId, std::vector<ConnectorApp*>& connectorApps)
{
    QStatus status;
    {
        //Release the current vector
        emptyVector();

        BusAttachment* busAttachment = GatewayController::getInstance()->getBusAttachment();

        // create proxy bus object
        ProxyBusObject proxy(*busAttachment, getBusName().c_str(), AJ_OBJECTPATH_PREFIX.c_str(), sessionId, true);

        qcc::String interfaceName = AJ_GATEWAYCONTROLLER_APPMGMT_INTERFACE;
        InterfaceDescription* interfaceDescription = (InterfaceDescription*) busAttachment->GetInterface(interfaceName.c_str());
        if (!interfaceDescription) {

            status = busAttachment->CreateInterface(interfaceName.c_str(), interfaceDescription);
            if (status != ER_OK) {
                QCC_LogError(status, ("Could not create interface"));
                goto end;
            }

            status = interfaceDescription->AddMethod(AJ_METHOD_GETINSTALLEDAPPS.c_str(), NULL, "a(ssos)", "connectorAppsInfoArray");
            if (status != ER_OK) {
                QCC_LogError(status, ("Could not AddMethod"));
                goto end;
            }

            status = interfaceDescription->AddProperty(AJ_PROPERTY_VERSION.c_str(), AJPARAM_UINT16.c_str(), PROP_ACCESS_READ);
            if (status != ER_OK) {
                QCC_LogError(status, ("Could not AddProperty"));
                goto end;
            }

            interfaceDescription->Activate();
        }

        if (!interfaceDescription) { //if for some reason we still don't have interfaceDescription
            status = ER_FAIL;
            QCC_LogError(status, ("Interface description missing"));
            goto end;
        }

        status = proxy.AddInterface(*interfaceDescription);
        if (status != ER_OK) {
            QCC_LogError(status, ("AddInterface failed"));
            goto end;
        }

        Message replyMsg(*busAttachment);
        status = proxy.MethodCall(interfaceName.c_str(), AJ_METHOD_GETINSTALLEDAPPS.c_str(), NULL, 0, replyMsg);
        if (status != ER_OK) {
            QCC_LogError(status, ("Call to getInstalledApps failed"));
            goto end;
        }

        const ajn::MsgArg* returnArgs = NULL;
        size_t numArgs = 0;
        replyMsg->GetArgs(numArgs, returnArgs);
        if (numArgs != 1) {
            QCC_DbgHLPrintf(("Received unexpected amount of returnArgs"));
            status = ER_BUS_UNEXPECTED_SIGNATURE;
            goto end;
        }

        int numApplications;
        MsgArg* tempEntries;
        status = returnArgs[0].Get("a(ssos)", &numApplications, &tempEntries);
        if (status != ER_OK) {
            QCC_LogError(status, ("Call to Get failed"));
            goto end;
        }

        for (int i = 0; i < numApplications; i++) {

            ConnectorApp*connectorApp = new ConnectorApp();
            status = connectorApp->init(getBusName(), &tempEntries[i]);

            if (status != ER_OK) {
                QCC_LogError(status, ("Call to connectorApp->init failed"));

                delete connectorApp;
                connectorApp = NULL;

                goto end;
            }

            m_InstalledApps.push_back(connectorApp);

        }
    }
end:

    connectorApps = m_InstalledApps;
    return status;
}


SessionResult GatewayMgmtApp::joinSession() {
    return joinSession(NULL);
}


SessionResult GatewayMgmtApp::joinSession(SessionListener*listener) {

    m_Listener = listener;

    BusAttachment* busAttachment = GatewayController::getInstance()->getBusAttachment();

    if (!busAttachment) {
        QCC_DbgHLPrintf(("BusAttachment is not set"));
        return { ER_BUS_BUS_NOT_STARTED, -1 };
    }
    busAttachment->EnableConcurrentCallbacks();

    if (m_SessionHandler.getSessionId() != 0) {
        QCC_DbgPrintf(("Session already started"));

        if (listener) {
            QCC_DbgPrintf(("Firing Listener"));

            listener->sessionEstablished(this);
        }
        return { ER_OK, static_cast<int>(m_SessionHandler.getSessionId()) };
    }

    SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES, false, SessionOpts::PROXIMITY_ANY, TRANSPORT_ANY);
    SessionId sessionId = 0;
    ajn::SessionPort port = GATEWAYSERVICE_PORT;
    QStatus status = busAttachment->JoinSession(getBusName().c_str(), port, &m_SessionHandler, sessionId, opts);
    if (status != ER_OK) {
        QCC_LogError(status, ("Unable to JoinSession with %s", getBusName().c_str()));
    }
    m_SessionHandler.JoinSessionCB(status, sessionId, opts, this);
    return { status, static_cast<int>(sessionId) };
}

QStatus GatewayMgmtApp::joinSessionAsync(SessionListener*listener)
{
    m_Listener = listener;

    BusAttachment* busAttachment = GatewayController::getInstance()->getBusAttachment();
    if (!busAttachment) {
        QCC_DbgHLPrintf(("BusAttachment is not set"));
        return ER_BUS_BUS_NOT_STARTED;
    }
    busAttachment->EnableConcurrentCallbacks();

    if (m_SessionHandler.getSessionId() != 0) {
        QCC_DbgPrintf(("Session already started, firing Listener"));

        if (listener) {
            listener->sessionEstablished(this);
        }

        return ER_OK;
    }

    SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES, true, SessionOpts::PROXIMITY_ANY, TRANSPORT_ANY);
    QStatus status = busAttachment->JoinSessionAsync(getBusName().c_str(), (ajn::SessionPort)GATEWAYSERVICE_PORT, &m_SessionHandler,
                                                     opts, &m_SessionHandler, NULL);

    if (status != ER_OK) {
        QCC_LogError(status, ("Unable to JoinSession with %s", getBusName().c_str()));
    }
    return status;


}

QStatus GatewayMgmtApp::leaveSession()
{
    BusAttachment* busAttachment = GatewayController::getInstance()->getBusAttachment();

    if (!busAttachment) {
        QCC_DbgHLPrintf(("BusAttachment is not set"));
        return ER_BUS_BUS_NOT_STARTED;
    }

    SessionId sessionId = m_SessionHandler.getSessionId();
    if (sessionId == 0) {
        QCC_DbgPrintf(("Session not started. Can't end Session"));
        return ER_OK;
    }

    QStatus status = busAttachment->LeaveSession(sessionId);

    if (status != ER_OK) {
        QCC_LogError(status, ("Unable to LeaveSession. Error:%d", status));
    }

    return status;
}

SessionListener* GatewayMgmtApp::getListener() const
{
    return m_Listener;
}


QStatus GatewayMgmtApp::release()
{
    emptyVector();

    // m_Listener is NOT deleted here since it comes from the outside

    return ER_OK;

}
}
}
