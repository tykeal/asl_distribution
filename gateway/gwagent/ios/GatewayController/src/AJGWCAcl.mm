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

#import "AJGWCAcl.h"
#import "alljoyn/about/AJNConvertUtil.h"
#import "AJGWCAnnouncementData.h"
#import "alljoyn/gateway/Enums.h"

@interface AJGWCAcl ()

@property (nonatomic) ajn::gwc::Acl* handle;

@end

@implementation AJGWCAcl

- (id)initWithHandle:(ajn::gwc::Acl *)handle
{
    self = [super init];
    if (self) {
        self.handle = (ajn::gwc::Acl *)handle;
    }
    return self;
}

//- (id)initWithGwBusName:(NSString*) gwBusName aclInfo:(AJNMessageArgument*) aclInfo
//{
//    self = [super init];
//    if (self) {
//        self.handle = new ajn::gwc::Acl([AJNConvertUtil convertNSStringToQCCString:gwBusName], (ajn::MsgArg*)aclInfo.handle);
//    }
//    return self;
//}

- (NSString*)aclName
{
    return [AJNConvertUtil convertQCCStringtoNSString:self.handle->getName()];
}

- (void)setAclName:(NSString*) name
{
    self.handle->setName([AJNConvertUtil convertNSStringToQCCString:name]);
}

- (NSString*)aclId
{
    return [AJNConvertUtil convertQCCStringtoNSString:self.handle->getId()];
}

- (NSString*)aclObjectPath
{
    return [AJNConvertUtil convertQCCStringtoNSString:self.handle->getObjectPath()];
}

- (NSString*)gwBusName
{
    return [AJNConvertUtil convertQCCStringtoNSString:self.handle->getGwBusName()];
}

- (QStatus)activateUsingSessionId:(AJNSessionId) sessionId aclResponseCode:(AJGWCAclResponseCode&) aclResponseCode
{
    return self.handle->activate(sessionId, (ajn::gwc::AclResponseCode&)aclResponseCode);
}

- (QStatus)deactivateUsingSessionId:(AJNSessionId) sessionId aclResponseCode:(AJGWCAclResponseCode&) aclResponseCode
{
    return self.handle->deactivate(sessionId, (ajn::gwc::AclResponseCode&)aclResponseCode);
}

- (QStatus)update:(AJNSessionId) sessionId aclRules:(AJGWCAclRules*) aclRules connectorCapabilities:(AJGWCConnectorCapabilities*) connectorCapabilities aclWriteResponse:(AJGWCAclWriteResponse**) aclWriteResponse
{

    ajn::gwc:: AclWriteResponse* aclWriteResponseHandle;

    QStatus status = self.handle->update(sessionId,
                           [aclRules handle],
                           [connectorCapabilities handle],
                           &aclWriteResponseHandle);

    if (ER_OK == status) {
        *aclWriteResponse = [[AJGWCAclWriteResponse alloc] initWithHandle:aclWriteResponseHandle];
    }

    return status;
}

- (QStatus)updateCustomMetadata:(AJNSessionId) sessionId metadata:(NSDictionary*) metadata status:(AJGWCAclResponseCode&) aclResponseCode
{
    std::map<qcc::String, qcc::String> metadataMap;
    // Populate std::map with NSDictionary data
    for (NSString* key in metadata.allKeys) {
        metadataMap.insert(std::make_pair([AJNConvertUtil convertNSStringToQCCString:key], [AJNConvertUtil convertNSStringToQCCString:[metadata objectForKey:key]]));
    }

    return self.handle->updateCustomMetadata(sessionId, metadataMap, (ajn::gwc::AclResponseCode&)aclResponseCode);
}

- (QStatus)updateMetadata:(AJNSessionId) sessionId metadata:(NSDictionary*) metadata status:(AJGWCAclResponseCode&) aclResponseCode
{
    std::map<qcc::String, qcc::String> metadataMap;
    // Populate std::map with NSDictionary data
    for (NSString* key in metadata.allKeys) {
        metadataMap.insert(std::make_pair([AJNConvertUtil convertNSStringToQCCString:key], [AJNConvertUtil convertNSStringToQCCString:[metadata objectForKey:key]]));
    }

    return self.handle->updateAclMetadata(sessionId, metadataMap, (ajn::gwc::AclResponseCode&)aclResponseCode);
}

- (AJGWCAclStatus)status
{
    return (AJGWCAclStatus)self.handle->getStatus();
}

- (QStatus)retrieveStatusUsingSessionId:(AJNSessionId) sessionId aclStatus:(AJGWCAclStatus&) aclStatus
{
    return self.handle->retrieveStatus(sessionId, (ajn::gwc::AclStatus&)aclStatus);
}

- (QStatus)retrieveUsingSessionId:(AJNSessionId) sessionId connectorCapabilities:(AJGWCConnectorCapabilities*) connectorCapabilities announcements:(NSArray*) announcements aclRules:(AJGWCAclRules**) aclRules
{
    std::vector<ajn::gwc::AnnouncementData *>  announcementsVect;

    // Populate std::vector of AnnouncementData with NSArray of AJGWCAnnouncementData
    for(AJGWCAnnouncementData* announcementData in announcements)
    {
        // port
        uint16_t port = [announcementData port];

        // Populate AboutData (std::map<qcc::String, ajn::MsgArg> AboutData)
        NSDictionary* aboutDataDict = [announcementData aboutData];
        ajn::services::AboutClient::AboutData aboutDataMap;
        for(NSString* key in aboutDataDict.allKeys)
        {
            qcc::String aboutDataMapKey = [AJNConvertUtil convertNSStringToQCCString:key]; // key
            ajn::MsgArg* aboutDataMapVal = (ajn::MsgArg*)[[aboutDataDict objectForKey:key] handle]; //value
            aboutDataMap.insert(std::make_pair(aboutDataMapKey, *aboutDataMapVal));
        }

        // ObjectDescriptions (std::map<qcc::String, std::vector<qcc::String> > )
        NSDictionary* objectDescriptionsDict = [announcementData objectDescriptions];
        ajn::services::AboutClient::ObjectDescriptions objectDescriptionsMap;

        for(NSString* key in objectDescriptionsDict.allKeys)
        {
            std::vector<qcc::String> objDescVect;

            for (NSString* str in [objectDescriptionsDict objectForKey:key])
            {
                objDescVect.insert(objDescVect.end(), [AJNConvertUtil convertNSStringToQCCString:str]); // add the strings to std::vector
            }
            objectDescriptionsMap.insert(std::make_pair([AJNConvertUtil convertNSStringToQCCString:key], objDescVect)); //insert into objectDescriptionMap
        }

        ajn::gwc::AnnouncementData* annData = new ajn::gwc::AnnouncementData(port, aboutDataMap, objectDescriptionsMap);
        announcementsVect.insert(announcementsVect.end(), annData);
    } //for

    const ajn::gwc::ConnectorCapabilities* gwConnectorCapabilities = const_cast<ajn::gwc::ConnectorCapabilities*>([connectorCapabilities handle]);

    ajn::gwc::AclRules* gwAccessRule;

    QStatus status =  self.handle->retrieve(sessionId, *gwConnectorCapabilities, announcementsVect, &gwAccessRule);

    *aclRules = [[AJGWCAclRules alloc] initWithHandle:gwAccessRule];

    return status;
}
@end
