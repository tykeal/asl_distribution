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

#import <Foundation/Foundation.h>
#import "alljoyn/notification/Notification.h"
#import "AJNSNotificationEnums.h"
#import "AJNSRichAudioUrl.h"
#import "AJNSNotificationText.h"

/**
 AJNSNotification class
 */

@interface AJNSNotification : NSObject

///---------------------
/// @name Properties
///---------------------
/** Array which holds incoming AJNSNotificationText objects */
@property (strong, nonatomic) NSMutableArray *ajnsntArr;

- (id)initWithHandle:(const ajn ::services ::Notification *)handle;

///---------------------
/// @name Initialization
///---------------------
/**
 Designated initializer
 
 @param messageId            The message id
 @param messageType          The message type
 @param deviceId             The device id
 @param deviceName           The device name
 @param appId                The app id
 @param appName              The app name
 @param sender               The sender name
 @param customAttributes     The notification custom attributes
 @param notificationText     The notification text(s)
 @param richIconUrl          The rich icon url
 @param richAudioUrl         The rich audio url
 @param richIconObjectPath   The rich icon object path
 @param richAudioObjectPath  The rich audio object path
 @param controlPanelServiceObjectPath The control panel service object path
 @return a `AJNSNotification` object
 */
- (AJNSNotification *)initWithMessageId:(int32_t)messageId
                           messageType:(AJNSNotificationMessageType)messageType
                              deviceId:(NSString *)deviceId
                            deviceName:(NSString *)deviceName
                                 appId:(NSString *)appId
                               appName:(NSString *)appName sender:(NSString *)sender
                      customAttributes:(NSMutableDictionary *)customAttributes
                      notificationText:(NSMutableArray *)notificationText
                           richIconUrl:(NSString *)richIconUrl
                          richAudioUrl:(NSMutableArray *)richAudioUrl
                    richIconObjectPath:(NSString *)richIconObjectPath
                   richAudioObjectPath:(NSString *)richAudioObjectPath
         controlPanelServiceObjectPath:(NSString *)controlPanelServiceObjectPath;

/**
 AJNSNotification initializer
 @param messageType      The message type
 @param notificationText The notification text(s)
 @return a `AJNSNotification` object
 */
- (AJNSNotification *)initWithMessageType:(AJNSNotificationMessageType)messageType andNotificationText:(NSMutableArray *)notificationText;

///---------------------
/// @name reterieval methods
///---------------------

/**
 Get the ProtoVersion
 @return protoversion The notification proto version
 */
- (int16_t)version;

/**
 Get the device Id
 @return deviceId The notification device id
 */
- (NSString *)deviceId;

/**
 Get the Device Name
 @return deviceName
 */
- (NSString *)deviceName;

/**
 Get the app Id
 @return appId
 */
- (NSString *)appId;

/**
 Get the app Name
 @return appName
 */
- (NSString *)appName;

/**
 Get the map of customAttributes
 @return customAttributes
 */
- (NSMutableDictionary *)customAttributes;

/**
 Get the Message Id
 @return notificationId
 */
- (int32_t)messageId;

/**
 Get the Sender
 @return Sender
 */
- (NSString *)senderBusName;

/**
 Get the MessageType
 @return MessageType
 */
- (AJNSNotificationMessageType)messageType;

/**
 Get the Notification Text
 @return notificationText
 */
- (NSArray *)text;

/**
 Get the Rich Icon Url
 @return RichIconUrl
 */
- (NSString *)richIconUrl;

/**
 Get the Rich Icon Object Path
 @return richIconObjectPath
 */
- (NSString *)richIconObjectPath;

/**
 Get the Rich Audio Object Path
 @return richAudioObjectPath
 */
- (NSString *)richAudioObjectPath;

/**
 Get the Rich Audio Urls
 @param inputArray array of URLs
 @return RichAudioUrl
 */
- (void)richAudioUrl:(NSMutableArray *)inputArray;

/**
 Get the ControlPanelService object path
 @return ControlPanelServiceObjectPath
 */
- (NSString *)controlPanelServiceObjectPath;

///---------------------
/// @name Setters
///---------------------

/**
 Set the App Id of the Notification
 @param appId The app id
 */
- (void)setAppId:(NSString *)appId;

/**
 Set the App Name of the Notification
 @param appName The app name
 */
- (void)setAppName:(NSString *)appName;

/**
 Set the Control Panel Service Object Path of the Notification
 @param controlPanelServiceObjectPath The control panel service object path
 */
- (void)setControlPanelServiceObjectPath:(NSString *)controlPanelServiceObjectPath;

/**
 Set the Custom Attributed of the Notification
 @param customAttributes The notification custom attributes
 */
- (void)setCustomAttributes:(NSMutableDictionary *)customAttributes;

/**
 Set the deviceId of the Notification
 @param deviceId The device id
 */
- (void)setDeviceId:(NSString *)deviceId;

/**
 Set the deviceName of the Notification
 @param deviceName The device name
 */
- (void)setDeviceName:(NSString *)deviceName;

/**
 Set the messageId of the Notification
 @param messageId The message id
 */
- (void)setMessageId:(int32_t)messageId;

/**
 Set the richAudioUrl of the Notification
 @param richAudioUrl The rich audio url
 */
- (void)setRichAudioUrl:(NSMutableArray *)richAudioUrl;

/**
 Set the richIconUrl of the Notification
 @param richIconUrl The rich icon url
 */
- (void)setRichIconUrl:(NSString *)richIconUrl;

/**
 Set the richIconObjectPath of the Notification
 @param richIconObjectPath The rich icon object path
 */
- (void)setRichIconObjectPath:(NSString *)richIconObjectPath;

/**
 Set the richAudioObjectPath of the Notification
 @param richAudioObjectPath  The rich audio object path
 */
- (void)setRichAudioObjectPath:(NSString *)richAudioObjectPath;

/**
 Set the sender name of the Notification
 @param sender The sender name
 */
- (void)setSender:(NSString *)sender;

- (QStatus) dismiss;

/**
 * Populate a temporary array to hold incoming AJNSNotificationText objects
 * This method is called when a new notification is coming
 */
- (void)createAJNSNotificationTextArray;

@property (nonatomic, readonly)ajn::services::Notification * handle;

@end

