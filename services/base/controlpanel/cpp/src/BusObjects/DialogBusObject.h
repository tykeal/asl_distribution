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

#ifndef DIALOGBUSOBJECT_H_
#define DIALOGBUSOBJECT_H_

#include "WidgetBusObject.h"

namespace ajn {
namespace services {

/**
 * DialogBusObject - BusObject for Dialogs
 */
class DialogBusObject : public WidgetBusObject {
  public:

    /**
     * Constructor for DialogBusObject class
     * @param bus - the bus to create the interface
     * @param objectPath - objectPath of BusObject
     * @param langIndx - the languageIndex of the BusObject
     * @param status - success/failure
     * @param widget - the widget associated with the BusObject
     */
    DialogBusObject(ajn::BusAttachment* bus, qcc::String const& objectPath,
                    uint16_t langIndx, QStatus& status, Widget* widget);

    /**
     * Destructor for DialogBusObject
     */
    virtual ~DialogBusObject();

    /**
     * Callback for Alljoyn when GetProperty is called on this BusObject
     * @param interfaceName - the name of the Interface
     * @param propName - the name of the Property
     * @param val - the MsgArg to fill
     * @return status - success/failure
     */
    QStatus Get(const char* interfaceName, const char* propName, MsgArg& val);

    /**
     * Callback when Execute is called
     * @param member - the member (method) of the interface that was executed
     * @param msg - the Message of the method
     */
    void DialogExecute(const ajn::InterfaceDescription::Member* member, ajn::Message& msg);

    /**
     * Execute this Dialog's remoteAction 1
     * @return status - success/failure
     */
    QStatus ExecuteAction1();

    /**
     * Execute this Dialog's remoteAction 2
     * @return status - success/failure
     */
    QStatus ExecuteAction2();

    /**
     * Execute this Dialog's remoteAction 3
     * @return status - success/failure
     */
    QStatus ExecuteAction3();

  private:

    QStatus fillProperty(char* key, MsgArg* variant);
};

} /* namespace services */
} /* namespace ajn */
#endif /* DIALOGBUSOBJECT_H_ */
