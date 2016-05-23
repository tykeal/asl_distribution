////////////////////////////////////////////////////////////////////////////////
// Copyright AllSeen Alliance. All rights reserved.
//
//    Contributed by Qualcomm Connected Experiences, Inc.,
//    with authorization from the AllSeen Alliance, Inc.
//    
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//    
//        http://www.apache.org/licenses/LICENSE-2.0
//    
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//    
//    Pursuant to Section 1 of the License, the work of authorship constituting
//    a Work and any Contribution incorporated in the Work shall mean only that
//    Contributor's code submissions authored by that Contributor.  Any rights
//    granted under the License are conditioned upon acceptance of these
//    clarifications.
////////////////////////////////////////////////////////////////////////////////

#import "BasicClient.h"

#include <qcc/platform.h>

#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <vector>

#include <qcc/String.h>

#include <alljoyn/BusAttachment.h>
#include <alljoyn/version.h>
#include <alljoyn/AllJoynStd.h>
#include <Status.h>

using namespace std;
using namespace qcc;
using namespace ajn;

static BasicClient *s_basicClient;

#import "AJNBusAttachment.h"
#import "AJNInterfaceDescription.h"
#import "AJNSessionOptions.h"
#import "AJNVersion.h"
#import "BasicObject.h"

////////////////////////////////////////////////////////////////////////////////
//
// Constants
//

static NSString* kBasicClientInterfaceName = @"org.alljoyn.bus.sample";
static NSString* kBasicClientServiceName = @"org.alljoyn.bus.sample";
static NSString* kBasicClientServicePath = @"/sample";
static const AJNSessionPort kBasicClientServicePort = 25;

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Basic Client private interface
//

@interface BasicClient() <AJNBusListener, AJNSessionListener>

@property (nonatomic, strong) AJNBusAttachment *bus;
@property (nonatomic, strong) NSCondition *joinedSessionCondition;
@property (nonatomic) AJNSessionId sessionId;
@property (nonatomic, strong) NSString *foundServiceName;
@property (nonatomic, strong) BasicObjectProxy *basicObjectProxy;
@property BOOL wasNameAlreadyFound;

@end

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Basic Client implementation
//

@implementation BasicClient

@synthesize bus = _bus;
@synthesize joinedSessionCondition = _joinedSessionCondition;
@synthesize sessionId = _sessionId;
@synthesize foundServiceName = _foundServiceName;
@synthesize basicObjectProxy = _basicObjectProxy;
@synthesize wasNameAlreadyFound = _wasNameAlreadyFound;
@synthesize delegate;

+ (BasicClient*)sharedInstance
{
    @synchronized(self) {
        if (s_basicClient == nil) {
            s_basicClient = [[BasicClient alloc] init];
        }
    }
    return s_basicClient;
}

- (void)sendHelloMessage
{
    dispatch_queue_t clientQueue = dispatch_queue_create("org.alljoyn.basic-service.clientQueue",NULL);
    dispatch_async( clientQueue, ^{
        [self run];
    });
    dispatch_release(clientQueue);
}

