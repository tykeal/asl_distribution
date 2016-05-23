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
//----------------------------------------------------------------------------------------------
#include "AllJoynBusAPI.h"

static FPPrintCallback ManagedOutput = NULL;
static FPJoinedCallback JoinNotifier = NULL;

// ================------------------------------------------------------------
// define a printf type function for feeding the managed output stream
#define BUFFER_SIZE 2048
static char BUFFER[BUFFER_SIZE];
// arbitrary size
void NotifyUser(NotifyType informType, const char* format, ...)
{
    va_list ap;
    va_start(ap, format);
    vsprintf_s(BUFFER, BUFFER_SIZE, format, ap);
    va_end(ap);
    if (NULL != ManagedOutput) {
        int i = strlen(BUFFER);
        int t = (int) informType;
        ManagedOutput(BUFFER, i,  t);
    }
}

// AllJoynConnection ------------------------------------------------------------
// singleton connection object
static AllJoynConnection* s_connection = NULL;

// copies the const NAME_PREFIX to marshaller
ALLJOYN_API void __stdcall GetNamePrefix(char*arg, int& maxchars)
{
    strcpy_s(arg, maxchars, NAME_PREFIX);
    maxchars = strlen(NAME_PREFIX);
}

// set the managed output stream callback
ALLJOYN_API void __stdcall SetLocalOutputStream(FPPrintCallback callback)
{
    ManagedOutput = callback;
}

// set the event handler for the joined event
ALLJOYN_API void __stdcall SetJoinListener(FPJoinedCallback callback)
{
    JoinNotifier = callback;
}

// the bus initialization and configuration function
ALLJOYN_API void __stdcall ConnectToAllJoyn(char* identity, bool& asAdvertiser)
{
    if ((NULL == ManagedOutput) || (NULL == JoinNotifier)) {
        MessageBox(NULL, L"Callbacks not set", L"Alljoyn", MB_OK);
    }
    if (NULL == s_connection) {    // create on demand
        s_connection = new AllJoynConnection(*ManagedOutput, *JoinNotifier);  // , *QueryCallback);

    }
    s_connection->Connect(identity, asAdvertiser);
//	if( s_connection->IsConnected() )
//	{
//		s_connection->CreateBusObjects();
//	}
    asAdvertiser = s_connection->IsConnected();
}


ALLJOYN_API void __stdcall DisconnectFromAllJoyn(void)
{
    if (NULL != s_connection) {
        delete s_connection;
    }
    s_connection = NULL;
}

ALLJOYN_API void __stdcall MessageOut(char*arg, int& maxchars)
{
    const int bufsize = 1024;
    static char outbuf[bufsize];
    strcpy_s(outbuf, bufsize, arg);
    outbuf[maxchars] = 0;
    ChatObject* co = s_connection->GetChatObject();
    QStatus status = co->SendChatSignal(outbuf);
}

// XferObject -----------------------------------------------------------------
ALLJOYN_API void __stdcall SetIncomingXferInterface(FPQueryCallback qcb, FPXferCallback xcb)
{
    XferObject* xo = s_connection->GetXferObject();
    xo->SetQueryCallback(qcb);
    xo->SetXferCallback(xcb);
}

ALLJOYN_API void __stdcall CreateXferProxyFor(char* name, int& index)
{
    index = s_connection->CreateProxy(XFER_SERVICE_INTERFACE_NAME, XFER_SERVICE_OBJECT_PATH, name);
}

ALLJOYN_API void __stdcall ReleaseXferProxy(char* name, int& index)
{
    s_connection->ReleaseProxy(index);
}

ALLJOYN_API void __stdcall QueryRemoteXfer(int index, char* filename, int& filesize, int& accept)
{
    NotifyUser(MSG_STATUS, "%s", filename);
    ProxyBusObject* pbo = s_connection->FetchProxy(index);

    Message reply(*s_connection->busAttachment);
    MsgArg inputs[2];
    inputs[0].Set("s", filename);
    inputs[1].Set("i", filesize);

    // give the remote user 30 secomds to respond
    QStatus status = pbo->MethodCall(XFER_SERVICE_INTERFACE_NAME, "query", inputs, 2, reply, 30000);
    if (status == ER_OK) {
        accept = reply->GetArg(0)->v_int32;
        if (0 != accept) {
            // TODO: if negotiated segment size returned
            // NotifyUser(MSG_STATUS, "Accepted %d %d", filesize, accept);
            NotifyUser(MSG_STATUS, "Accepted");
        } else {
            NotifyUser(MSG_STATUS, "Rejected");
        }
    } else {
        NotifyUser(MSG_ERROR, "%s", QCC_StatusText(status));
//	    if( status == ER_BUS_REPLY_IS_ERROR_MESSAGE)
//			if( NULL != reply->GetArg(0)->v_string.str )
//				NotifyUser(MSG_ERROR, "%s", reply->GetArg(0)->v_string.str);
    }
}

