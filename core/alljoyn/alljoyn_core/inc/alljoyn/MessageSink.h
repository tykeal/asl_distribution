/**
 * @file
 * Abstract interface implemented by objects that wish to consume Message Bus
 * messages.
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
#ifndef _ALLJOYN_MESSAGESINK_H
#define _ALLJOYN_MESSAGESINK_H

#ifndef __cplusplus
#error Only include MessageSink.h in C++ code.
#endif

#include <qcc/platform.h>

#include <alljoyn/Message.h>

#include <alljoyn/Status.h>

namespace ajn {

/**
 * Abstract interface implemented by objects that wish to consume Message Bus
 * messages.
 */
class MessageSink {
  public:
    /**
     * Virtual destructor for derivable class.
     */
    virtual ~MessageSink() { }

    /**
     * Consume a message bus message.
     *
     * @param msg   Message to be consumed.
     * @return #ER_OK if successful.
     */
    virtual QStatus PushMessage(Message& msg) = 0;
};

}

#endif
