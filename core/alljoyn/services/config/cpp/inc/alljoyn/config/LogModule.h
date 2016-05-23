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


#ifndef LOGMODULE_H_
#define LOGMODULE_H_

#include <qcc/Debug.h>
#include <qcc/platform.h>

namespace ajn {
namespace services {
namespace logModules {

static char const* const CONFIG_MODULE_LOG_NAME = "Config";
static const uint32_t ALL_LOG_LEVELS = 15;
}

static char const* const QCC_MODULE = logModules::CONFIG_MODULE_LOG_NAME;
}
}

#endif /* LOGMODULE_H_ */
