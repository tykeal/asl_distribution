/**
 * @file
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

/**
 * Per-module definition of the current module for debug logging.  Must be defined
 * prior to first inclusion of aj_debug.h
 */
#define AJ_MODULE TARGET_NVRAM

#include <ajtcl/aj_nvram.h>
#include <ajtcl/aj_debug.h>
#include "../../aj_target_nvram.h"

/**
 * Turn on per-module debug printing by setting this variable to non-zero value
 * (usually in debugger).
 */
#ifndef NDEBUG
uint8_t dbgTARGET_NVRAM = 0;
#endif

uint8_t AJ_EMULATED_NVRAM[AJ_NVRAM_SIZE];
uint8_t* AJ_NVRAM_BASE_ADDRESS;

extern void AJ_NVRAM_Layout_Print();

#define NV_FILE "ajtcl.nvram"

const char* nvFile = NV_FILE;

void AJ_SetNVRAM_FilePath(const char* path)
{
    if (path) {
        nvFile = path;
    }
}

void AJ_NVRAM_Init()
{
    AJ_NVRAM_BASE_ADDRESS = AJ_EMULATED_NVRAM;
    _AJ_LoadNVFromFile();
    if (*((uint32_t*)AJ_NVRAM_BASE_ADDRESS) != AJ_NV_SENTINEL) {
        _AJ_NVRAM_Clear();
        _AJ_StoreNVToFile();
    }
}

void _AJ_NV_Write(void* dest, const void* buf, uint16_t size)
{
    memcpy(dest, buf, size);
    _AJ_StoreNVToFile();
}

void _AJ_NV_Move(void* dest, const void* buf, uint16_t size)
{
    memmove(dest, buf, size);
    _AJ_StoreNVToFile();
}

void _AJ_NV_Read(void* src, void* buf, uint16_t size)
{
    memcpy(buf, src, size);
}

void _AJ_NVRAM_Clear()
{
    memset((uint8_t*)AJ_NVRAM_BASE_ADDRESS, INVALID_DATA_BYTE, AJ_NVRAM_SIZE);
    *((uint32_t*)AJ_NVRAM_BASE_ADDRESS) = AJ_NV_SENTINEL;
    _AJ_StoreNVToFile();
}


static AJ_Status _AJ_LoadNVFromFile()
{
    FILE* f = fopen(nvFile, "rb");
    if (f == NULL) {
        AJ_AlwaysPrintf(("Error: AJ_LoadNVFromFile(\"%s\") failed\n", nvFile));
        return AJ_ERR_FAILURE;
    }

    memset(AJ_NVRAM_BASE_ADDRESS, INVALID_DATA_BYTE, AJ_NVRAM_SIZE);
    fread(AJ_NVRAM_BASE_ADDRESS, AJ_NVRAM_SIZE, 1, f);
    fclose(f);
    return AJ_OK;
}

AJ_Status _AJ_StoreNVToFile()
{
    FILE* f = fopen(nvFile, "wb");
    if (!f) {
        AJ_AlwaysPrintf(("Error: AJ_StoreNVToFile(\"%s\") failed\n", nvFile));
        return AJ_ERR_FAILURE;
    }

    fwrite(AJ_NVRAM_BASE_ADDRESS, AJ_NVRAM_SIZE, 1, f);
    fclose(f);
    return AJ_OK;
}

// Compact the storage by removing invalid entries
AJ_Status _AJ_CompactNVStorage()
{
    uint16_t capacity = 0;
    uint16_t id = 0;
    uint16_t* data = (uint16_t*)(AJ_NVRAM_BASE_ADDRESS + SENTINEL_OFFSET);
    uint8_t* writePtr = (uint8_t*)data;
    uint16_t entrySize = 0;
    uint16_t garbage = 0;
    //AJ_NVRAM_Layout_Print();
    while ((uint8_t*)data < (uint8_t*)AJ_NVRAM_END_ADDRESS && *data != INVALID_DATA) {
        id = *data;
        capacity = *(data + 1);
        entrySize = ENTRY_HEADER_SIZE + capacity;
        if (id != INVALID_ID) {
            _AJ_NV_Move(writePtr, data, entrySize);
            writePtr += entrySize;
        } else {
            garbage += entrySize;
        }
        data += entrySize >> 1;
    }

    memset(writePtr, INVALID_DATA_BYTE, garbage);
    _AJ_StoreNVToFile();
    //AJ_NVRAM_Layout_Print();
    return AJ_OK;
}
