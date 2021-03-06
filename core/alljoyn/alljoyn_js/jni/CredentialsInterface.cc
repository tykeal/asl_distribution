/*
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
 */
#include "CredentialsInterface.h"

#include <qcc/Debug.h>

#define QCC_MODULE "ALLJOYN_JS"

std::map<qcc::String, int32_t> _CredentialsInterface::constants;

std::map<qcc::String, int32_t>& _CredentialsInterface::Constants()
{
    if (constants.empty()) {
        CONSTANT("PASSWORD",          0x0001);
        CONSTANT("USER_NAME",         0x0002);
        CONSTANT("CERT_CHAIN",        0x0004);
        CONSTANT("PRIVATE_KEY",       0x0008);
        CONSTANT("LOGON_ENTRY",       0x0010);
        CONSTANT("EXPIRATION",        0x0020);
        CONSTANT("NEW_PASSWORD",      0x1001);
        CONSTANT("ONE_TIME_PWD",      0x2001);
    }
    return constants;
}

_CredentialsInterface::_CredentialsInterface(Plugin& plugin) :
    ScriptableObject(plugin, Constants())
{
    QCC_DbgTrace(("%s", __FUNCTION__));
}

_CredentialsInterface::~_CredentialsInterface()
{
    QCC_DbgTrace(("%s", __FUNCTION__));
}