ALLJOYN_API void __stdcall InitiateXfer(int proxyIndex, int segmentSize, int nSegments, bool& success)
{
    ProxyBusObject* pbo = s_connection->FetchProxy(proxyIndex);
    Message reply(*s_connection->busAttachment);
    MsgArg inputs[2];
    inputs[0].Set("i", segmentSize);
    inputs[1].Set("i", nSegments);
    // 5 seconds to respond
    QStatus status = pbo->MethodCall(XFER_SERVICE_INTERFACE_NAME, "initiate", inputs, 2, reply, 5000);
    NotifyUser(MSG_SYSTEM, "Initiated transfer");
    if (status == ER_OK) {
        success = true;
    } else {
        success = false;
    }
}

//("receive", "ayii",  "i", "segment, serialNum. segSize , success ", 0);
ALLJOYN_API void __stdcall TransferSegment(int proxyIndex, void* pv, int serialNum, int segmentSize, bool& success)
{
    ProxyBusObject* pbo = s_connection->FetchProxy(proxyIndex);
    NotifyUser(MSG_SYSTEM, "Transfer %d", serialNum);
    Message reply(*s_connection->busAttachment);
    MsgArg inputs[3];
    uint8_t* bytes = (uint8_t*)pv;
//	for( int i=0; i < 7 ; i++)
//	{
//		NotifyUser(MSG_ERROR, "Send %d", bytes[i] );
//	}

//	uint8_t bytes[8] = {1,2,3,4,5,6,7,8};
    inputs[0].Set("ay", segmentSize, bytes);
    inputs[1].Set("i", serialNum);
    inputs[2].Set("i", segmentSize);
    // 5 seconds to respond
    QStatus status = pbo->MethodCall(XFER_SERVICE_INTERFACE_NAME, "receive", inputs, 3, reply, 5000);
    NotifyUser(MSG_SYSTEM, "Initiated transfer");
    if (status == ER_OK) {
        success = reply->GetArg(0)->v_int32;
    } else {
        success = false;
    }

}

ALLJOYN_API void __stdcall SetPendingTransferIn(char* filename, bool& success)
{
    XferObject* xo = s_connection->GetXferObject();
    xo->SetSaveAsFilename(filename);
    success = true;
}

ALLJOYN_API void __stdcall GetRemoteTransferStatus(int proxyIndex, int& state, int& errorCode)
// 0 - available 1 - busy -1 error
{
    ProxyBusObject* pbo = s_connection->FetchProxy(proxyIndex);
    NotifyUser(MSG_SYSTEM, "Check Status");
    Message reply(*s_connection->busAttachment);
    MsgArg inputs[1];
    int dummy = 0;
    inputs[0].Set("i", dummy);
    QStatus status = pbo->MethodCall(XFER_SERVICE_INTERFACE_NAME, "status", inputs, 1, reply, 5000);
    if (status == ER_OK) {
        state = reply->GetArg(0)->v_int32;
        if (state == -1) {
            status = pbo->MethodCall(XFER_SERVICE_INTERFACE_NAME, "error", inputs, 1, reply, 5000);
            if (status == ER_OK) {
                errorCode = reply->GetArg(0)->v_int32;
            }
        }
    }
}


ALLJOYN_API void __stdcall EndRemoteTransfer(int proxyIndex, bool& success)
{
    ProxyBusObject* pbo = s_connection->FetchProxy(proxyIndex);
    NotifyUser(MSG_SYSTEM, "End Transfer");
    Message reply(*s_connection->busAttachment);
    MsgArg inputs[1];
    int close = 1;
    inputs[0].Set("i", close);
    QStatus status = pbo->MethodCall(XFER_SERVICE_INTERFACE_NAME, "close", inputs, 1, reply, 5000);
    if (status == ER_OK) {
        success = true;
    } else {
        success = false;
    }
}

