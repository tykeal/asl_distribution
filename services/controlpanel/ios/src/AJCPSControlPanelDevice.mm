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

#import "AJCPSControlPanelDevice.h"
#import "alljoyn/about/AJNConvertUtil.h"
#import "alljoyn/controlpanel/ControlPanelControllerUnit.h"
#import "AJCPSControlPanelListenerAdapter.h"
#import "AJCPSControlPanel.h"


@interface AJCPSControlPanelDevice ()
@property (nonatomic) ajn::services::ControlPanelDevice *handle;
@end


@implementation AJCPSControlPanelDevice

- (id)initWithHandle:(ajn::services::ControlPanelDevice *)handle;
{
	self = [super init];
	if (self) {
		self.handle = handle;
	}
	return self;
}

- (void)dealloc
{
	//we are not the creators of this handle
}

- (QStatus)startSessionAsync
{
	return self.handle->startSessionAsync();
}

- (QStatus)startSession
{
	return self.handle->startSession();
}

- (QStatus)endSession
{
	return self.handle->endSession();
}

- (QStatus)shutdownDevice
{
	return self.handle->shutdownDevice();
}

- (NSString *)getDeviceBusName
{
	return [AJNConvertUtil convertQCCStringtoNSString:self.handle->getDeviceBusName()];
}

- (AJNSessionId)getSessionId
{
	return self.handle->getSessionId();
}

// const std::map<qcc::String, ControlPanelControllerUnit*>& getDeviceUnits const;

- (NSDictionary *)getDeviceUnits
{
	const std::map <qcc::String, ajn::services::ControlPanelControllerUnit *>& cpp_deviceUnits = self.handle->getDeviceUnits();
    
	NSMutableDictionary *deviceUnits = [[NSMutableDictionary alloc]init];
    
	for (std::map <qcc::String, ajn::services::ControlPanelControllerUnit *>::const_iterator itr = cpp_deviceUnits.begin(); itr != cpp_deviceUnits.end(); itr++) {
		NSString *key = [AJNConvertUtil convertQCCStringtoNSString:itr->first];
		AJCPSControlPanelControllerUnit *value = [[AJCPSControlPanelControllerUnit alloc] initWithHandle:itr->second];
        
		[deviceUnits setObject:value forKey:key];
	}
    
	return deviceUnits;
}

- (NSArray *)getAllControlPanels
{
	std::vector <ajn::services::ControlPanel *> controlPanelsVec;
    
	self.handle->getAllControlPanels(controlPanelsVec);
    
	NSMutableArray *controlPanels = [[NSMutableArray alloc]init];
    
	for (int i = 0; i != controlPanelsVec.size(); i++) {
		AJCPSControlPanel *controlPanel = [[AJCPSControlPanel alloc]initWithHandle:controlPanelsVec.at(i)];
        
		[controlPanels addObject:controlPanel];
	}
    
	return controlPanels;
}

- (AJCPSControlPanelControllerUnit *)getControlPanelUnit:(NSString *)objectPath
{
	return [[AJCPSControlPanelControllerUnit alloc]initWithHandle:self.handle->getControlPanelUnit([AJNConvertUtil convertNSStringToQCCString:objectPath])];
}

- (AJCPSControlPanelControllerUnit *)addControlPanelUnit:(NSString *)objectPath interfaces:(NSArray *)interfaces
{
	std::vector <qcc::String> cpp_interfaces;
    
	for (NSString *str in interfaces) {
		cpp_interfaces.push_back([AJNConvertUtil convertNSStringToQCCString:str]);
	}
    
	return [[AJCPSControlPanelControllerUnit alloc]initWithHandle:self.handle->addControlPanelUnit([AJNConvertUtil convertNSStringToQCCString:objectPath], cpp_interfaces)];
}

- (AJCPSNotificationAction *)addNotificationAction:(NSString *)objectPath
{
	return [[AJCPSNotificationAction alloc]initWithHandle:self.handle->addNotificationAction([AJNConvertUtil convertNSStringToQCCString:objectPath])];
}

- (QStatus)removeNotificationAction:(AJCPSNotificationAction *)notificationAction
{
	return self.handle->removeNotificationAction([notificationAction handle]);
}

- (id <AJCPSControlPanelListener> )getListener
{
	AJCPSControlPanelListenerAdapter *adapter = (AJCPSControlPanelListenerAdapter *)self.handle->getListener();
    
	return adapter->getListener();
}

- (QStatus)setListener:(id <AJCPSControlPanelListener> )listener
{
	AJCPSControlPanelListenerAdapter *adapter = (AJCPSControlPanelListenerAdapter *)self.handle->getListener();
    
	if (adapter) {
		delete adapter;
		adapter = NULL; // for completeness sake
	}
    
	adapter = new AJCPSControlPanelListenerAdapter(listener);
    
	return self.handle->setListener(adapter);
}

@end