- (void)run
{
    NSLog(@"AllJoyn Library version: %@", AJNVersion.versionInformation);
    NSLog(@"AllJoyn Library build info: %@\n", AJNVersion.buildInformation);
    [self.delegate didReceiveStatusUpdateMessage:[NSString stringWithFormat:@"AllJoyn Library version: %s\n", ajn::GetVersion()]];
    [self.delegate didReceiveStatusUpdateMessage:[NSString stringWithFormat:@"AllJoyn Library build info: %s\n", ajn::GetBuildInfo()]];

    NSLog(@"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    NSLog(@"+ Creating bus attachment                                                                 +");
    NSLog(@"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    
    QStatus status;
    
    self.wasNameAlreadyFound = NO;
    
    // create the message bus
    //
    self.bus = [[AJNBusAttachment alloc] initWithApplicationName:@"BasicClient" allowRemoteMessages:YES];
    
    // create an interface description
    //
    AJNInterfaceDescription *interfaceDescription = [self.bus createInterfaceWithName:@"org.alljoyn.bus.sample" enableSecurity:NO];
    
    // add the methods to the interface description
    //
    status = [interfaceDescription addMethodWithName:@"cat" inputSignature:@"ss" outputSignature:@"s" argumentNames:[NSArray arrayWithObjects:@"str1",@"str2",@"outStr", nil]];
    
    if (status != ER_OK && status != ER_BUS_MEMBER_ALREADY_EXISTS) {
        @throw [NSException exceptionWithName:@"BusObjectInitFailed" reason:@"Unable to add method to interface: cat" userInfo:nil];
    }
    
    [interfaceDescription activate];
    
    // start the message bus
    //
    status =  [self.bus start];
    
    if (ER_OK != status) {
        NSLog(@"Bus start failed.");
        [self.delegate didReceiveStatusUpdateMessage:@"BusAttachment::Start failed\n"];
    }
    else {
        [self.delegate didReceiveStatusUpdateMessage:@"BusAttachment started.\n"];
    }
    
    // connect to the message bus
    //
    status = [self.bus connectWithArguments:@"null:"];
    
    if (ER_OK != status) {
        NSLog(@"Bus connect failed.");
        [self.delegate didReceiveStatusUpdateMessage:@"BusAttachment::Connect(\"null:\") failed\n"];
    }
    else {
        [self.delegate didReceiveStatusUpdateMessage:@"BusAttachement connected to null:\n"];
    }


    self.joinedSessionCondition = [[NSCondition alloc] init];
    [self.joinedSessionCondition lock];
    
    // register a bus listener in order to receive discovery notifications
    //
    [self.bus registerBusListener:self];
    [self.delegate didReceiveStatusUpdateMessage:@"BusListener Registered.\n"];
    
    // begin discovery of the well known name of the service to be called
    //
    [self.bus findAdvertisedName:kBasicClientServiceName];

    [self.delegate didReceiveStatusUpdateMessage:@"Waiting to discover service...\n"];
    
    // wait for the join session to complete
    //
    if ([self.joinedSessionCondition waitUntilDate:[NSDate dateWithTimeIntervalSinceNow:60]]) {
        
        // once joined to a session, use a proxy object to make the function call
        //
        self.basicObjectProxy = [[BasicObjectProxy alloc] initWithBusAttachment:self.bus serviceName:self.foundServiceName objectPath:kBasicClientServicePath sessionId:self.sessionId];
        
        // get a description of the interfaces implemented by the remote object before making the call
        //
        [self.basicObjectProxy introspectRemoteObject];
        
        // now make the function call
        //
        NSString *result = [self.basicObjectProxy concatenateString:@"Code " withString:@"Monkies!!!!!!!"];
        
        if (result) {
            NSLog(@"[%@] %@ concatenated string.", result, [result compare:@"Code Monkies!!!!!!!"] == NSOrderedSame ? @"Successfully":@"Unsuccessfully");
            [self.delegate didReceiveStatusUpdateMessage:@"Successfully called method on remote object!!!\n"];
        }
        
        self.basicObjectProxy = nil;
        
    }
    else {
        NSLog(@"Timed out while attempting to join a session with BasicService...");
    }
    
    [self.joinedSessionCondition unlock];
    
    NSLog(@"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    NSLog(@"+ Destroying bus attachment                                                               +");
    NSLog(@"+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++");
    
    // deallocate the bus
    //
    self.bus = nil;
}

#pragma mark - AJNBusListener delegate methods

- (void)listenerDidRegisterWithBus:(AJNBusAttachment*)busAttachment
{
    NSLog(@"AJNBusListener::listenerDidRegisterWithBus:%@",busAttachment);
}

- (void)listenerDidUnregisterWithBus:(AJNBusAttachment*)busAttachment
{
    NSLog(@"AJNBusListener::listenerDidUnregisterWithBus:%@",busAttachment);
}

- (void)didFindAdvertisedName:(NSString*)name withTransportMask:(AJNTransportMask)transport namePrefix:(NSString*)namePrefix
{
    NSLog(@"AJNBusListener::didFindAdvertisedName:%@ withTransportMask:%u namePrefix:%@", name, transport, namePrefix);
    
    [self.delegate didReceiveStatusUpdateMessage:[NSString stringWithFormat:@"FoundAdvertisedName(name=%@, prefix=%@)\n", name, namePrefix]];
    if ([namePrefix compare:kBasicClientServiceName] == NSOrderedSame) {
        
        BOOL shouldReturn;
        @synchronized(self) {
            shouldReturn = self.wasNameAlreadyFound;
            self.wasNameAlreadyFound = true;
        }
        
        if (shouldReturn) {
            NSLog(@"Already found an advertised name, ignoring this name %@...", name);
            return;
        }
        
        // Since we are in an AllJoyn callback we must enable concurrent callbacks before calling a synchronous method.
        //
        [self.bus enableConcurrentCallbacks];
        
        self.sessionId = [self.bus joinSessionWithName:name onPort:kBasicClientServicePort withDelegate:self options:[[AJNSessionOptions alloc] initWithTrafficType:kAJNTrafficMessages supportsMultipoint:YES proximity:kAJNProximityAny transportMask:kAJNTransportMaskAny]];
        
        if (self.sessionId) {
            self.foundServiceName = name;
            
            NSLog(@"Client joined session %d", self.sessionId);

            [self.delegate didReceiveStatusUpdateMessage:[NSString stringWithFormat:@"JoinSession SUCCESS (Session id=%d)\n", self.sessionId]];

        }
        else {
            [self.delegate didReceiveStatusUpdateMessage:@"JoinSession failed\n"];            
        }
        
        [self.joinedSessionCondition signal];
    }
}

- (void)didLoseAdvertisedName:(NSString*)name withTransportMask:(AJNTransportMask)transport namePrefix:(NSString*)namePrefix
{
    NSLog(@"AJNBusListener::listenerDidUnregisterWithBus:%@ withTransportMask:%u namePrefix:%@",name,transport,namePrefix);
}

- (void)nameOwnerChanged:(NSString*)name to:(NSString*)newOwner from:(NSString*)previousOwner
{
    NSLog(@"AJNBusListener::nameOwnerChanged:%@ to:%@ from:%@", name, newOwner, previousOwner);
    [self.delegate didReceiveStatusUpdateMessage:[NSString stringWithFormat:@"NameOwnerChanged: name=%@, oldOwner=%@, newOwner=%@\n", name, previousOwner, newOwner]];
}

- (void)busWillStop
{
    NSLog(@"AJNBusListener::busWillStop");
}

- (void)busDidDisconnect
{
    NSLog(@"AJNBusListener::busDidDisconnect");
}

#pragma mark - AJNSessionListener methods

- (void)sessionWasLost:(AJNSessionId)sessionId forReason:(AJNSessionLostReason)reason
{
    NSLog(@"AJNBusListener::sessionWasLost %u forReason %u", sessionId, reason);
}

- (void)didAddMemberNamed:(NSString*)memberName toSession:(AJNSessionId)sessionId
{
    NSLog(@"AJNBusListener::didAddMemberNamed:%@ toSession:%u", memberName, sessionId);
}

- (void)didRemoveMemberNamed:(NSString*)memberName fromSession:(AJNSessionId)sessionId
{
    NSLog(@"AJNBusListener::didRemoveMemberNamed:%@ fromSession:%u", memberName, sessionId);
}

@end
