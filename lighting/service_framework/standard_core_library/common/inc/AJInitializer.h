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

#ifndef AJINITIALIZER_H_
#define AJINITIALIZER_H_

#include <alljoyn/Status.h>

/**
 * class AJInitializer
 * Utility class for handling AllJoyn lifecycle methods
 */
class AJInitializer {
  public:
    /**
     * Calls AllJoynInit(). If bundled router is enabled it also calls AllJoynRouterInit()
     * @return ER_OK if initialization succeeded
     */
    QStatus Initialize();

    /**
     * ~AJInitializer
     * Calls AllJoynRouterShutdown() if bundled router is enabled and then calls AllJoynShutdown()
     */
    ~AJInitializer();
};

/**
 * class AJInitWrapper
 * Utility class wrapping AJInitializer functionality into a no-arg constructor
 */
class AJInitWrapper {
  public:
    AJInitializer ajInit;

    AJInitWrapper();
};

#endif /* AJINITIALIZER_H_ */

