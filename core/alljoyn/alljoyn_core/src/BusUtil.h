# Contributed by Qualcomm Connected Experiences, Inc.,
# with authorization from the AllSeen Alliance, Inc.
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
# 
# Pursuant to Section 1 of the License, the work of authorship constituting
# a Work and any Contribution incorporated in the Work shall mean only that
# Contributor's code submissions authored by that Contributor.  Any rights
# granted under the License are conditioned upon acceptance of these
# clarifications.
#ifndef _ALLJOYN_BUSUTIL_H
#define _ALLJOYN_BUSUTIL_H
/**
 * @file
 *
 * This file defines a namespace for utility functions
 *
 */

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

#ifndef __cplusplus
#error Only include BusUtil.h in C++ code.
#endif

#include <qcc/platform.h>
#include <qcc/String.h>
#include <map>

#include <alljoyn/Status.h>

namespace ajn {
/**
 * Checks if the string passed is a well-formed unique name.
 *
 * A well-formed unique name means it begins with a @c ':' and has
 * the form @c i.j[.k]* where  <tt> i, j, k </tt> are integers.
 * Unique names are nul terminated and have a maximum length of 255
 * characters not including the nul.
 *
 * @param str  The string to check
 *
 * @return true if the string is a well-formed unique name
 */
bool IsLegalUniqueName(const char* str);

/**
 * Checks if the string passed is a well-formed bus name.
 *
 * A well-formed bus name means it is either a legal unique name or a series of alphanumeric
 * characters, underscores, and hyphens separated by period characters.  A bus name must have
 * at least one period character and cannot start with a period character. Bus names are nul
 * terminated and have a maximum length of 255 characters not including the nul.
 *
 * @param str  The string to check
 *
 * @return true if the string is a well-formed bus name
 */
bool IsLegalBusName(const char* str);

/**
 * Checks if the string passed is a well-formed object path.
 *
 * An object path is sequences of alphanumeric characters and underscores separated by
 * forward slashes ('/'). The first character must be a forward slash, the last character
 * cannot be a forward slash unless the entire path is a single forward slash (denoting the root object).
 * Object paths are nul terminated and unlike other names have no length limit.
 *
 * @param str  The string to check
 *
 * @return true if the string is a well-formed object path
 */
bool IsLegalObjectPath(const char* str);

/**
 * Checks if the string passed is a well-formed interface name.
 *
 * An interface name is sequences of alphanumeric characters and underscores separated by
 * period characters. An interface name must have at least one period character and cannot
 * start with a period character. They are nul terminated and have a maximum length of 255
 * characters not including the nul.
 *
 * @param str  The string to check
 *
 * @return true if the string is a well-formed interface name
 */
bool IsLegalInterfaceName(const char* str);

/**
 * Checks if the string passed is a well-formed error name.
 *
 * An error name has the same format as an interface name.
 *
 * @param str  The string to check
 *
 * @return true if the string is a well-formed error name
 *
 * @see IsLegalInterfaceName
 */
bool IsLegalErrorName(const char* str);

/**
 * Checks if the string passed is a well-formed member name.
 *
 * Member names contain only alphanumeric characters and underscores and must not begin
 * with a digit. They are nul terminated and have a maximum length of 255 characters not
 * including the nul.
 *
 * @param str  The string to check
 *
 * @return true if the string is a well-formed member name
 */
bool IsLegalMemberName(const char* str);

/**
 * Generate a well-known bus name from an object path.
 *
 * The well-known name is generated by removing the leading slash and replacing all
 * other slashes by periods. Returns an empty string if the parameter is not a legal
 * object path.
 *
 * For example: @c /org/alljoyn/Bus/Test ---> @c org.alljoyn.Bus.Test
 *
 * @param str  The object path to convert
 *
 * @return A bus name
 */
qcc::String BusNameFromObjPath(const char* str);

typedef std::multimap<qcc::String, qcc::String> MatchMap;

/**
 * Parse match rule arg strings
 *
 * @param match            Match rule string of form &lt;key0&gt;=&lt;val0&gt;,&lt;key1&gt;=&lt;val1&gt;
 * @param[out] matchMap    A map of the key, value pairs.
 * @return ER_OK if successful.
 */
QStatus ParseMatchRule(const qcc::String& match,
                       MatchMap& matchMap);

/**
 * Simple pattern matching function that supports '*' and '?' only.  Returns a
 * bool in the sense of "a difference between the string and pattern exists."
 * This is so it works like fnmatch or strcmp, which return a 0 if a match is
 * found.
 *
 * We require an actual character match and do not consider an empty string
 * something that can match or be matched.
 *
 * @param[in] str The string
 * @param[in] pat The pattern
 *
 * @return true if does not match, false if it does
 */
bool WildcardMatch(qcc::String str, qcc::String pat);

}

#endif
