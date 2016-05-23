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

#import "AJCPSHttpControl.h"
#import "AJCPSControlPanelDevice.h"
#import "alljoyn/about/AJNConvertUtil.h"

@interface AJCPSHttpControl ()
@property ajn::services::HttpControl *handle;
@end

@implementation AJCPSHttpControl

- (id)initWithHandle:(ajn::services::HttpControl *)handle
{
	self = [super init];
	if (self) {
		self.handle = handle;
	}
	return self;
}

- (uint16_t)getInterfaceVersion
{
    return ((ajn::services::HttpControl *)self.handle)->getInterfaceVersion();
}

/**
 * Register the HttpControl BusObject
 * @param bus - bus used for registering the object
 * @return status - success/failure
 */
- (QStatus)registerObjects:(AJNBusAttachment *)bus
{
	return ((ajn::services::HttpControl *)self.handle)->registerObjects((ajn::BusAttachment *)[bus handle]);
}

/**
 * Refresh the HttpControl
 * @param bus - bus used for refreshing the object
 * @return status - success/failure
 */
- (QStatus)refreshObjects:(AJNBusAttachment *)bus
{
	return ((ajn::services::HttpControl *)self.handle)->refreshObjects((ajn::BusAttachment *)[bus handle]);
}

/**
 * Unregister the HttpControl BusObject
 * @param bus - bus used to unregister the object
 * @return status - success/failure
 */
- (QStatus)unregisterObjects:(AJNBusAttachment *)bus
{
	return ((ajn::services::HttpControl *)self.handle)->unregisterObjects((ajn::BusAttachment *)[bus handle]);
}

/**
 * Get the Device that contains this HttpControl
 * @return ControlPanelDevice
 */
- (AJCPSControlPanelDevice *)getDevice
{
	return [[AJCPSControlPanelDevice alloc]initWithHandle:((ajn::services::HttpControl *)self.handle)->getDevice()];
}

/**
 * Get the Url for the HttpControl
 * @return url
 */
- (NSString *)getUrl
{
	return [AJNConvertUtil convertQCCStringtoNSString:((ajn::services::HttpControl *)self.handle)->getUrl()];
}

/**
 * Get the ControlPanelMode of this HttpControl
 * @return ControlPanelMode
 */
- (AJCPSControlPanelMode)getControlPanelMode
{
	return ((ajn::services::HttpControl *)self.handle)->getControlPanelMode();
}

@end




//#ifndef HTTPCONTROL_H_
//#define HTTPCONTROL_H_
//
//#include <alljoyn/BusObject.h>
//#include <alljoyn/controlpanel/ControlPanelEnums.h>
//
//namespace ajn {
//namespace services {
//
//class ControlPanelDevice;
//class HttpControlBusObject;
//
///**
// * HttpControl class. Allows definition of a url
// */
//class HttpControl {
//  public:
//
//    /**
//     * Constructor for HttpControl
//     * @param url - url of HttpControl
//     */
//    HttpControl(qcc::String const& url);// SKIP
//
//    /**
//     * Constructor for HttpControl
//     * @param objectPath - objectPath of HttpControl
//     * @param device - the device containing this HttpControl
//     */
//    HttpControl(qcc::String const& objectPath, ControlPanelDevice* device);
//
//    /**
//     * Destructor of HttpControl
//     */
//    virtual ~HttpControl();
//
//    /**
//     * Get the Interface Version of the HttpControl
//     * @return interface Version
//     */
//    const uint16_t getInterfaceVersion() const;
//
//    /**
//     * Register the HttpControl BusObject
//     * @param bus - bus used for registering the object
//     * @param unitName - name of unit
//     * @return status - success/failure
//     */
//    QStatus registerObjects(BusAttachment* bus, qcc::String const& unitName);// SKIP
//
//    /**
//     * Register the HttpControl BusObject
//     * @param bus - bus used for registering the object
//     * @return status - success/failure
//     */
//    QStatus registerObjects(BusAttachment* bus);
//
//    /**
//     * Refresh the HttpControl
//     * @param bus - bus used for refreshing the object
//     * @return status - success/failure
//     */
//    QStatus refreshObjects(BusAttachment* bus);
//
//    /**
//     * Unregister the HttpControl BusObject
//     * @param bus - bus used to unregister the object
//     * @return status - success/failure
//     */
//    QStatus unregisterObjects(BusAttachment* bus);
//
//    /**
//     * Fill MsgArg passed in with Url
//     * @param val - msgArg to fill
//     * @return status - success/failure
//     */
//    QStatus fillUrlArg(MsgArg& val);// SKIP
//
//    /**
//     * Read MsgArg passed in and use it to set the url
//     * @param val - MsgArg passed in
//     * @return status - success/failure
//     */
//    QStatus readUrlArg(MsgArg const& val);// SKIP
//
//    /**
//     * Read MsgArg passed in and use it to set the url
//     * @param val - MsgArg passed in
//     * @return status - success/failure
//     */
//    QStatus readVersionArg(MsgArg const& val);// SKIP
//
//    /**
//     * Get the Device that contains this HttpControl
//     * @return ControlPanelDevice
//     */
//    ControlPanelDevice* getDevice() const;
//
//    /**
//     * Get the Url for the HttpControl
//     * @return url
//     */
//    const qcc::String& getUrl() const;
//
//    /**
//     * Get the ControlPanelMode of this HttpControl
//     * @return ControlPanelMode
//     */
//    ControlPanelMode getControlPanelMode() const;
//
//  private:
//
//    /**
//     * Url of HttpControl
//     */
//    qcc::String m_Url;
//
//    /**
//     * ObjectPath of HttpControl
//     */
//    qcc::String m_ObjectPath;
//
//    /**
//     * BusObject of HttpControl
//     */
//    HttpControlBusObject* m_HttpControlBusObject;
//
//    /**
//     * The Device containing the HttpControl
//     */
//    ControlPanelDevice* m_Device;
//
//    /**
//     * The mode of the HttpControl
//     */
//    ControlPanelMode m_ControlPanelMode;
//
//    /**
//     * Version of the Widget
//     */
//    uint16_t m_Version;
//
//    /**
//     * Copy constructor of  HttpControl - private.  HttpControl is not copy-able
//     * @param  httpControl -  HttpControl to copy
//     */
//    HttpControl(const HttpControl&  httpControl);
//
//    /**
//     * Assignment operator of HttpControl - private. HttpControl is not assignable
//     * @param httpControl
//     * @return
//     */
//    HttpControl& operator=(const HttpControl&  httpControl);
//};
//} //namespace services
//} //namespace ajn
//
//#endif /* HTTPCONTROL_H_ */
