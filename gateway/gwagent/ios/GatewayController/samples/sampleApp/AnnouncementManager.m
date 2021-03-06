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

#import "AnnouncementManager.h"
#import "alljoyn/Status.h"
#import "AJNStatus.h"
#import "AJNMessageArgument.h"
#import "alljoyn/about/AJNAboutDataConverter.h"

static dispatch_queue_t annQueue;

@interface AnnouncementManager ()

@property (atomic) NSMutableArray* announcements;

@end


@implementation AnnouncementManager

+ (id)sharedInstance
{
    static AnnouncementManager *announcementManager;

    static dispatch_once_t donce;
    dispatch_once(&donce, ^{
        announcementManager = [[self alloc] init];
        annQueue = dispatch_queue_create("org.alljoyn.annQueue", NULL);
    });

    return announcementManager;
}

- (void)destroyInstance
{
    [_announcements removeAllObjects];
}
- (id)init
{
    if (self = [super init]) {
        _announcements = [[NSMutableArray alloc] init];
    }
    return self;
}


- (NSArray*)getAnnouncements
{
    return _announcements;
}

- (void)addNewAnnouncement:(AJGWCAnnouncementData*) announcement
{
    // Dealing with announcement entries should be syncronized, so we add it to a queue
    dispatch_sync(annQueue, ^{
    AJNMessageArgument *appIdMsgArg = [announcement aboutData][@"AppId"];
    uint8_t *appIdBuffer;
    size_t appIdNumElements;
    QStatus status;
    status = [appIdMsgArg value:@"ay", &appIdNumElements, &appIdBuffer];

    // Add the received announcement
    if (status != ER_OK) {
        NSLog(@"AnnouncementManager has failed to read appId:%@ - not using this announcement", [AJNStatus descriptionForStatusCode:status]);
        return;
    }

    // Dealing with announcement entries should be syncronized, so we add it to a queue
        uint8_t *tmpAppIdBuffer;
        size_t tmpAppIdNumElements;
        QStatus tmpStatus;
        int res;

        // Iterate over the announcements dictionary
        for (AJGWCAnnouncementData *tmpAnn in self.announcements) {
            AJNMessageArgument *tmpMsgrg = [tmpAnn aboutData][@"AppId"];

            tmpStatus = [tmpMsgrg value:@"ay", &tmpAppIdNumElements, &tmpAppIdBuffer];
            if (tmpStatus != ER_OK) {
                NSLog(@"AnnouncementManager has failed to read appId:%@", [AJNStatus descriptionForStatusCode:tmpStatus]);
                return;
            }

            res = 1;
            // compare if the announcement AppId already exists
            if (appIdNumElements == tmpAppIdNumElements) {
                res = memcmp(appIdBuffer, tmpAppIdBuffer, appIdNumElements);
            }

            // found a matched (res=0)
            if (!res) {
                NSLog(@"AnnouncementManager got an announcement from a known appID - checking the DeviceId");
                //check if deviceId is identical
                AJNMessageArgument *deviceIdMsgArg = [announcement aboutData][@"DeviceId"];
                NSString* deviceIdStr = [AJNAboutDataConverter messageArgumentToString:deviceIdMsgArg];

                AJNMessageArgument *tmpDeviceIdMsgArg = [tmpAnn aboutData][@"DeviceId"];
                NSString* tmpDeviceIdStr = [AJNAboutDataConverter messageArgumentToString:tmpDeviceIdMsgArg];

                if ([deviceIdStr isEqualToString:tmpDeviceIdStr]) {
                    NSLog(@"AnnouncementManager got an announcement with the same appID + DeviceId - removing the existed one.");
                    [_announcements removeObject:tmpAnn];
                }
            }

        }
    NSLog(@"adding a new announcement to AnnouncementManager");
    [_announcements addObject:announcement];

    });
}

@end
