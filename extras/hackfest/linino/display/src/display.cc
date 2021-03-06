/**
 * @file
 * Arduino LOL shield communications
 */

/******************************************************************************
 * Copyright (c) 2014, AllSeen Alliance. All rights reserved.
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

#include <algorithm>

#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <aj_tutorial/display.h>

#if !defined(HOST_BUILD)
#include <aj_tutorial/smsg.h>
#endif

#if defined(HOST_BUILD)
#define dbg 1
#else
#define dbg 0
#endif

using namespace std;

static const uint16_t font9x14[][9] = {
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000 }, // ' '
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x3ff4, 0x0000, 0x0000, 0x0000, 0x0000 }, // '!'
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000 }, // '"'
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000 }, // '#'
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000 }, // '$'
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000 }, // '%'
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000 }, // '^'
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000 }, // '''
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000 }, // '('
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000 }, // ')'
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000 }, // '*'
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000 }, // '+'
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000 }, // ','
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000 }, // '-'
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000 }, // '.'
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000 }, // '/'
    { 0x0ff0, 0x1808, 0x2404, 0x2204, 0x2104, 0x2084, 0x2044, 0x1028, 0x0ff0 }, // '0'
    { 0x0004, 0x0004, 0x0004, 0x0004, 0x3ffc, 0x1004, 0x0804, 0x0404, 0x0204 }, // '1'
    { 0x1804, 0x2404, 0x2204, 0x2104, 0x2084, 0x2044, 0x2024, 0x1014, 0x080c }, // '2'
    { 0x0e70, 0x1088, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x0000, 0x0000 }, // '3'
    { 0x3ffc, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x0100, 0x3f00 }, // '4'
    { 0x2070, 0x2088, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x2108, 0x3f10 }, // '5'
    { 0x0030, 0x0048, 0x0084, 0x0084, 0x0084, 0x0084, 0x0044, 0x0008, 0x3ff0 }, // '6'
    { 0x3c00, 0x2200, 0x2100, 0x2080, 0x2040, 0x2020, 0x2010, 0x2008, 0x2004 }, // '7'
    { 0x0810, 0x1428, 0x2244, 0x2184, 0x2084, 0x2184, 0x2244, 0x1428, 0x0810 }, // '8'
    { 0x0ffc, 0x1000, 0x2200, 0x2100, 0x2100, 0x2100, 0x1100, 0x0a00, 0x0400 }, // '9'
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000 }, // ':'
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000 }, // ';'
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000 }, // '<'
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000 }, // '='
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000 }, // '>'
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000 }, // '?'
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000 }, // '@'
    { 0x03fc, 0x0500, 0x0900, 0x1100, 0x2100, 0x1100, 0x0d00, 0x0300, 0x01fc }, // 'A'
    { 0x0e30, 0x1148, 0x2084, 0x2084, 0x2084, 0x2084, 0x2084, 0x2084, 0x3ffc }, // 'B'
    { 0x0810, 0x1008, 0x2004, 0x2004, 0x2004, 0x2004, 0x2004, 0x1008, 0x0ff0 }, // 'C'
    { 0x07e0, 0x0810, 0x1008, 0x2004, 0x2004, 0x2004, 0x2004, 0x2004, 0x3ffc }, // 'D'
    { 0x2084, 0x2084, 0x2084, 0x2084, 0x2084, 0x2084, 0x2084, 0x2084, 0x3ffc }, // 'E'
    { 0x2100, 0x2100, 0x2100, 0x2100, 0x2100, 0x2100, 0x2100, 0x2100, 0x3ffc }, // 'F'
    { 0x0830, 0x1048, 0x2084, 0x2084, 0x2004, 0x2004, 0x2004, 0x1008, 0x0ff0 }, // 'G'
    { 0x3ffc, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x3ffc }, // 'H'
    { 0x2004, 0x2004, 0x2004, 0x2004, 0x3ffc, 0x2004, 0x2004, 0x2004, 0x2004 }, // 'I'
    { 0x3ff0, 0x0008, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0008, 0x0070 }, // 'J'
    { 0x0000, 0x2004, 0x1008, 0x0810, 0x0420, 0x0240, 0x0180, 0x0080, 0x3ffc }, // 'K'
    { 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x3ffc }, // 'L'
    { 0x3ffc, 0x1000, 0x0800, 0x0400, 0x0200, 0x0400, 0x0800, 0x1000, 0x3ffc }, // 'M'
    { 0x3ffc, 0x0008, 0x0030, 0x0040, 0x0180, 0x0200, 0x0c00, 0x1000, 0x3ffc }, // 'N'
    { 0x07e0, 0x0810, 0x300c, 0x2004, 0x2004, 0x2004, 0x300c, 0x0810, 0x07e0 }, // 'O'
    { 0x0400, 0x0a00, 0x1100, 0x2100, 0x2100, 0x2100, 0x2100, 0x2100, 0x3ffc }, // 'P'
    { 0x07f4, 0x0808, 0x3014, 0x2024, 0x2004, 0x2004, 0x3014, 0x0828, 0x07f0 }, // 'Q'
    { 0x0c04, 0x1208, 0x2110, 0x2120, 0x2140, 0x2180, 0x2100, 0x2100, 0x3ffc }, // 'R'
    { 0x0870, 0x1088, 0x2104, 0x2104, 0x2104, 0x2104, 0x2104, 0x1108, 0x0e10 }, // 'S'
    { 0x2000, 0x2000, 0x2000, 0x2000, 0x3ffc, 0x2000, 0x2000, 0x2000, 0x2000 }, // 'T'
    { 0x3ff0, 0x0008, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0008, 0x3ff0 }, // 'U'
    { 0x3fc0, 0x0020, 0x0010, 0x0008, 0x000c, 0x0008, 0x0010, 0x0020, 0x3fc0 }, // 'V'
    { 0x3ffc, 0x0008, 0x0010, 0x0020, 0x0040, 0x0020, 0x0010, 0x0008, 0x3ffc }, // 'W'
    { 0x2004, 0x1818, 0x0620, 0x0140, 0x0080, 0x0140, 0x0620, 0x1818, 0x2004 }, // 'X'
    { 0x3800, 0x0400, 0x0200, 0x0100, 0x00fc, 0x0100, 0x0200, 0x0400, 0x3800 }, // 'Y'
    { 0x3004, 0x2804, 0x2404, 0x2204, 0x2104, 0x2084, 0x2044, 0x2024, 0x201c }, // 'Z'
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000 }, // '['
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000 }, // '\'
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000 }, // ']'
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000 }, // '^'
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000 }, // '_'
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000 }, // '`'
    { 0x01fc, 0x0248, 0x0484, 0x0484, 0x0484, 0x0484, 0x0484, 0x0484, 0x0078 }, // 'a'
    { 0x0078, 0x0084, 0x0084, 0x0084, 0x0084, 0x0084, 0x0084, 0x0048, 0x3ffc }, // 'b'
    { 0x0048, 0x0084, 0x0084, 0x0084, 0x0084, 0x0084, 0x0084, 0x0084, 0x0078 }, // 'c'
    { 0x3ffc, 0x0048, 0x0084, 0x0084, 0x0084, 0x0084, 0x0084, 0x0084, 0x0078 }, // 'd'
    { 0x0068, 0x00a4, 0x00a4, 0x00a4, 0x00a4, 0x00a4, 0x00a4, 0x00a4, 0x0078 }, // 'e'
    { 0x2200, 0x2200, 0x2200, 0x2200, 0x1ffc, 0x0200, 0x0200, 0x0200, 0x0200 }, // 'f'
    { 0x007e, 0x0089, 0x0085, 0x0085, 0x0085, 0x0085, 0x0085, 0x0085, 0x0078 }, // 'g'
    { 0x007c, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0040, 0x1ffc }, // 'h'
    { 0x0004, 0x0004, 0x0004, 0x0004, 0x02fc, 0x0084, 0x0084, 0x0004, 0x0004 }, // 'i'
    { 0x02fc, 0x0082, 0x0081, 0x0081, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001 }, // 'j'
    { 0x0084, 0x0084, 0x0084, 0x0048, 0x0048, 0x0048, 0x0030, 0x0030, 0x3ffc }, // 'k'
    { 0x0004, 0x0004, 0x0004, 0x0004, 0x3ffc, 0x2004, 0x2004, 0x0004, 0x0004 }, // 'l'
    { 0x007c, 0x0080, 0x0080, 0x0080, 0x007c, 0x0080, 0x0080, 0x0000, 0x00fc }, // 'm'
    { 0x007c, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0040, 0x00fc }, // 'n'
    { 0x0078, 0x0084, 0x0084, 0x0084, 0x0084, 0x0084, 0x0084, 0x0084, 0x0078 }, // 'o'
    { 0x0078, 0x0084, 0x0084, 0x0084, 0x0084, 0x0084, 0x0084, 0x0048, 0x00ff }, // 'p'
    { 0x00ff, 0x0048, 0x0084, 0x0084, 0x0084, 0x0084, 0x0084, 0x0084, 0x0078 }, // 'q'
    { 0x0040, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0080, 0x0040, 0x00fc }, // 'r'
    { 0x00a4, 0x00a4, 0x00a4, 0x00a4, 0x00a4, 0x00a4, 0x00a4, 0x00a4, 0x0018 }, // 's'
    { 0x0200, 0x0204, 0x0204, 0x0204, 0x3ff8, 0x0200, 0x0200, 0x0200, 0x0200 }, // 't'
    { 0x00fc, 0x0008, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x0004, 0x00f8 }, // 'u'
    { 0x00c0, 0x0020, 0x0010, 0x0008, 0x0004, 0x0008, 0x0010, 0x0020, 0x00c0 }, // 'v'
    { 0x00f0, 0x0008, 0x0004, 0x0008, 0x00f0, 0x0008, 0x0004, 0x0008, 0x00f0 }, // 'w'
    { 0x0104, 0x0088, 0x0050, 0x0020, 0x0020, 0x0020, 0x0050, 0x0088, 0x0104 }, // 'x'
    { 0x00fe, 0x0009, 0x0005, 0x0005, 0x0005, 0x0005, 0x0005, 0x0005, 0x00f9 }, // 'y'
    { 0x0084, 0x00c4, 0x00a4, 0x00a4, 0x0094, 0x0094, 0x008c, 0x008c, 0x0084 }, // 'z'
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000 }, // '{'
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000 }, // '|'
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000 }, // '}'
    { 0x0000, 0x0000, 0x0000, 0x0000, 0x0004, 0x0000, 0x0000, 0x0000, 0x0000 }  // '~'
};

bool Valid(uint8_t x, uint8_t y)
{
    return (x < 14) && (y < 9);
}


Display::Display()
{
    ClearDisplay();
}



bool Display::ClearDisplayBuffer()
{
    memset(display, 0, sizeof(display));
    return true;
}

bool Display::DrawPointBuffer(uint8_t x, uint8_t y, bool on)
{
    if (!Valid(x, y)) {
        return false;
    }

    _DrawPoint(x, y, on);
    return true;
}

const static int32_t SCALE = 1024 * 1024;

static int32_t ComputeScaledSlope(int32_t d1, int32_t d2)
{
    return (SCALE * d1) / d2;
}

static uint8_t ComputeCoordinate(int32_t slope, uint8_t c, uint8_t i1, uint8_t i2, uint8_t j1, uint8_t j2)
{
    int32_t factor = (slope < 0) ? -1 : 1;
    uint8_t b = (i1 > i2) ? j2 : j1;
    return (((slope * c) + (factor * SCALE / 2)) / SCALE) + b;
}


bool Display::DrawLineBuffer(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool on)
{
    if (!Valid(x1, y1) || !Valid(x2, y2)) {
        return false;
    }

    uint8_t x;
    uint8_t y;

    if (abs(x2 - x1) > abs(y2 - y1)) {
        // stick to integer math - Yuns don't have FP HW
        int32_t slope = ComputeScaledSlope((int32_t)y2 - y1, (int32_t)x2 - x1);
        for (x = min(x1, x2); x <= max(x1, x2); ++x) {
            y = ComputeCoordinate(slope, x, x1, x2, y1, y2);
            _DrawPoint(x, y, on);
        }
    } else {
        // stick to integer math - Yuns don't have FP HW
        int32_t slope = ComputeScaledSlope((int32_t)x2 - x1, (int32_t)y2 - y1);
        for (y = min(y1, y2); y <= max(y1, y2); ++y) {
            x = ComputeCoordinate(slope, y, y1, y2, x1, x2);
            _DrawPoint(x, y, on);
        }
    }
    return true;
}

bool Display::DrawBoxBuffer(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, bool on, bool fill)
{
    if (!Valid(x1, y1) || !Valid(x2, y2)) {
        return false;
    }

    uint16_t topbottom = 0;
    uint16_t sides = (1 << x1) | (1 << x2);
    uint8_t x;
    uint8_t y;

    for (x = min(x1, x2); x <= max(x1, x2); ++x) {
        topbottom |= 1 << x;
    }

    if (fill) {
        sides = topbottom;
    }

    if (on) {
        display[y1] |= topbottom;
        display[y2] |= topbottom;
    } else {
        topbottom = ~topbottom;
        sides = ~sides;
        display[y1] &= topbottom;
        display[y2] &= topbottom;
    }

    for (y = min(y1, y2) + 1; y <= max(y1, y2) - 1; ++y) {
        if (on) {
            display[y] |= sides;
        } else {
            display[y] &= sides;
        }
    }

    return true;
}

bool Display::DrawBitmapBuffer(const uint16_t* bitmap)
{
    memcpy(display, bitmap, sizeof(display));
    return true;
}


bool Display::DrawScoreBoardBuffer(uint8_t left, uint8_t right, bool highlightLeft, bool highlightRight)
{
    /*
     *  +-------+
     *  |       |
     *  | x xxx |
     *  | x x x |
     *  | x x x |
     *  | x xxx |
     *  | x x x |
     *  | x x x |
     *  | x xxx |
     *  |       |
     *  +-------+
     */
    static const uint16_t score[20][9] = {
        { 0x0000, 0x000e, 0x000a, 0x000a, 0x000a, 0x000a, 0x000a, 0x000e, 0x0000 }, //  0
        { 0x0000, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0000 }, //  1
        { 0x0000, 0x000e, 0x0002, 0x0002, 0x000e, 0x0008, 0x0008, 0x000e, 0x0000 }, //  2
        { 0x0000, 0x000e, 0x0002, 0x0002, 0x000e, 0x0002, 0x0002, 0x000e, 0x0000 }, //  3
        { 0x0000, 0x000a, 0x000a, 0x000a, 0x000e, 0x0002, 0x0002, 0x0002, 0x0000 }, //  4
        { 0x0000, 0x000e, 0x0008, 0x0008, 0x000e, 0x0002, 0x0002, 0x000e, 0x0000 }, //  5
        { 0x0000, 0x000e, 0x0008, 0x0008, 0x000e, 0x000a, 0x000a, 0x000e, 0x0000 }, //  6
        { 0x0000, 0x000e, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0002, 0x0000 }, //  7
        { 0x0000, 0x000e, 0x000a, 0x000a, 0x000e, 0x000a, 0x000a, 0x000e, 0x0000 }, //  8
        { 0x0000, 0x000e, 0x000a, 0x000a, 0x000e, 0x0002, 0x0002, 0x000e, 0x0000 }, //  9
        { 0x0000, 0x002e, 0x002a, 0x002a, 0x002a, 0x002a, 0x002a, 0x002e, 0x0000 }, // 10
        { 0x0000, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0000 }, // 11
        { 0x0000, 0x002e, 0x0022, 0x0022, 0x002e, 0x0028, 0x0028, 0x002e, 0x0000 }, // 12
        { 0x0000, 0x002e, 0x0022, 0x0022, 0x002e, 0x0022, 0x0022, 0x002e, 0x0000 }, // 13
        { 0x0000, 0x002a, 0x002a, 0x002a, 0x002e, 0x0022, 0x0022, 0x0022, 0x0000 }, // 14
        { 0x0000, 0x002e, 0x0028, 0x0028, 0x002e, 0x0022, 0x0022, 0x002e, 0x0000 }, // 15
        { 0x0000, 0x002e, 0x0028, 0x0028, 0x002e, 0x002a, 0x002a, 0x002e, 0x0000 }, // 16
        { 0x0000, 0x002e, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0022, 0x0000 }, // 17
        { 0x0000, 0x002e, 0x002a, 0x002a, 0x002e, 0x002a, 0x002a, 0x002e, 0x0000 }, // 18
        { 0x0000, 0x002e, 0x002a, 0x002a, 0x002e, 0x0022, 0x0022, 0x002e, 0x0000 }  // 19
    };
    uint16_t leftBitmap[9];
    uint16_t rightBitmap[9];

    left %= 20;
    right %= 20;
    memcpy(leftBitmap, score[left], sizeof(leftBitmap));
    memcpy(rightBitmap, score[right], sizeof(rightBitmap));
    for (int i = 0; i < 9; ++i) {
        if (highlightRight) {
            rightBitmap[i] ^= 0x7f;
        }
        if (highlightLeft) {
            leftBitmap[i] ^= 0x7f;
        }
        display[i] = (leftBitmap[i] << 7) | rightBitmap[i];
    }
    return true;
}

