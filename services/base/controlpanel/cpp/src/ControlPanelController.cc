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

#ifdef _WIN32
/* Disable deprecation warnings */
#pragma warning(disable: 4996)
#endif

#include <alljoyn/controlpanel/ControlPanelController.h>
#include <alljoyn/controlpanel/ControlPanelService.h>
#include "ControlPanelConstants.h"
#include <alljoyn/controlpanel/LogModule.h>
#include <alljoyn/AboutObjectDescription.h>
#include <vector>

#include <alljoyn/about/AboutClient.h>

namespace ajn {
namespace services {
using namespace cpsConsts;

ControlPanelController::ControlPanelController()
{
}

ControlPanelController::~ControlPanelController()
{
}

ControlPanelDevice* ControlPanelController::createControllableDevice(qcc::String const& sender,
                                                                     const AboutObjectDescription& objectDescs)
{
    QCC_DbgTrace(("ControlPanelController::createControllableDevice"));
    if (sender.length() == 0) {
        QCC_DbgHLPrintf(("Sender cannot be empty"));
        return NULL;
    }

    ControlPanelDevice* device = 0;
    std::map<qcc::String, ControlPanelDevice*>::iterator iter;
    if ((iter = m_ControllableDevices.find(sender)) != m_ControllableDevices.end()) {
        QCC_DbgPrintf(("ControlPanelDevice for this sender already exists"));
        device = iter->second;
    }

    //AboutClient::ObjectDescriptions::const_iterator it;
    qcc::String ControlPanelPrefix = "/ControlPanel/";
    bool hasControlPanel = false;

    size_t numPaths = objectDescs.GetPaths(NULL, 0);
    const char** paths = new const char*[numPaths];
    numPaths = objectDescs.GetPaths(paths, numPaths);
    QCC_DbgPrintf(("numPaths=%d", numPaths));

    for (size_t i = 0; i < numPaths; i++) {
        QCC_DbgPrintf(("paths[%d]=%s", i, paths[i]));
        qcc::String key = qcc::String(paths[i]);

        if (key.compare(0, ControlPanelPrefix.size(), ControlPanelPrefix) == 0) {
            if (!device) {
                device = getControllableDevice(sender);
            }
            size_t numInterfaces = objectDescs.GetInterfaces(paths[i], NULL, 0);
            const char** interfaces = new const char*[numInterfaces];
            numInterfaces = objectDescs.GetInterfaces(paths[i], interfaces, numInterfaces);
            QCC_DbgPrintf(("numInterfaces=%d", numInterfaces));
            std::vector<qcc::String> vecInterfaces;
            for (size_t j = 0; j < numInterfaces; j++) {
                QCC_DbgPrintf(("interfaces[%d]=%s", j, interfaces[j]));
                vecInterfaces.push_back(qcc::String(interfaces[j]));
            }
            if (device->addControlPanelUnit(key, vecInterfaces)) {
                QCC_DbgPrintf(("Adding ControlPanelUnit for objectPath: %s", key.c_str()));
                hasControlPanel = true;
            }
            delete [] interfaces;
        }
    }

    delete [] paths;

    if (hasControlPanel) {
        QCC_DbgPrintf(("Calling startSession for device %s", sender.c_str()));
        device->startSessionAsync();
    }
    return device;
}

ControlPanelDevice* ControlPanelController::createControllableDevice(qcc::String const& sender,
                                                                     const AnnounceHandler::ObjectDescriptions& objectDescs)
{
    if (sender.length() == 0) {
        QCC_DbgHLPrintf(("Sender cannot be empty"));
        return NULL;
    }

    ControlPanelDevice* device = 0;
    std::map<qcc::String, ControlPanelDevice*>::iterator iter;
    if ((iter = m_ControllableDevices.find(sender)) != m_ControllableDevices.end()) {
        QCC_DbgPrintf(("ControlPanelDevice for this sender already exists"));
        device = iter->second;
    }

    AboutClient::ObjectDescriptions::const_iterator it;
    qcc::String ControlPanelPrefix = "/ControlPanel/";
    bool hasControlPanel = false;

    for (it = objectDescs.begin(); it != objectDescs.end(); ++it) {
        qcc::String key = it->first;

        if (key.compare(0, ControlPanelPrefix.size(), ControlPanelPrefix) == 0) {
            if (!device) {
                device = getControllableDevice(sender);
            }
            if (device->addControlPanelUnit(key, it->second)) {
                QCC_DbgPrintf(("Adding ControlPanelUnit for objectPath: %s", key.c_str()));
                hasControlPanel = true;
            }
        }
    }
    if (hasControlPanel) {
        QCC_DbgPrintf(("Calling startSession for device %s", sender.c_str()));
        device->startSessionAsync();
    }
    return device;
}

ControlPanelDevice* ControlPanelController::getControllableDevice(qcc::String const& sender)
{
    if (sender.length() == 0) {
        QCC_DbgHLPrintf(("Sender cannot be empty"));
        return NULL;
    }

    std::map<qcc::String, ControlPanelDevice*>::iterator iter;
    if ((iter = m_ControllableDevices.find(sender)) != m_ControllableDevices.end()) {
        QCC_DbgPrintf(("ControlPanelDevice for this sender already exists"));
        return iter->second;
    }

    ControlPanelDevice* newDevice = new ControlPanelDevice(sender);
    m_ControllableDevices[sender] = newDevice;
    return newDevice;
}

QStatus ControlPanelController::deleteControllableDevice(qcc::String const& sender)
{
    QCC_DbgTrace(("ControlPanelController::deleteControllableDevice"));
    if (sender.length() == 0) {
        QCC_DbgHLPrintf(("Sender cannot be empty"));
        return ER_BAD_ARG_1;
    }

    std::map<qcc::String, ControlPanelDevice*>::iterator iter;
    if ((iter = m_ControllableDevices.find(sender)) == m_ControllableDevices.end()) {
        QCC_DbgHLPrintf(("Sender does not exist"));
        return ER_BAD_ARG_1;
    }

    ControlPanelDevice* device = iter->second;
    QStatus status = device->shutdownDevice();
    if (status != ER_OK) {
        QCC_LogError(status, ("Could not end Session successfully"));
    }

    m_ControllableDevices.erase(iter);
    delete device;
    return status;
}

QStatus ControlPanelController::deleteAllControllableDevices()
{
    QCC_DbgTrace(("ControlPanelController::deleteAllControllableDevices"));
    QStatus returnStatus = ER_OK;
    std::map<qcc::String, ControlPanelDevice*>::iterator iter;
    std::map<qcc::String, ControlPanelDevice*>::iterator deliter;
    for (iter = m_ControllableDevices.begin(); iter != m_ControllableDevices.end();) {

        ControlPanelDevice* device = iter->second;
        deliter = iter++;
        QStatus status = device->shutdownDevice();
        if (status != ER_OK) {
            QCC_LogError(status, ("Could not shutdown Device successfully"));
            returnStatus = status;
        }

        m_ControllableDevices.erase(deliter);
        delete device;
    }
    return returnStatus;
}

const std::map<qcc::String, ControlPanelDevice*>& ControlPanelController::getControllableDevices() const
{
    return m_ControllableDevices;
}

} /* namespace services */
} /* namespace ajn */
