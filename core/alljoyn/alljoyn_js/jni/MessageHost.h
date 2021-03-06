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
#ifndef _MESSAGEHOST_H
#define _MESSAGEHOST_H

#include "BusAttachment.h"
#include "ScriptableObject.h"
#include <alljoyn/Message.h>
#include <alljoyn/MsgArg.h>
#include <qcc/String.h>

class _MessageHost : public ScriptableObject {
  public:
    _MessageHost(Plugin& plugin, BusAttachment& busAttachment, ajn::Message& message);
    virtual ~_MessageHost();

  protected:
    BusAttachment busAttachment;
    ajn::Message message;

    bool getSender(NPVariant* npresult);
    bool getDestination(NPVariant* npresult);
    bool getFlags(NPVariant* npresult);
    bool getInterfaceName(NPVariant* npresult);
    bool getObjectPath(NPVariant* npresult);
    bool getAuthMechanism(NPVariant* npresult);
    bool getIsUnreliable(NPVariant* npresult);
    bool getMemberName(NPVariant* npresult);
    bool getSignature(NPVariant* npresult);
    bool getSessionId(NPVariant* npresult);
    bool getTimestamp(NPVariant* npresult);
};

typedef qcc::ManagedObj<_MessageHost> MessageHost;

#endif // _MESSAGEHOST_H
