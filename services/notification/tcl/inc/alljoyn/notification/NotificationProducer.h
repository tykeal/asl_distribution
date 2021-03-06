/******************************************************************************
 * Copyright (c) 2013 - 2014, AllSeen Alliance. All rights reserved.
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

#ifndef NOTIFICATIONPRODUCER_H_
#define NOTIFICATIONPRODUCER_H_

#include <alljoyn/notification/NotificationCommon.h>
#include <alljoyn/services_common/ServicesCommon.h>

/** @defgroup NotificationProducer Notification Producer
 * details Functions and variables that assist in writing Notification Producers
 *  @{
 */

/*!
   \brief Constant for messageType
 */
#define AJNS_NOTIFICATION_MESSAGE_TYPE_EMERGENCY 0

/*!
   \brief Constant for messageType
 */
#define AJNS_NOTIFICATION_MESSAGE_TYPE_WARNING   1

/*!
   \brief Constant for messageType
 */
#define AJNS_NOTIFICATION_MESSAGE_TYPE_INFO      2

/*!
   \brief Constant for about of notification producer objects
 */
#define NUM_NOTIFICATION_PRODUCER_OBJECTS 4

/*!
   \brief The object path on which "Emergency" type notifications are sent
 */
extern const char AJNS_NotificationObjectPathEmergency[];

/*!
   \brief The object path on which "warning" type notifications are sent
 */
extern const char AJNS_NotificationObjectPathWarning[];

/*!
   \brief The object path on which "Info" type notifications are sent
 */
extern const char AJNS_NotificationObjectPathInfo[];

/*!
   \brief AllJoyn objects exposed by the NotificationProducer
 */
#define NOTIFICATION_PRODUCER_APPOBJECTS \
    { AJNS_NotificationObjectPathEmergency,     AJNS_NotificationInterfaces, AJ_OBJ_FLAG_ANNOUNCED }, \
    { AJNS_NotificationObjectPathWarning,       AJNS_NotificationInterfaces, AJ_OBJ_FLAG_ANNOUNCED }, \
    { AJNS_NotificationObjectPathInfo,          AJNS_NotificationInterfaces, AJ_OBJ_FLAG_ANNOUNCED }, \
    { AJNS_NotificationProducerObjectPath,      AJNS_NotificationProducerInterfaces, AJ_OBJ_FLAG_ANNOUNCED },

/*!
   \brief Send a notification with the given content
   \param busAttachment The bus through which the router is reached
   \param content
   \param messageType
   \param ttl
   \param messageSerialNumber Returned serial number of the outgoing notification message. Use later when calling \ref AJNS_Producer_CancelNotification.
   \return AJ_Status
 */
AJ_Status AJNS_Producer_SendNotification(AJ_BusAttachment* busAttachment, AJNS_NotificationContent* notificationContent, uint16_t messageType, uint32_t ttl, uint32_t* messageSerialNumber);

/*!
   \brief Instruct the AllJoyn bus to remove last message of the specified message type from the bus
   \details
   Effectively, this overrides the ttl parameter in the function
   \param busAttachment The bus through which the router is reached
   \param messageType One of \ref AJNS_NOTIFICATION_MESSAGE_TYPE_INFO, \ref AJNS_NOTIFICATION_MESSAGE_TYPE_WARNING, or \ref AJNS_NOTIFICATION_MESSAGE_TYPE_EMERGENCY
   \return AJ_Status
 */
AJ_Status AJNS_Producer_DeleteLastNotification(AJ_BusAttachment* busAttachment, uint16_t messageType);

/*!
   \brief Instruct the AllJoyn bus to remove message of the specified notification id the bus
   \details
   Effectively, this overrides the ttl parameter in the function
   \param busAttachment The bus through which the router is reached
   \param messageSerialNumber The serial number of the notification to cancel on the daemon
   \return AJ_Status
 */
AJ_Status AJNS_Producer_CancelNotification(AJ_BusAttachment* busAttachment, uint32_t messageSerialNumber);

/*!
   \brief Implementation of Dismiss functionality canceling the message on daemon and sending a Dismiss SSL to recall received message
   \details
   Effectively, this overrides the ttl parameter in the function
   \param busAttachment The bus through which the router is reached
   \param msg The received Dismiss request message to process
   \return AJ_Status
 */
AJ_Status AJNS_Producer_DismissRequestHandler(AJ_BusAttachment* busAttachment, AJ_Message* msg);

/*!
   \brief Implementation of GetProperty functionality for the notification objects
   \details
   Use this function to respond to Get Property events as a callback function passed to AJ_BusPropGet
   \skip switch (msg->msgId)
   \until }
   \param replyMsg The reply message that will be sent
   \param propId The identifier of the property field
   \param context For internal use
   \return AJ_Status
 */
AJ_Status AJNS_Producer_PropGetHandler(AJ_Message* replyMsg, uint32_t propId, void* context);

/*!
   \brief Implementation of SetProperty functionality for the notification objects
   \details
   Use this function to respond to Set Property events as a callback function passed to AJ_BusPropSet
   \skip switch (msg->msgId)
   \until }
   \param replyMsg The reply message that will be sent
   \param propId The identifier of the property field
   \param context For internal use
   \return AJ_Status
 */
AJ_Status AJNS_Producer_PropSetHandler(AJ_Message* replyMsg, uint32_t propId, void* context);

/**
 * Function called after busAttachment connects to router
 * @param busAttachment
 * @return status
 */
AJ_Status AJNS_Producer_ConnectedHandler(AJ_BusAttachment* busAttachment);

/**
 * Session request accept/reject function for service targetted session
 * @param port
 * @param sessionId
 * @param joiner
 */
uint8_t AJNS_Producer_CheckSessionAccepted(uint16_t port, uint32_t sessionId, const char* joiner);

/**
 * MessageProcessor function for the producer
 * @param busAttachment
 * @param msg
 * @param msgStatus
 * @return serviceStatus - was message handled
 */
AJSVC_ServiceStatus AJNS_Producer_MessageProcessor(AJ_BusAttachment* busAttachment, AJ_Message* msg, AJ_Status* msgStatus);

/**
 * Function called after busAttachment disconnects from router
 * @param busAttachment
 * @return status
 */
AJ_Status AJNS_Producer_DisconnectHandler(AJ_BusAttachment* busAttachment);

/** @} */ // End of group 'NotificationProducer'

#endif /* NOTIFICATIONPRODUCER_H_ */