bool Display::DrawCharacterBuffer(char c) {
    if (isprint(c)) {
        return DrawBitmapBuffer(font9x14[c - ' ']);
    } else {
        return DrawBitmapBuffer(font9x14['.' - ' ']);
    }
}

bool Display::SendDisplay()
{
    uint8_t buf[sizeof(display)];
    if (dbg) printf("        +--------------+\n");
    for (size_t i = 0; i < 9; ++i) {
        // MSB
        buf[2 * i] = display[i] >> 8;
        // LSB
        buf[2 * i + 1] = display[i] & 0xff;
        if (dbg) printf("%u: %04x |", (unsigned int)i, display[i]);
        if (dbg) for (int j = 0; j < 14; ++j) {
            printf("%c", (display[i] & (1 << (13 - j))) ? '*' : ' ');
        }
        if (dbg) printf("| %02x %02x\n", buf[2 * i] , buf[2 * i + 1]);
    }
    if (dbg) printf("        +--------------+\n");

#if defined(HOST_BUILD)
    return true;
#else
    int r = smsg.Write(buf, sizeof(buf));
    return (r == sizeof(buf));
#endif
}

void Display::_DrawPoint(uint8_t x, uint8_t y, bool on)
{
    assert(x < 14);
    assert(y < 9);
    if (on) {
        display[y] |= 1 << (13 - x);
    } else {
        display[y] &= ~(1 << (13 - x));
    }
}
