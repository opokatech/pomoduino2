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

#include "UI.hpp"
#include "Utils.hpp"
#include "Const.hpp"

namespace MO
{
    UI::UI(): the_timer(0), the_beeper(Const::PIN_BEEPER, 1)
    {

    }

    // -------------------------------------------------------------------------

    void UI::Show_Ready(const State_IF &a_state)
    {
        the_display.Write(0, "P%02u READY    %c%02u",
                          a_state.Get_Current_Period_Minutes(),
                          char(CHAR_POM),
                          a_state.Get_Pomodoros());

        create_progress(a_state);
        the_display.Write(1, the_progress);
    }

    // -------------------------------------------------------------------------

    void UI::Show_Running(const State_IF &a_state)
    {
        uint8_t pom = a_state.Get_Pomodoros();
        the_display.Write(0, "P%02u %5s    %c%02u",
                          a_state.Get_Current_Period_Minutes(),
                          Utils::ms_to_m_s(a_state.Get_Time_Left_Ms()),
                          char(CHAR_POM),
                          pom);
        create_progress(a_state);

        if (a_state.Is_Pomodoro())
        {
            if (pom < Display::MAX_CHARS) // we have space
                the_progress[pom] = 126; // this is the arrow char
        }
        the_display.Write(1, the_progress);
    }

    // -------------------------------------------------------------------------

    void UI::Show_Paused(const State_IF &a_state)
    {
        uint8_t pom = a_state.Get_Pomodoros();
        // alternate those 2 lines
        if (the_timer < 5)
        {
            the_display.Write(0, "P%02u %5s    %c%02u",
                              a_state.Get_Current_Period_Minutes(),
                              Utils::ms_to_m_s(a_state.Get_Time_Left_Ms()),
                              char(CHAR_POM),
                              pom);
        }
        else
        {
            the_display.Write(0, "P%02u %5s    %c%02u",
                              a_state.Get_Current_Period_Minutes(),
                              "",
                              char(CHAR_POM),
                              pom);
        }

        the_timer += 1;
        if (the_timer >= 10)
            the_timer = 0;

        create_progress(a_state);
        the_display.Write(1, the_progress);
    }

    // -------------------------------------------------------------------------

    void UI::Show_Finished(const State_IF &a_state)
    {
        // display pomodoro done while playing beeper
        if (a_state.Is_Pomodoro())
        {
            the_display.Write(0, "!POMODORO!");
            the_display.Write(1, "well done!");
        }
        else
        {
            the_display.Write(0, "end of break");
            the_display.Write(1, "back to work");
        }

        the_beeper.Update();
    }

    // -------------------------------------------------------------------------

    void UI::Set_Beeper(uint8_t a_val)
    {
        the_beeper.Reset(a_val);
    }

    // -------------------------------------------------------------------------

    bool UI::Showing() const
    {
        // we are done when beeper stoped.
        return the_beeper.Done() == false;
    }

    // -------------------------------------------------------------------------

    void UI::Setup()
    {
        uint8_t pomodoro[8] =
		{
		  B10000,
		  B01010,
		  B00100,
		  B01110,
		  B11111,
		  B11111,
		  B11111,
		  B01110,
        };

        the_display.Setup_Char(CHAR_POM, pomodoro);

        the_display.Setup();
        the_beeper.Setup();
    }

    // -------------------------------------------------------------------------

    void UI::create_progress(const State_IF &a_state)
    {
        memset(the_progress, 0, Display::BUF_SIZE);
        uint8_t pos = 0;
        for (pos = 0; pos < a_state.Get_Pomodoros() &&
                      pos < Display::MAX_CHARS; ++pos)
        {
            the_progress[pos] = CHAR_POM;
        }
    }
}

