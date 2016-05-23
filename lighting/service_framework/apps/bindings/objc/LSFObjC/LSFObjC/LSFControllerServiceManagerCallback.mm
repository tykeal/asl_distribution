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

#import "LSFControllerServiceManagerCallback.h"

LSFControllerServiceManagerCallback::LSFControllerServiceManagerCallback(id<LSFControllerServiceManagerCallbackDelegate> delegate) : _csmDelegate(delegate)
{
    //Empty Constructor
}

LSFControllerServiceManagerCallback::~LSFControllerServiceManagerCallback()
{
    _csmDelegate = nil;
}

void LSFControllerServiceManagerCallback::GetControllerServiceVersionReplyCB(uint32_t version)
{
    [_csmDelegate getControllerServiceVersionReply: version];
}

void LSFControllerServiceManagerCallback::LightingResetControllerServiceReplyCB(LSFResponseCode responseCode)
{
    [_csmDelegate lightingResetControllerServiceReplyWithCode: responseCode];
}

void LSFControllerServiceManagerCallback::ControllerServiceLightingResetCB(void)
{
    [_csmDelegate controllerServiceLightingReset];
}

void LSFControllerServiceManagerCallback::ControllerServiceNameChangedCB(const LSFString& controllerServiceDeviceID, const LSFString& controllerServiceName)
{
    [_csmDelegate controllerServiceNameChangedForControllerID: [NSString stringWithUTF8String: controllerServiceDeviceID.c_str()] andName: [NSString stringWithUTF8String: controllerServiceName.c_str()]];
}
