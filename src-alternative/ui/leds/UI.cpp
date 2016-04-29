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

#include "UI.hpp"
#include "Utils.hpp"
#include "Const.hpp"

namespace MO
{
    UI::UI(): the_timer(0), the_beeper(Const::PIN_BEEPER, 1)
    {
        Utils::debug("UI leds started\n");
    }

    // -------------------------------------------------------------------------

    void UI::Show_Ready(const State_IF &a_state)
    {
        // in ready state indicated what is next, pause for some time
        // and show how many are done TODO

        uint8_t period_min = a_state.Get_Current_Period_Minutes();
        if (period_min == Const::POM_WORK_MIN)
        {
            digitalWrite(PIN_L1, HIGH);
            digitalWrite(PIN_L2, HIGH);
            digitalWrite(PIN_L3, HIGH);
            digitalWrite(PIN_L4, HIGH);
            digitalWrite(PIN_L5, HIGH);
        } 
        else if (period_min == Const::POM_BREAK_SHORT_MIN)
        {
            digitalWrite(PIN_L1, HIGH);
            digitalWrite(PIN_L2, LOW);
            digitalWrite(PIN_L3, LOW);
            digitalWrite(PIN_L4, LOW);
            digitalWrite(PIN_L5, LOW);
        }
        else if (period_min == Const::POM_BREAK_LONG_MIN)
        {
            digitalWrite(PIN_L1, HIGH);
            digitalWrite(PIN_L2, HIGH);
            digitalWrite(PIN_L3, HIGH);
            digitalWrite(PIN_L4, LOW);
            digitalWrite(PIN_L5, LOW);
        }
    }     
          
    // -------------------------------------------------------------------------

    void UI::Show_Running(const State_IF &a_state)
    {
        uint32_t time_pct = a_state.Get_Time_Left_Ms() * 100/
                            a_state.Get_Time_Max_Ms();

        digitalWrite(PIN_L1, (time_pct > 0) ? HIGH: LOW);
        digitalWrite(PIN_L2, (time_pct > 20)? HIGH: LOW);
        digitalWrite(PIN_L3, (time_pct > 40)? HIGH: LOW);
        digitalWrite(PIN_L4, (time_pct > 60)? HIGH: LOW);
        digitalWrite(PIN_L5, (time_pct > 80)? HIGH: LOW);
    }

    // -------------------------------------------------------------------------

    void UI::Show_Paused(const State_IF &a_state)
    {
        the_timer += 1;

        if (the_timer >= 10)
        {
            the_timer = 0;
        }

        if (the_timer < 5)
        {
            Show_Running(a_state);
        }
        else
        {
            digitalWrite(PIN_L1, LOW);
            digitalWrite(PIN_L2, LOW);
            digitalWrite(PIN_L3, LOW);
            digitalWrite(PIN_L4, LOW);
            digitalWrite(PIN_L5, LOW);
        }
    }

    // -------------------------------------------------------------------------

    void UI::Show_Finished(const State_IF &a_state)
    {
        if (the_timer % 2)
        {
            Show_Ready(a_state);
        }
        else
        {
            digitalWrite(PIN_L1, LOW);
            digitalWrite(PIN_L2, LOW);
            digitalWrite(PIN_L3, LOW);
            digitalWrite(PIN_L4, LOW);
            digitalWrite(PIN_L5, LOW);
        }
       
        if (the_timer > 0)
            the_timer -= 1;
        the_beeper.Update();
    }

    // -------------------------------------------------------------------------

    void UI::Set_Beeper(byte a_val)
    {
        the_timer = a_val * 10;
        the_beeper.Reset(a_val);
    }

    // -------------------------------------------------------------------------

    bool UI::Showing() const
    {
        return (the_timer != 0) || (the_beeper.Done() == false);
    }

    // -------------------------------------------------------------------------

    void UI::Setup()
    {
        pinMode(PIN_L1, OUTPUT);
        pinMode(PIN_L2, OUTPUT);
        pinMode(PIN_L3, OUTPUT);
        pinMode(PIN_L4, OUTPUT);
        pinMode(PIN_L5, OUTPUT);

        the_beeper.Setup();
    }
}

