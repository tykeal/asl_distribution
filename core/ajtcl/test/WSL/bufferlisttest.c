/**
 * @file Unit tests for AJ_WSL buffer list.
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

#ifdef __cplusplus
extern "C" {
#endif



#define AJ_MODULE WSL_UNIT_TEST

#include <ajtcl/aj_target.h>

#include "../../src/wsl/aj_buf.h"
#include "../../src/wsl/aj_wsl_htc.h"
#include "../../src/wsl/aj_wsl_spi.h"
#include "../../src/wsl/aj_wsl_wmi.h"
#include "../../src/wsl/aj_wsl_net.h"
#include <ajtcl/aj_debug.h>


/**
 * Turn on per-module debug printing by setting this variable to non-zero value
 * (usually in debugger).
 */
#ifndef NDEBUG
uint8_t dbgWSL_UNIT_TEST = 5;
#endif

static void run_buflist_external(const struct test_case* test)
{

    uint8_t externA[10];
    uint8_t externB[10];
    /*
     * verify the buffer list management
     */
    AJ_BufList* list1 = AJ_BufListCreate();
    AJ_BufNode* pNode1 = AJ_BufListCreateNodeExternalBuffer((uint8_t*)&externA, sizeof(externA));
    AJ_BufNode* pNode2 = AJ_BufListCreateNodeExternalBuffer((uint8_t*)&externB, sizeof(externB));

    AJ_AlwaysPrintf(("\n\n**************\nTEST:  %s\n\n", __FUNCTION__));

    memset(pNode1->buffer, 0x1, pNode1->length);
    memset(pNode2->buffer, 0x2, pNode2->length);

    AJ_BufListPushHead(list1, pNode1);
    AJ_BufListPushTail(list1, pNode2);

    AJ_BufNodeIterate(AJ_BufListNodePrint, list1, NULL);
    AJ_BufNodeIterate(AJ_BufListNodePrintDump, list1, NULL);

    AJ_BufListFree(list1, 1);


}


static void run_buflist_coalesce(const struct test_case* test)
{

    /*
     * verify the buffer list management
     */
    AJ_BufList* list1 = AJ_BufListCreate();
    AJ_BufNode* pNode1 = AJ_BufListCreateNode(100);
    AJ_BufNode* pNode2 = AJ_BufListCreateNode(200);

    AJ_AlwaysPrintf(("\n\n**************\nTEST:  %s\n\n", __FUNCTION__));

    memset(pNode1->buffer, 0x1, pNode1->length);
    memset(pNode2->buffer, 0x2, pNode2->length);

    AJ_BufListPushHead(list1, pNode1);
    AJ_BufListPushTail(list1, pNode2);

    AJ_BufNodeIterate(AJ_BufListNodePrint, list1, NULL);
    AJ_BufNodeIterate(AJ_BufListNodePrintDump, list1, NULL);

    AJ_BufListFree(list1, 1);



    // Test squeezing together a few buffer nodes in a list.
    AJ_AlwaysPrintf(("%s", "\n\nTEST: Coalesce Start\n"));
    {
        AJ_BufList* list3 = AJ_BufListCreate();

        AJ_BufNode* pNodeA = AJ_BufListCreateNode(8);
        AJ_BufNode* pNodeB = AJ_BufListCreateNode(8);
        AJ_BufNode* pNodeC = AJ_BufListCreateNode(8);
        AJ_BufNode* pNodeD = AJ_BufListCreateNode(8);
        memset(pNodeA->buffer, 0xA1, 8);
        memset(pNodeB->buffer, 0xB2, 8);
        memset(pNodeC->buffer, 0xC3, 8);
        memset(pNodeD->buffer, 0xD4, 8);

        AJ_BufListPushHead(list3, pNodeA);
        AJ_BufListPushTail(list3, pNodeB);
        AJ_BufListPushTail(list3, pNodeC);
        AJ_BufListPushTail(list3, pNodeD);

        AJ_BufNodeIterate(AJ_BufListNodePrintDump, list3, NULL);

        AJ_AlwaysPrintf(("%s", "\n\nTEST: coalesce the head twice, then dump\n"));
        AJ_BufListCoalesce(list3->head);
        AJ_BufListCoalesce(list3->head);
        AJ_BufNodeIterate(AJ_BufListNodePrintDump, list3, NULL);


        AJ_AlwaysPrintf(("%s", "\n\nTEST: Next pull 16 bytes then dump\n"));

        AJ_BufListPullBytes(list3, 4);
        AJ_BufListPullBytes(list3, 4);
        AJ_BufListPullBytes(list3, 8);
        AJ_BufNodeIterate(AJ_BufListNodePrintDump, list3, NULL);
        AJ_AlwaysPrintf(("%s", "\n\nTEST: PULL BYTES 16 end\n"));

        AJ_BufListFree(list3, 1);
    }
    AJ_AlwaysPrintf(("%s", "\nTEST: Coalesce End\n"));
}


/**
 * Run buffer list tests.
 */
int main(void)
{
    AJ_WSL_ModuleInit();

    toTarget.fakeWireCurr = toTarget.fakeWireBuffer;
    toTarget.fakeWireRead = toTarget.fakeWireBuffer;
    toTarget.fakeWireWrite = toTarget.fakeWireBuffer;
    fromTarget.fakeWireCurr = fromTarget.fakeWireBuffer;
    fromTarget.fakeWireRead = fromTarget.fakeWireBuffer;
    fromTarget.fakeWireWrite = fromTarget.fakeWireBuffer;

    run_buflist_external(NULL);
    run_buflist_coalesce(NULL);

}


#ifdef __cplusplus
}
#endif
