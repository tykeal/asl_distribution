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

#include "ContainerBusObject.h"
#include "../ControlPanelConstants.h"
#include <alljoyn/controlpanel/ControlPanelService.h>
#include <alljoyn/controlpanel/LogModule.h>

namespace ajn {
namespace services {
using namespace qcc;
using namespace cpsConsts;

ContainerBusObject::ContainerBusObject(BusAttachment* bus, String const& objectPath, uint16_t langIndx,
                                       QStatus& status, Widget* widget) :
    WidgetBusObject(objectPath, langIndx, status, widget)
{
    if (status != ER_OK) {
        QCC_LogError(status, ("Could not create the BusObject"));
        return;
    }

    String interfaceName = widget->getIsSecured() ? AJ_SECURED_CONTAINER_INTERFACE : AJ_CONTAINER_INTERFACE;
    m_InterfaceDescription = (InterfaceDescription*) bus->GetInterface(interfaceName.c_str());
    if (!m_InterfaceDescription) {
        do {
            CHECK_AND_BREAK(bus->CreateInterface(interfaceName.c_str(), m_InterfaceDescription, widget->getIsSecured()));
            CHECK_AND_BREAK(addDefaultInterfaceVariables(m_InterfaceDescription));
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

    //Get the signal methods for future use
    m_SignalPropertyChanged = m_InterfaceDescription->GetMember(AJ_SIGNAL_PROPERTIES_CHANGED.c_str());
    if (widget->getControlPanelMode() == CONTROLLER_MODE) {
        status = addSignalHandler(bus);
    }

    QCC_DbgPrintf(("Created ContainerBusObject successfully"));
}

ContainerBusObject::~ContainerBusObject() {
}

QStatus ContainerBusObject::Introspect(std::vector<IntrospectionNode>& childNodes)
{
    if (!m_Proxy) {
        QCC_LogError(ER_BUS_PROPERTY_VALUE_NOT_SET, ("Cannot Check Versions. ProxyBusObject is not set"));
        return ER_BUS_PROPERTY_VALUE_NOT_SET;
    }

    QStatus status = m_Proxy->IntrospectRemoteObject();
    if (status != ER_OK) {
        QCC_LogError(status, ("Could not introspect RemoteObject"));
        return status;
    }

    size_t numChildren = m_Proxy->GetChildren();
    if (numChildren == 0) {
        QCC_LogError(ER_FAIL, ("Container does not have children"));
        return ER_FAIL;
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
            } else if (strcmp(ifaces[j]->GetName(), AJ_PROPERTY_INTERFACE.c_str()) == 0) {
                IntrospectionNode node(objectPath, PROPERTY, false);
                childNodes.push_back(node);
            } else if (strcmp(ifaces[j]->GetName(), AJ_SECURED_PROPERTY_INTERFACE.c_str()) == 0) {
                IntrospectionNode node(objectPath, PROPERTY, true);
                childNodes.push_back(node);
            } else if (strcmp(ifaces[j]->GetName(), AJ_LABEL_INTERFACE.c_str()) == 0) {
                IntrospectionNode node(objectPath, LABEL, false);
                childNodes.push_back(node);
            } else if (strcmp(ifaces[j]->GetName(), AJ_ACTION_INTERFACE.c_str()) == 0) {
                if (proxyBusObjectChildren[i]->GetChildren()) {
                    IntrospectionNode node(objectPath, ACTION_WITH_DIALOG, false);
                    childNodes.push_back(node);
                } else {
                    IntrospectionNode node(objectPath, ACTION, false);
                    childNodes.push_back(node);
                }
            } else if (strcmp(ifaces[j]->GetName(), AJ_SECURED_ACTION_INTERFACE.c_str()) == 0) {
                if (proxyBusObjectChildren[i]->GetChildren()) {
                    IntrospectionNode node(objectPath, ACTION_WITH_DIALOG, true);
                    childNodes.push_back(node);
                } else {
                    IntrospectionNode node(objectPath, ACTION, true);
                    childNodes.push_back(node);
                }
            } else {
                QCC_DbgPrintf(("Ignoring interfaceName: %s", ifaces[j]->GetName()));
            }
        }
        delete[] ifaces;
    }
    delete[] proxyBusObjectChildren;
    return ER_OK;
}

} /* namespace services */
} /* namespace ajn */



