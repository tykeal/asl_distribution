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
#ifndef GATEWAYENUMS_H_
#define GATEWAYENUMS_H_

namespace ajn {
namespace gw {

/**
 * Enum to describe the connection status of the App
 */
typedef enum {
    GW_CS_NOT_INITIALIZED =  0,      //!< NOT_INITIALIZED
    GW_CS_IN_PROGRESS = 1,           //!< IN_PROGRESS
    GW_CS_CONNECTED = 2,             //!< CONNECTED
    GW_CS_NOT_CONNECTED = 3,         //!< NOT_CONNECTED
    GW_CS_ERROR = 4,                 //!< ERROR
    GW_CS_MAX_CONNECTION_STATUS = 4  //!< MAX_CONNECTION_STATUS
} ConnectionStatus;

/**
 * Enum to describe the operational status of the App
 */
typedef enum {
    GW_OS_RUNNING =  0,               //!< RUNNING
    GW_OS_STOPPED = 1,                //!< STOPPED
    GW_OS_MAX_OPERATIONAL_STATUS = 1  //!< MAX_OPERATIONAL_STATUS
} OperationalStatus;

/**
 * Enum to describe the install status of the App
 */
typedef enum {
    GW_IS_INSTALLED =  0,            //!< INSTALLED
    GW_IS_INSTALL_IN_PROGRESS = 1,   //!< INSTALL_IN_PROGRESS
    GW_IS_UPGRADE_IN_PROGRESS = 2,   //!< UPGRADE_IN_PROGRESS
    GW_IS_UNINSTALL_IN_PROGRESS = 3, //!< UNINSTALL_IN_PROGRESS
    GW_IS_INSTALL_FAILED = 4,        //!< INSTALL_FAILED
    GW_IS_MAX_INSTALL_STATUS = 4     //!< MAX_INSTALL_STATUS
} InstallStatus;

/**
 * Enum to describe the Acl Status of the Acl
 */
typedef enum {
    GW_AS_INACTIVE =  0,           //!< INACTIVE
    GW_AS_ACTIVE = 1,              //!< ACTIVE
    GW_AS_MAX_ACL_STATUS = 1       //!< MAX_ACL_STATUS
} AclStatus;

/**
 * Enum to describe the response code for trying to restart an App
 */
typedef enum {
    GW_RESTART_APP_RC_SUCCESS =  0,     //!< RESTART_APP_RC_SUCCESS
    GW_RESTART_APP_RC_INVALID = 1       //!< RESTART_APP_INVALID
} RestartAppResponseCode;

/**
 * Enum to describe the response code for trying to create/update an Acl
 */
typedef enum {
    GW_ACL_RC_SUCCESS =  0,             //!< SUCCESS
    GW_ACL_RC_INVALID = 1,              //!< ACL_RC_INVALID
    GW_ACL_RC_REGISTER_ERROR = 2,       //!< GW_ACL_RC_REGISTER_ERROR
    GW_ACL_RC_ACL_NOT_FOUND = 3,        //!< ACL_RC_ACL_NOT_FOUND
    GW_ACL_RC_PERSISTENCE_ERROR = 4,    //!< GW_ACL_RC_PERSISTENCE_ERROR
    GW_ACL_RC_POLICYMANAGER_ERROR = 5,  //!< GW_ACL_RC_POLICYMANAGER_ERROR
    GW_ACL_RC_METADATA_ERROR = 6        //!< GW_ACL_RC_METADATA_ERROR
} AclResponseCode;

} /* namespace gw */
} /* namespace ajn */


#endif /* GATEWAYENUMS_H_ */
