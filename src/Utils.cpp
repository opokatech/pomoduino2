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

#include "Utils.hpp"
#include <stdio.h>
#include <stdarg.h>
#ifdef MO_DEBUG
// it is only needed if we want to print via Serial, so not for gtests
#include <Arduino.h>
#endif

namespace Utils
{
    const char *ms_to_m_s(uint32_t a_ms)
    {
        static const uint8_t B_SIZE = 64;
        static char buf[B_SIZE];

        uint32_t s = a_ms / 1000;
        uint32_t m = s / 60;
        s -= m * 60;

        snprintf(buf, B_SIZE, "%02lu:%02lu", m, s);
        return buf;
    }

    // -------------------------------------------------------------------------

    void debug(const char *a_format, ...)
    {
#ifdef MO_DEBUG
        const unsigned int B_SIZE = 256;
        char buf[B_SIZE];

        va_list vl;

        va_start(vl, a_format);
        int written = vsnprintf(buf, B_SIZE, a_format, vl);
        va_end(vl);

        if (written > 0)
        {
            Serial.println(buf);
        }
#else
        (a_format); // to avoid warning about not used variable
                    // when compiled without MO_DEBUG
#endif
    }
}
