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

#ifndef ACTIONWIDGET_H_
#define ACTIONWIDGET_H_

/** @defgroup ActionWidget Action Widget
 * details Action Widget Struct and Functions that assist in Un/Marshaling
 * Action Widget from/to a message.
 *  @{
 */

#include <ajtcl/services/Common/BaseWidget.h>

/////////////////////////*     ActionWidget     *//////////////////////////////////////

/**
 * ActionWidget structure - widget to represent an Action(Button)
 */
typedef struct ActionWidget {
    BaseWidget base; //!< Internal BaseWidget
} ActionWidget;

/**
 * Initialize the ActionWidget structure
 * @param widget - pointer to actionWidget structure
 */
void initializeActionWidget(ActionWidget* widget);

/** @} */
#endif /* ACTIONWIDGET_H_ */

