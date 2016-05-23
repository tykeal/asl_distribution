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

#include <alljoyn/gateway/GatewayConnectorApp.h>
#include <alljoyn/gateway/GatewayConnectorAppManager.h>
#include <alljoyn/gateway/GatewayMgmt.h>
#include <alljoyn/gateway/GatewayRouterPolicyManager.h>
#include "busObjects/AppMgmtBusObject.h"
#include "GatewayConstants.h"
#include <dirent.h>

namespace ajn {
namespace gw {
using namespace qcc;
using namespace gwConsts;

GatewayConnectorAppManager::GatewayConnectorAppManager() : m_AppMgmtBusObject(NULL)
{
}

GatewayConnectorAppManager::~GatewayConnectorAppManager()
{
}

std::map<String, GatewayConnectorApp*> GatewayConnectorAppManager::getConnectorApps() const
{
    return m_ConnectorApps;
}

QStatus GatewayConnectorAppManager::init(BusAttachment* bus)
{
    QStatus status = ER_OK;

    if (!bus || !bus->IsStarted() || !bus->IsConnected()) {
        status = ER_BAD_ARG_1;
        QCC_LogError(status, ("Could not accept this BusAttachment, busAttachment not started or not connected"));
        return status;
    }

    if (m_AppMgmtBusObject) {
        QCC_DbgPrintf(("Objects already registered. Ignoring request"));
        return ER_OK;
    }

    m_AppMgmtBusObject = new AppMgmtBusObject(bus, this, &status);
    if (status != ER_OK) {
        QCC_LogError(status, ("Could not create GatewayConnectorAppMgmt BusObject"));
        return status;
    }

    status = bus->RegisterBusObject(*m_AppMgmtBusObject);
    if (status != ER_OK) {
        QCC_LogError(status, ("Could not register GatewayConnectorAppMgmt BusObject"));
        return status;
    }

    status = loadConnectorApps();
    if (status != ER_OK) {
        QCC_LogError(status, ("Could not load Installed Apps"));
        return status;
    }

    std::map<String, GatewayConnectorApp*>::iterator it;
    for (it = m_ConnectorApps.begin(); it != m_ConnectorApps.end(); it++) {
        status = it->second->init(bus);
        if (status != ER_OK) {
            QCC_LogError(status, ("Could not register app"));
            return status;
        }
    }

    return status;
}

QStatus GatewayConnectorAppManager::shutdown(BusAttachment* bus)
{
    QStatus returnStatus = ER_OK;

    if (!bus || !bus->IsStarted() || !bus->IsConnected()) {
        returnStatus = ER_BAD_ARG_1;
        QCC_LogError(returnStatus, ("Could not acccept this BusAttachment, busAttachment not started or not connected"));
        return returnStatus;
    }

    if (!m_AppMgmtBusObject) {
        QCC_DbgPrintf(("Objects not registered. Ignoring request"));
        return ER_OK;
    }

    GatewayRouterPolicyManager* policyManager = GatewayMgmt::getInstance()->getRouterPolicyManager();
    if (!policyManager) {
        QCC_DbgHLPrintf(("PolicyManager not defined"));
        return ER_FAIL;
    }

    bus->UnregisterBusObject(*m_AppMgmtBusObject);
    delete m_AppMgmtBusObject;
    m_AppMgmtBusObject = NULL;

    std::map<String, GatewayConnectorApp*>::iterator it;
    std::vector<pthread_t> shutdownThreads;

    for (it = m_ConnectorApps.begin(); it != m_ConnectorApps.end(); it++) {
        pthread_t thread;
        bool success = it->second->shutdownConnectorApp(&thread);
        if (success) {
            shutdownThreads.push_back(thread);
        }
    }

    for (size_t i = 0; i < shutdownThreads.size(); i++) {
        pthread_join(shutdownThreads[i], NULL);
    }

    for (it = m_ConnectorApps.begin(); it != m_ConnectorApps.end();) {
        GatewayConnectorApp* app = it->second;

        QStatus status = app->shutdown(bus);
        if (status != ER_OK) {
            QCC_LogError(status, ("Could not unregister app"));
            returnStatus = status;
        }
        m_ConnectorApps.erase(it++);

        bool success = policyManager->removeConnectorAppRules(app->getConnectorId());
        if (!success) {
            QCC_DbgHLPrintf(("Updating the Policies failed"));
            returnStatus =  ER_FAIL;
        }
        delete app;
    }

    return returnStatus;
}

QStatus GatewayConnectorAppManager::loadConnectorApps()
{
    DIR* dir;
    struct dirent* entry;
    if ((dir = opendir(GATEWAY_APPS_DIRECTORY.c_str())) == NULL) {
        QCC_DbgHLPrintf(("Could not open gatewayApps directory"));
        return ER_FAIL;
    }

    while ((entry = readdir(dir)) != NULL) {

        qcc::String connectorId(entry->d_name);
        if (connectorId.compare(".") == 0 || connectorId.compare("..") == 0) {
            continue;
        }

        if (entry->d_type != DT_DIR) {   // this is not a directory - does not represents an app
            QCC_DbgTrace(("Ignoring non directory %s", entry->d_name));
            continue;
        }

        GatewayConnectorAppManifest manifest;
        qcc::String manifestFileName = GATEWAY_APPS_DIRECTORY + "/" + connectorId + "/Manifest.xml";
        QStatus status = manifest.parseManifestFile(manifestFileName);
        if (status != ER_OK) {
            QCC_LogError(status, ("Could not parse the manifest file for app: %s", connectorId.c_str()));
            continue;
        }

        GatewayConnectorApp* gatewayApp = new GatewayConnectorApp(connectorId, manifest);
        m_ConnectorApps.insert(std::pair<qcc::String, GatewayConnectorApp*>(connectorId, gatewayApp));
    }
    closedir(dir);

    return ER_OK;
}

void GatewayConnectorAppManager::sigChildReceived(pid_t pid)
{
    std::map<String, GatewayConnectorApp*>::iterator it;
    for (it = m_ConnectorApps.begin(); it != m_ConnectorApps.end(); it++) {
        if (it->second->getProcessId() == pid) {
            it->second->sigChildReceived();
            break;
        }
    }
}

} /* namespace gw */
} /* namespace ajn */


