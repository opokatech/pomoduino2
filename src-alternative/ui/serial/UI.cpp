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

#include <Arduino.h>
#include <stdarg.h>

#include "UI.hpp"
#include "Utils.hpp"

namespace MO
{
    UI::UI(): the_timer(0)
    {
        memset(the_buf, 0, B_SIZE);
        memset(the_last_buf, 0, B_SIZE);
    }

    // -------------------------------------------------------------------------

    void UI::Show_Ready(const State_IF &a_state)
    {
        write("P%02u READY    #%02u",
               a_state.Get_Current_Period_Minutes(),
               a_state.Get_Pomodoros());
    }

    // -------------------------------------------------------------------------

    void UI::Show_Running(const State_IF &a_state)
    {
        write("P%02u %5s    #%02u",
               a_state.Get_Current_Period_Minutes(),
               Utils::ms_to_m_s(a_state.Get_Time_Left_Ms()),
               a_state.Get_Pomodoros());
    }

    // -------------------------------------------------------------------------

    void UI::Show_Paused(const State_IF &a_state)
    {
        write("P%02u %5s    - PAUSED #%02u",
              a_state.Get_Current_Period_Minutes(),
              Utils::ms_to_m_s(a_state.Get_Time_Left_Ms()),
              a_state.Get_Pomodoros());
    }

    // -------------------------------------------------------------------------

    void UI::Show_Finished(const State_IF &a_state)
    {
        // display pomodoro done while playing beeper
        if (a_state.Is_Pomodoro())
        {
            write("!POMODORO! - well done!");
        }
        else
        {
            write("end of break - back to work");
        }
        if (the_timer > 0)
            the_timer -= 1;
    }

    // -------------------------------------------------------------------------

    void UI::Set_Beeper(byte a_val)
    {
        the_timer = a_val * 10;
    }

    // -------------------------------------------------------------------------

    bool UI::Showing() const
    {
        return the_timer != 0;
    }

    // -------------------------------------------------------------------------

    void UI::Setup()
    {
        Serial.begin(9600);
    }

    // -------------------------------------------------------------------------

    void UI::write(const char *a_format, ...)
    {
        va_list vl;
        va_start(vl, a_format);
        memset(the_buf, 0, B_SIZE);
        int written = vsnprintf(the_buf, B_SIZE, a_format, vl);
        va_end(vl);

        if (written > 0)
        {
            if (strcmp(the_buf, the_last_buf) != 0)
            {
                Serial.println(the_buf);
                memcpy(the_last_buf, the_buf, B_SIZE);
            }
        }
    }
}

