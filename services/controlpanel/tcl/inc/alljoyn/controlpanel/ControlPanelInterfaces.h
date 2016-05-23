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

#ifndef CONTROLPANELINTERFACES_H_
#define CONTROLPANELINTERFACES_H_

#include <alljoyn.h>

/**
 * The Description of the root Interfaces, ControlPanel and NotificationAction
 */
extern const AJ_InterfaceDescription ControlPanelInterfaces[];
extern const AJ_InterfaceDescription NotificationActionInterfaces[];

/**
 * The Description of the PropertyInterface
 */
extern const AJ_InterfaceDescription PropertyInterfaces[];
extern const AJ_InterfaceDescription SecuredPropertyInterfaces[];

/**
 * The Description of the ActionInterface
 */
extern const AJ_InterfaceDescription ActionInterfaces[];
extern const AJ_InterfaceDescription SecuredActionInterfaces[];

/**
 * The Description of the ContainerInterface
 */
extern const AJ_InterfaceDescription ContainerInterfaces[];
extern const AJ_InterfaceDescription SecuredContainerInterfaces[];

/**
 * The Description of the LabelInterface
 */
extern const AJ_InterfaceDescription LabelPropertyInterfaces[];

/**
 * The Description of the DialogInterface
 */
extern const AJ_InterfaceDescription DialogInterfaces[];
extern const AJ_InterfaceDescription SecuredDialogInterfaces[];

/**
 * The Description of the HttpControlInterfaces
 */
extern const AJ_InterfaceDescription HttpControlInterfaces[];

#endif /* CONTROLPANELINTERFACES_H_ */
