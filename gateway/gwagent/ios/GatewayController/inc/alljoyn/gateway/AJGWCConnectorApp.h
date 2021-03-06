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

#import <Foundation/Foundation.h>
#import "alljoyn/Status.h"
#import "alljoyn/gateway/ConnectorApp.h"
#import "AJNSessionOptions.h"
#import "AJGWCConnectorCapabilities.h"
#import "AJGWCAclRules.h"
#import "AJGWCConnectorAppStatus.h"
#import "AJGWCEnums.h"
#import "AJGWCAclWriteResponse.h"
#import "AJGWCConnectorAppStatusSignalHandler.h"

@interface AJGWCConnectorApp : NSObject

/**
 * Constructor
 * @param handle A handle to a cpp ConnectorApp object
 */
- (id)initWithHandle:(ajn::gwc::ConnectorApp *) handle;

/**
 * Constructor
 * @param gwBusName The name of the gateway {@link AJNBusAttachment} the application is installed on
 * @param appObjPath The object path to reach the third party application on the gateway
 */
//- (id)initWithGwBusName:(NSString*) gwBusName appObjPath:(NSString*) appObjPath;

/**
 * Constructor
 * @param appInfo
 */
//- (id)initWithGwBusName:(NSString*) gwBusName appInfo:(AJNMessageArgument*) appInfo;

/**
 * @return gwBusName the {@link AJGWCConnectorApp} is installed on
 */
- (NSString*)gwBusName;

/**
 * @return The id of the {@link AJGWCConnectorApp}
 */
- (NSString*)appId;

/**
 * @return The name of the {@link AJGWCConnectorApp}.
 */
- (NSString*)friendlyName;

/**
 * @return The object path to reach the application on the gateway
 */
- (NSString*)objectPath;

/**
 * @return The application version
 */
- (NSString*)appVersion;

/**
 * Retrieves the Manifest file of the application.
 * @param sessionId The id of the session established with the gateway
 * @param xml representation of the Manifest file in XML format.
 * @return {@link QStatus}
 */
- (QStatus)retrieveManifestFileUsingSessionId:(AJNSessionId) sessionId fileContent:(NSString **)xml;

/**
 * Retrieves the Manifest rules of the application
 * @param sessionId The id of the session established with the gateway
 * @param connectorCapabilities {@link AJGWCConnectorCapabilities}
 * @return {@link QStatus}
 */
- (QStatus)retrieveConnectorCapabilitiesUsingSessionId:(AJNSessionId) sessionId connectorCapabilities:(AJGWCConnectorCapabilities**)connectorCapabilities;

/**
 * Retrieves the configurable rules of the application
 * @param sessionId The id of the session established with the gateway
 * @param rules {@link AJGWCAclRules}
 * @param announcements Array of {@link AJGWCAnnouncementData} objects
 * @return {@link QStatus}
 */
- (QStatus)retrieveApplicableConnectorCapabilitiesUsingSessionId:(AJNSessionId) sessionId rules:(AJGWCAclRules**)rules announcements:(NSArray*) announcements;

/**
 * Retrieves the state of the application
 * @param sessionId The id of the session established with the gateway
 * @param connectorAppStatus {@link ConnectorAppStatus}
 * @return {@link QStatus}
 */
- (QStatus)retrieveStatusUsingSessionId:(AJNSessionId) sessionId status:(AJGWCConnectorAppStatus**)connectorAppStatus;

/**
 * Restarts the application
 * @param sessionId The id of the session established with the gateway
 * @param restartStatus {@link AJGWCRestartStatus}
 * @return {@link QStatus}
 */
- (QStatus)restartUsingSessionId:(AJNSessionId) sessionId status:(AJGWCRestartStatus&) restartStatus;

/**
 * Set an {@link AJGWCConnectorAppStatusSignalHandler} to receive application
 * related events. In order to receive the events, in addition to calling this method,
 * a session should be successfully established with the gateway hosting the application.
 * Use {@link AJGWCConnectorApp#unsetStatusSignalHandler()} to stop receiving the events.
 * @param handler Signal handler
 * @return {@link QStatus}
 */
- (QStatus)setStatusSignalHandler:(id<AJGWCConnectorAppStatusSignalHandler>) handler;

/**
 * Stop receiving Service Provider Application related signals
 */
- (void)unsetStatusSignalHandler;

/**
 * Sends request to create {@link AJGWCAcl} object with the received name and
 * the {@link AJGWCAclRules}. The {@link AJGWCAclRules} are validated against the {@link AJGWCConnectorCapabilities}.
 * Only valid rules will be sent for the ACL creation. The invalid rules could be received from the
 * returned {@link AJGWCAclWriteResponse} object.
 * @param sessionId The id of the session established with the gateway
 * @param name The ACL name
 * @param aclRules The ACL access rules
 * @param aclStatus {@link AJGWCAclWriteResponse}
 * @return {@link QStatus}
 */
- (QStatus)createAclUsingSessionId:(AJNSessionId) sessionId name:(NSString*) name aclRules:(AJGWCAclRules*) aclRules aclStatus:(AJGWCAclWriteResponse**)aclStatus;

/**
 * Retrieves a list of the Access Control Lists installed on the application
 * @param sessionId The id of the session established with the gateway
 * @param aclListArray Array of the {@link AJGWCAcl}
 * @return {@link QStatus}
 */
- (QStatus)retrieveAclsUsingSessionId:(AJNSessionId) sessionId acls:(NSMutableArray *)aclListArray;

/**
 * Delete the Access Control List of this application
 * @param sessionId The id of the session established with the gateway
 * @param aclId The id of the ACL to be deleted
 * @param responseCode {@link AJGWCAclResponseCode}
 * @return {@link QStatus}
 */
- (QStatus)deleteAclUsingSessionId:(AJNSessionId) sessionId aclId:(NSString*) aclId status:(AJGWCAclResponseCode &)responseCode;

@end
