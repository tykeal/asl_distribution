/******************************************************************************
 * Copyright (c) 2013, AllSeen Alliance. All rights reserved.
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

// AllJoyn Objective-C Framework headers
#import "AllJoynFramework/AJNSessionOptions.h"

// Status Types 
typedef enum {
    PGMInvalid,
    PGMHostedAndUnlocked,
    PGMHostedAndLocked,
    PGMJoinedAndUnlocked,
    PGMJoinedAndLocked,
    PGMFound                 // Not hosted, not joined. Advertisement seen
} PGMStatus;

/* Invalid Session Port */
#define PGMBadSessionPort 0
 
/*
 * PGMGroup is a class that contains the data representing a group. This class is
 * only used by the PGMGroupRegistry.
 */
@interface PGMGroup : NSObject  

/* The session id of the group. */
@property (nonatomic) AJNSessionId sessionId;

/* The session port of the group. */
@property (nonatomic) AJNSessionPort sessionPort;

/* 
 * Flag denoting that the group is a Legacy AllJoyn group which does not advertise
 * a name which follows the naming convention of PeerGroupManager groups.
 */
@property (nonatomic) BOOL isLegacyGroup;

/* The status or state of the group in respect to the user of the PeerGroupManager. */
@property (nonatomic) PGMStatus status;

/* The name of the group. */
@property (nonatomic, copy) NSString *groupName;

/* An array of peer ids (NSStrings) of all the peers in the group. */
@property (nonatomic, strong) NSMutableArray *idsOfPeers;

/*
 * An array of peer ids (NSStrings) of all the peers allowed in the group.
 * This property is to be used for controlling who is allowed to join the 
 * group in the acceptance policy once createPrivateGroup: is implemented.
 */
@property (nonatomic, strong) NSMutableArray *idsOfAllowedPeers;

@end
