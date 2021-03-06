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

#include "alljoyn/gateway/GatewayConnector.h"
#define GW_CONNECTOR_IFC_NAME "org.alljoyn.gwagent.connector.App"
#define GW_CONNECTOR_SIG_MATCH "type='signal',interface='org.alljoyn.gwagent.connector.App'"
#define GW_MGMNT_APP_WKN "org.alljoyn.GWAgent.GMApp"

using namespace ajn::gw;
using namespace ajn;

GatewayConnector::GatewayConnector(BusAttachment* bus, qcc::String const& appName) :
    m_Bus(bus), m_ObjectPath("/gw/"),
    m_WellKnownName("org.alljoyn.GWAgent.Connector."),
    m_RemoteAppAccess(NULL)
{
    m_ObjectPath.append(appName);
    m_WellKnownName.append(appName);
}

GatewayConnector::~GatewayConnector()
{

}

QStatus GatewayConnector::init()
{
    QStatus status = ER_OK;

    const InterfaceDescription* ifc = initInterface(status);
    if (ER_OK != status) {
        return status;
    }

    status =  m_Bus->RegisterSignalHandler(this, static_cast<MessageReceiver::SignalHandler>(
                                               &GatewayConnector::mergedAclUpdatedSignalHandler), ifc->GetMember("MergedAclUpdated"), NULL);
    if (ER_OK != status) {
        return status;
    }

    status =  m_Bus->RegisterSignalHandler(this, static_cast<MessageReceiver::SignalHandler>(
                                               &GatewayConnector::shutdownSignalHandler), ifc->GetMember("ShutdownApp"), NULL);
    if (ER_OK != status) {
        return status;
    }

    status = m_Bus->AddMatch(GW_CONNECTOR_SIG_MATCH);
    if (ER_OK != status) {
        return status;
    }

    m_RemoteAppAccess = new ProxyBusObject(*m_Bus, GW_MGMNT_APP_WKN, m_ObjectPath.c_str(), 0);
    status = m_RemoteAppAccess->AddInterface(*ifc);
    if (ER_OK != status) {
        return status;
    }

    status = m_Bus->RequestName(m_WellKnownName.c_str(), DBUS_NAME_FLAG_DO_NOT_QUEUE);

    return status;
}

const InterfaceDescription* GatewayConnector::initInterface(QStatus& status)
{
    status = ER_OK;

    const InterfaceDescription* ret = m_Bus->GetInterface(GW_CONNECTOR_IFC_NAME);
    if (ret) {
        return ret;
    }

    InterfaceDescription* ifc;
    status = m_Bus->CreateInterface(GW_CONNECTOR_IFC_NAME, ifc);
    if (ER_OK != status) {
        return NULL;
    }

    status = ifc->AddMethod("GetMergedAcl", NULL,  "a(obas)a(saya(obas))", "exposedServices,remotedApps");
    if (ER_OK != status) {
        return NULL;
    }

    status = ifc->AddMethod("UpdateConnectionStatus", "q", NULL, "connectionStatus", MEMBER_ANNOTATE_NO_REPLY);
    if (ER_OK != status) {
        return NULL;
    }

    status = ifc->AddSignal("MergedAclUpdated", NULL, NULL);
    if (ER_OK != status) {
        return NULL;
    }

    status = ifc->AddSignal("ShutdownApp", NULL, NULL);
    if (ER_OK != status) {
        return NULL;
    }

    ifc->Activate();

    return m_Bus->GetInterface(GW_CONNECTOR_IFC_NAME);
}

QStatus GatewayConnector::getMergedAcl(GatewayMergedAcl* response)
{
    QStatus status = ER_OK;

    Message reply(*m_Bus);
    status = m_RemoteAppAccess->MethodCall(GW_CONNECTOR_IFC_NAME, "GetMergedAcl", NULL, 0, reply);
    if (ER_OK != status) {
        return status;
    }

    status = response->unmarshal(reply);

    return status;
}

QStatus GatewayConnector::updateConnectionStatus(ConnectionStatus connStatus)
{
    MsgArg input[1];
    input[0].Set("q", connStatus);
    return m_RemoteAppAccess->MethodCall(GW_CONNECTOR_IFC_NAME, "UpdateConnectionStatus", input, 1);
}

void GatewayConnector::mergedAclUpdatedSignalHandler(const InterfaceDescription::Member* member, const char* sourcePath, Message& msg)
{
    mergedAclUpdated();
}

void GatewayConnector::shutdownSignalHandler(const InterfaceDescription::Member* member, const char* sourcePath, Message& msg)
{
    shutdown();
}

QStatus GatewayConnector::getMergedAclAsync(GatewayMergedAcl* response)
{
    Message reply(*m_Bus);
    return m_RemoteAppAccess->MethodCallAsync(GW_CONNECTOR_IFC_NAME, "GetMergedAcl", this,
                                              static_cast<MessageReceiver::ReplyHandler>(&GatewayConnector::getMergedAclReplyHandler), NULL, 0, response);

}

void GatewayConnector::getMergedAclReplyHandler(Message& msg, void* mergedAcl) {
    GatewayMergedAcl* response = static_cast<GatewayMergedAcl*>(mergedAcl);
    QStatus status = response->unmarshal(msg);
    receiveGetMergedAclAsync(status, response);
}
