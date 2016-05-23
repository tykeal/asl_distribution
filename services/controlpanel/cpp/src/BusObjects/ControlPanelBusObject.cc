/******************************************************************************
 * Copyright (c) 2013-2014, AllSeen Alliance. All rights reserved.
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

#include "ControlPanelBusObject.h"
#include "../ControlPanelConstants.h"
#include <alljoyn/controlpanel/ControlPanelService.h>
#include <alljoyn/controlpanel/LogModule.h>

using namespace qcc;
namespace ajn {
namespace services {
using namespace cpsConsts;

#define CONTROLPANEL_INTERFACE_VERSION 1

ControlPanelBusObject::ControlPanelBusObject(BusAttachment* bus, String const& objectPath, QStatus& status) :
    BusObject(objectPath.c_str()), m_Proxy(0), m_ObjectPath(objectPath), m_InterfaceDescription(0)
{
    status = ER_OK;

    String interfaceName = AJ_CONTROLPANEL_INTERFACE;
    m_InterfaceDescription = (InterfaceDescription*) bus->GetInterface(interfaceName.c_str());
    if (!m_InterfaceDescription) {
        do {
            CHECK_AND_BREAK(bus->CreateInterface(interfaceName.c_str(), m_InterfaceDescription));
            CHECK_AND_BREAK(m_InterfaceDescription->AddProperty(AJ_PROPERTY_VERSION.c_str(), AJPARAM_UINT16.c_str(), PROP_ACCESS_READ));
            m_InterfaceDescription->Activate();
        } while (0);
    }
    if (status != ER_OK) {
        QCC_LogError(status, ("Could not create interface"));
        return;
    }

    status = AddInterface(*m_InterfaceDescription);
    if (status != ER_OK) {
        QCC_LogError(status, ("Could not add interface"));
        return;
    }
    QCC_DbgPrintf(("Created ControlPanelBusObject successfully"));
}

ControlPanelBusObject::~ControlPanelBusObject()
{
    if (m_Proxy) {
        delete m_Proxy;
    }
}

QStatus ControlPanelBusObject::Get(const char* interfaceName, const char* propName, MsgArg& val)
{
    QCC_DbgPrintf(("Get property was called - in ControlPanelBusObject class."));

    if (0 == strcmp(AJ_PROPERTY_VERSION.c_str(), propName)) {
        return val.Set(AJPARAM_UINT16.c_str(), CONTROLPANEL_INTERFACE_VERSION);
    }
    return ER_BUS_NO_SUCH_PROPERTY;
}

QStatus ControlPanelBusObject::Set(const char* interfaceName, const char* propName, MsgArg& val)
{
    return ER_ALLJOYN_ACCESS_PERMISSION_ERROR;
}

QStatus ControlPanelBusObject::setRemoteController(BusAttachment* bus, qcc::String const& deviceBusName, SessionId sessionId)
{
    if (m_Proxy && m_Proxy->GetSessionId() == sessionId) {
        QCC_DbgPrintf(("ProxyBusObject already set - ignoring"));
        return ER_OK;
    }

    if (!m_InterfaceDescription) {
        QCC_DbgHLPrintf(("InterfaceDescription is not set. Cannot set RemoteController"));
        return ER_FAIL;
    }

    if (m_Proxy) { // delete existing ProxyBusObject and create new one with correct sessionId
        delete m_Proxy;
    }

    m_Proxy = new ProxyBusObject(*bus, deviceBusName.c_str(), m_ObjectPath.c_str(), sessionId);
    QStatus status = m_Proxy->AddInterface(*m_InterfaceDescription);
    if (status != ER_OK) {
        QCC_LogError(status, ("Could not add Interface to ProxyBusobject"));
    }
    return status;
}

QStatus ControlPanelBusObject::checkVersions()
{
    if (!m_Proxy) {
        QCC_DbgHLPrintf(("Cannot Check Versions. ProxyBusObject is not set."));
        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    }

    MsgArg value;
    QStatus status = m_Proxy->GetProperty(AJ_CONTROLPANEL_INTERFACE.c_str(), AJ_PROPERTY_VERSION.c_str(), value);
    if (status != ER_OK) {
        QCC_LogError(status, ("Call to get Version Property failed"));
        return status;
    }

    uint16_t version = 1;
    status = value.Get(AJPARAM_UINT16.c_str(), &version);
    if (status != ER_OK) {
        QCC_LogError(status, ("Could not unmarshal version property"));
        return status;
    }

    if (CONTROLPANEL_INTERFACE_VERSION < version) {
        QCC_DbgHLPrintf(("The versions of the interface are not compatible"));
        return ER_BUS_INTERFACE_MISMATCH;
    }
    return ER_OK;
}

QStatus ControlPanelBusObject::Introspect(std::vector<IntrospectionNode>& childNodes)
{
    if (!m_Proxy) {
        QCC_DbgHLPrintf(("Cannot Check Versions. ProxyBusObject is not set"));
        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    }

    QStatus status = m_Proxy->IntrospectRemoteObject();
    if (status != ER_OK) {
        QCC_LogError(status, ("Could not introspect RemoteObject"));
        return status;
    }

    size_t numChildren = m_Proxy->GetChildren();
    if (numChildren == 0) {
        return ER_OK;
    }

    ProxyBusObject** proxyBusObjectChildren = new ProxyBusObject *[numChildren];
    numChildren = m_Proxy->GetChildren(proxyBusObjectChildren, numChildren);

    for (size_t i = 0; i < numChildren; i++) {

        String const& objectPath = proxyBusObjectChildren[i]->GetPath();
        QCC_DbgPrintf(("ObjectPath is: %s", objectPath.c_str()));

        status = proxyBusObjectChildren[i]->IntrospectRemoteObject();
        if (status != ER_OK) {
            QCC_LogError(status, ("Could not introspect RemoteObjectChild"));
            delete[] proxyBusObjectChildren;
            return status;
        }

        size_t numInterfaces = proxyBusObjectChildren[i]->GetInterfaces();

        if (numInterfaces == 0) {
            continue;
        }

        const InterfaceDescription** ifaces = new const InterfaceDescription *[numInterfaces];
        numInterfaces = proxyBusObjectChildren[i]->GetInterfaces(ifaces, numInterfaces);
        for (size_t j = 0; j < numInterfaces; j++) {
            QCC_DbgPrintf(("InterfaceName is : %s", ifaces[j]->GetName()));
            if (strcmp(ifaces[j]->GetName(), AJ_CONTAINER_INTERFACE.c_str()) == 0) {
                IntrospectionNode node(objectPath, CONTAINER, false);
                childNodes.push_back(node);
            } else if (strcmp(ifaces[j]->GetName(), AJ_SECURED_CONTAINER_INTERFACE.c_str()) == 0) {
                IntrospectionNode node(objectPath, CONTAINER, true);
                childNodes.push_back(node);
            } else {
                QCC_DbgPrintf(("Ignoring interface - not a container interface"));
            }
        }
        delete[] ifaces;
    }
    delete[] proxyBusObjectChildren;
    return ER_OK;
}

} /* namespace services */
} /* namespace ajn */



