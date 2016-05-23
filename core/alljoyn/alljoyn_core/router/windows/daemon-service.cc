/**
 * @file
 * daemon-service - Wrapper to allow daemon to be built as a DLL
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

#define DAEMONLIBRARY_EXPORTS
#include "DaemonLib.h"

// Standard Windows DLL entry point
BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD ul_reason_for_call,
                      LPVOID lpReserved
                      )
{
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

// Global buffer to hold log file path when started as a Windows Service
char g_logFilePathName[MAX_PATH];
bool g_isManaged = false;

// forward reference

bool IsWhiteSpace(char c)
{
    if ((c == ' ') || (c == '\t') || (c == '\n') || (c == '\r')) {
        return true;
    }
    return false;
}

// convert string passed to DaemonMain into argc, argv that can be passed to the
// LoadDaemon function to start the daemon.
DAEMONLIBRARY_API void DaemonMain(wchar_t* cmd)
{
    if (!cmd || !*cmd || wcslen(cmd) >= 2000) {         // make sure it fits
        printf("Bad command string\n");
        return;
    }
    char cmdLine[2000];     // on the stack
    char* tempPtrs[20];     // arbitrary limit of 20!

    sprintf_s(cmdLine, 2000, "%S", cmd);
    char* src = cmdLine;

    int i = 0;   // count the arguments
    char workingBuffer[MAX_PATH];     // on the stack
    int cnt = (int)strlen(cmdLine);
    // parse the first 20 arguments
    while (cnt > 0 && i < 20) {
        char* dest = workingBuffer;
        while (*src && !IsWhiteSpace(*src)) {
            // The largest any single argument can be is MAX_PATH characters any
            // thing larger is an error.
            if (dest - workingBuffer == MAX_PATH) {
                printf("Bad command string\n");
                return;
            }
            *dest++ = *src++;
            cnt--;
        }
        *dest = (char)0;         // terminate current arg
        size_t len = strlen(workingBuffer) + 1;
        tempPtrs[i] = new char[len];
        memcpy((void*)tempPtrs[i], (const void*)workingBuffer, len);
        while (*src && IsWhiteSpace(*src)) {       // skip white space
            src++;
            cnt--;
        }
        i++;
    }
    if (!i) {
        printf("Empty command string\n");
        return;
    }

    // the code can only parse 20 arguments and arguments were left unparsed.
    if (cnt > 0 && i == 20) {
        printf("Too many command arguments\n");
        return;
    }
    // now create argc and argv
    char** argv = new char*[i];
    for (int ii = 0; ii < i; ii++)
        argv[ii] = tempPtrs[ii];
    LoadDaemon(i, argv);
    for (int ii = 0; ii < i; ii++)
        delete[] argv[ii];
    delete[] argv;
}

DAEMONLIBRARY_API void SetLogFile(wchar_t* str)
{
    sprintf_s(g_logFilePathName, MAX_PATH, "%S", str);
    g_isManaged = true;
}