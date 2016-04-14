/*
Copyright (c) 2016 Miroslaw Opoka <mirek@opoki.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef __CONST_HPP__
#define __CONST_HPP__

#include <stdint.h>

namespace MO
{
    namespace Const
    {
        const uint8_t PIN_B1                = 9;  // button 1
        const uint8_t PIN_B2                = 10; // button 2

        // display
        const uint8_t PIN_RS                = 12;
        const uint8_t PIN_ENABLE            = 11;
        const uint8_t PIN_D0                = 5;
        const uint8_t PIN_D1                = 4;
        const uint8_t PIN_D2                = 3;
        const uint8_t PIN_D3                = 2;

        // pomodoro constants
        const uint8_t POM_WORK_MIN          = 25;
        const uint8_t POM_BREAK_SHORT_MIN   = 5;
        const uint8_t POM_BREAK_LONG_MIN    = 15;

        const uint8_t POM_WORK_BEEPS        = 5;
        const uint8_t POM_BREAK_SHORT_BEEPS = 1;
        const uint8_t POM_BREAK_LONG_BEEPS  = 3;

        // eeprom address for saving pomodoros
        const int     POM_SAVE_ADDRESS      = 0;
    }
}

#endif
