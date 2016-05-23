/*******************************************************************************
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
#ifndef _TEST_CLIENTSETUP_H
#define _TEST_CLIENTSETUP_H


#include <qcc/String.h>
#include <qcc/Util.h>
#include <qcc/Environ.h>
#include <qcc/Debug.h>




#include <alljoyn/BusAttachment.h>
#include <alljoyn/DBusStd.h>
#include <alljoyn/version.h>


#include <alljoyn/Status.h>

#include <stdio.h>
#include <vector>

#define QCC_MODULE "ALLJOYN"

using namespace std;
using namespace qcc;
using namespace ajn;

class ClientSetup : public MessageReceiver {
  public:
    ClientSetup(const char* default_bus_addr, const char* wellKnownName);

    BusAttachment* getClientMsgBus();
    qcc::String getClientArgs();

    QStatus MethodCall(int noOfCalls, int type);
    QStatus AsyncMethodCall(int noOfCalls, int type);
    void AsyncCallReplyHandler(Message& msg, void* context);
    QStatus SignalHandler(int noOfCalls, int type);
    void MySignalHandler(const InterfaceDescription::Member*member,
                         const char* sourcePath,
                         Message& msg);

    void MySignalHandler2(const InterfaceDescription::Member*member,
                          const char* sourcePath,
                          Message& msg);
    int getSignalFlag();
    void setSignalFlag(int flag);

    const char* getClientInterfaceName() const;
    const char* getClientDummyInterfaceName1() const;
    const char* getClientDummyInterfaceName2() const;
    const char* getClientDummyInterfaceName3() const;
    const char* getClientObjectPath() const;

    const char* getClientValuesInterfaceName() const;
    const char* getClientValuesDummyInterfaceName1() const;
    const char* getClientValuesDummyInterfaceName2() const;
    const char* getClientValuesDummyInterfaceName3() const;
  private:
    Event waitEvent;
    int g_Signal_flag;
    BusAttachment clientMsgBus;
    qcc::String clientArgs;
    qcc::String wellKnownName;
};

#endif
