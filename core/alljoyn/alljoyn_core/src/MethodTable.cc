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
/**
 * @file
 *
 * This file defines the method hash table class
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

#include <qcc/platform.h>

#include "MethodTable.h"

/** @internal */
#define QCC_MODULE "ALLJOYN"

using namespace qcc;
using namespace std;

namespace ajn {

MethodTable::~MethodTable()
{
    lock.Lock(MUTEX_CONTEXT);
    MapType::iterator iter = hashTable.begin();
    while (iter != hashTable.end()) {
        delete iter->second;
        ++iter;
    }

    hashTable.clear();
    lock.Unlock(MUTEX_CONTEXT);
}

void MethodTable::Add(BusObject* object,
                      MessageReceiver::MethodHandler func,
                      const InterfaceDescription::Member* member,
                      void* context)
{
    Entry* entry = new Entry(object, func, member, context);
    lock.Lock(MUTEX_CONTEXT);
    hashTable[Key(object->GetPath(), entry->ifaceStr.empty() ? NULL : entry->ifaceStr.c_str(), member->name.c_str())] = entry;

    /* Method calls don't require an interface so we need to add an entry with a NULL interface */
    if (!entry->ifaceStr.empty()) {
        // specification states "if there are multiple properties on an object
        // with the same name, the results are undefined." We choose to only
        // use the first member that was added.
        if (hashTable.find(Key(object->GetPath(), NULL, member->name.c_str())) == hashTable.end()) {
            hashTable[Key(object->GetPath(), NULL, member->name.c_str())] = new Entry(*entry);
        }
    }
    lock.Unlock(MUTEX_CONTEXT);
}

MethodTable::SafeEntry* MethodTable::Find(const char* objectPath,
                                          const char* iface,
                                          const char* methodName)
{
    SafeEntry* entry = NULL;
    Key key(objectPath, iface, methodName);
    lock.Lock(MUTEX_CONTEXT);
    MapType::iterator iter = hashTable.find(key);
    if (iter != hashTable.end()) {
        entry = new SafeEntry();
        entry->Set(iter->second);
    }
    lock.Unlock(MUTEX_CONTEXT);
    return entry;
}

void MethodTable::RemoveAll(BusObject* object)
{
    MapType::iterator iter;
    /*
     * Iterate over all entries deleting all entries that reference the object
     */
    lock.Lock(MUTEX_CONTEXT);
    iter = hashTable.begin();
    while (iter != hashTable.end()) {
        if (iter->second->object == object) {
            Entry* deleteMe = iter->second;
            hashTable.erase(iter);
            delete deleteMe;
            iter = hashTable.begin();
        } else {
            ++iter;
        }
    }
    lock.Unlock(MUTEX_CONTEXT);
}

void MethodTable::AddAll(BusObject* object)
{
    object->InstallMethods(*this);
}

}

