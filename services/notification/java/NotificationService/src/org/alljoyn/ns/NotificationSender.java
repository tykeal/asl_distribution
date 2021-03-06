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

package org.alljoyn.ns;

import java.util.List;
import java.util.Map;
import java.util.UUID;

import org.alljoyn.about.AboutKeys;
import org.alljoyn.ns.commons.GenericLogger;
import org.alljoyn.ns.commons.NativePlatform;
import org.alljoyn.ns.commons.NativePlatformFactory;
import org.alljoyn.ns.commons.NativePlatformFactoryException;
import org.alljoyn.ns.transport.Transport;


/** 
 * The class is used to trigger sending a notification
 */
public class NotificationSender {
	private static final String TAG = "ioe" + NotificationSender.class.getSimpleName();
	
	/**
	 * The TTL low limit in seconds  
	 */
	public static final int MESSAGE_TTL_LL = 30;
	
	/**
	 * The TTL upper limit in seconds
	 */
	public static final int MESSAGE_TTL_UL = 43200;
		
	/**
	 * Reference to native platform object
	 */
	private NativePlatform nativePlatform;

	/**
	 * Constructor
	 * @throws NotificationServiceException
	 */
	public NotificationSender() throws NotificationServiceException {
		try {
			nativePlatform       = NativePlatformFactory.getPlatformObject();
			GenericLogger logger = nativePlatform.getNativeLogger();
			logger.info(TAG,  "Notification Sender created");
		} catch (NativePlatformFactoryException npfe) {
			throw new NotificationServiceException("Failed to create Notification Service: " + npfe.getMessage());
		}
	}

	/**
	 * Send the Notification message
	 * @param notification The notification object to be sent
	 */
	public void send(Notification notification, int ttl) throws NotificationServiceException {
		GenericLogger logger = nativePlatform.getNativeLogger();
		
		if ( ttl < MESSAGE_TTL_LL || ttl > MESSAGE_TTL_UL ) {
			logger.error(TAG, "The allowed TTL range is between '" + MESSAGE_TTL_LL + "' and '" + MESSAGE_TTL_UL + "'");
			throw new NotificationServiceException("The allowed TTL range is between '" + MESSAGE_TTL_LL + "' and '" + MESSAGE_TTL_UL + "'");
		}
		
		Transport transport = Transport.getInstance();
		
		//get a map of the PropertyStore properties 
   	    Map<String, Object> props = transport.readAllProperties();
   	    
   	    UUID appId = transport.getAppId(props);
   	    
   	    String deviceId   = (String)props.get(AboutKeys.ABOUT_DEVICE_ID);
   	    if ( deviceId == null || deviceId.length() == 0 ) {
   	    	logger.error(TAG, "The DeviceId is NULL or empty");
   	    	throw new NotificationServiceException("The DeviceId is not set in the PropertyStore");
   	    }
   	    
   	    String deviceName = (String)props.get(AboutKeys.ABOUT_DEVICE_NAME);
   	    if ( deviceName == null || deviceName.length() == 0 ) {
   	    	logger.error(TAG, "The DeviceName is NULL or empty");
   	    	throw new NotificationServiceException("The DeviceName is not set in the PropertyStore");
   	    }
   	    
   	    String appName    = (String)props.get(AboutKeys.ABOUT_APP_NAME); 
   	    if ( appName == null || appName.length() == 0 ) {
   	    	logger.error(TAG, "The AppName is NULL or empty");
   	    	throw new NotificationServiceException("The AppName is not set in the PropertyStore");
   	    }
   	    
		NotificationMessageType messageType      = notification.getMessageType();
		List<NotificationText> text              = notification.getText();
		List<RichAudioUrl> richAudioUrl          = notification.getRichAudioUrl();
		Map<String, String> customAttributes     = notification.getCustomAttributes();
		String richIconUrl                       = notification.getRichIconUrl();
		String richIconObjPath                   = notification.getRichIconObjPath();
		String richAudioObjPath                  = notification.getRichAudioObjPath();
		String responseObjectPath                = notification.getResponseObjectPath();
		
		String audioUrl = null;
		if (richAudioUrl != null && richAudioUrl.size() > 0) {
			audioUrl = richAudioUrl.get(0).getUrl();
		}		
		
		logger.debug(TAG, "Sending message with message type: " + messageType + ", TTL: " + ttl + ", message: " + text.get(0).getText() + ", richIconUrl: '" + richIconUrl + "' RichAudioUrl: '" + audioUrl + ", richIconObjPath: '" + richIconObjPath + "' RichAudioObjPath: '" + richAudioObjPath + "'");
		PayloadAdapter.sendPayload(deviceId, deviceName, appId, appName, messageType, text, customAttributes, ttl, richIconUrl, richAudioUrl, richIconObjPath, richAudioObjPath, responseObjectPath);
	}//send

	/**
	 * Delete the last message by a given message type
	 * @param messageType
	 * @throws NotificationServiceException if message type was not defined
	 */	
	public void deleteLastMsg(NotificationMessageType messageType) throws NotificationServiceException  {
		if(messageType == null ) {
			throw new NotificationServiceException("MessageType parameter must be set");
		}
		Transport.getInstance().deleteLastMessage(messageType);
	}//deleteLastMsg

	

}//NotificationSenderImpl
