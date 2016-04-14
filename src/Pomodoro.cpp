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

#include "Pomodoro.hpp"
#include "Utils.hpp"
#include "Const.hpp"

namespace MO
{
    Pomodoro::Pomodoro(UI_IF *a_ui, Button_Logic *a_b1, Button_Logic *a_b2,
                       Eeprom_IF *a_eeprom):
        the_timer_type(T_POM25), the_state(READY),
        the_timer(0), the_pomodoros(0),

        the_ui(a_ui),
        the_b1(a_b1),
        the_b2(a_b2),
        the_eeprom(a_eeprom),

        the_pom25(Const::POM_WORK_MIN, Const::POM_WORK_BEEPS),
        the_pom5(Const::POM_BREAK_SHORT_MIN, Const::POM_BREAK_SHORT_BEEPS),
        the_pom15(Const::POM_BREAK_LONG_MIN, Const::POM_BREAK_LONG_BEEPS)
    {
        the_pom[T_POM25] = &the_pom25;
        the_pom[T_POM5]  = &the_pom5;
        the_pom[T_POM15] = &the_pom15;

        // read pomodoros from eeprom
        the_pomodoros = the_eeprom->Read(Const::POM_SAVE_ADDRESS);

        reset_timer();
    }

    // -------------------------------------------------------------------------

    void Pomodoro::Setup()
    {
        the_ui->Setup();
    }

    // -------------------------------------------------------------------------

    void Pomodoro::Run(uint32_t a_time)
    {
        if (the_state == READY)
            run_ready();
        else if (the_state == RUNNING)
            run_running(a_time);
        else if (the_state == FINISHED)
            run_finished();
        else if (the_state == PAUSED)
            run_pause();
    }

    // -------------------------------------------------------------------------

    void Pomodoro::run_ready()
    {
        the_ui->Show_Ready(*this);

        // if B1 pressed then cycle through times in timer
        if (the_b1->Released())
        {
            the_timer_type = (the_timer_type + 1) % T_SIZE;
            reset_timer();
            Utils::debug("next timer idx = %u", the_timer_type);
        }

        if (the_b2->On())
        {
            // if B2 was pressed longer than 3s then reset pomodoros
            if (the_b2->Duration() > 3000)
            {
                the_pomodoros = 0;

                // save pomodoros to eeprom
                the_eeprom->Write(Const::POM_SAVE_ADDRESS, the_pomodoros);

                the_timer_type = T_POM25;
                reset_timer();
                Utils::debug("cleared pomorodos");
            }
        }
        // b2 is off
        else if (the_b2->Released())
        {
            if (the_b2->Last_Duration() < 250)
            {
                the_ui->Set_Beeper(p().Get_Beeps());
                reset_timer();
                Utils::debug("going to running state");

                the_state = RUNNING;
            }
        }
    }

    // -------------------------------------------------------------------------

    void Pomodoro::run_running(uint32_t a_time)
    {
        // update counter
        the_timer.Update(a_time);

        the_ui->Show_Running(*this);

        if (the_timer.Elapsed())
        {
            the_state = FINISHED;
        }
        else if (the_b2->Released())
        {
            the_state = PAUSED;
        }
    }

    // -------------------------------------------------------------------------

    void Pomodoro::run_finished()
    {
        the_ui->Show_Finished(*this);

        // play beeper until it is done
        if (the_ui->Showing() == false)
        {
            if (the_timer_type == T_POM25)
            {
                the_pomodoros += 1;
                // save pomodoros to eeprom
                the_eeprom->Write(Const::POM_SAVE_ADDRESS, the_pomodoros);

                the_timer_type = T_POM5;
                if (the_pomodoros % 4 == 0)
                {
                    the_timer_type = T_POM15;
                }
            }
            else
            {
                the_timer_type = T_POM25;
            }
            reset_timer();
            the_state = READY;
        }
    }

    // -------------------------------------------------------------------------

    void Pomodoro::run_pause()
    {
        the_ui->Show_Paused(*this);

        // if B2 pressed then go to running
        if (the_b2->On())
        {
            // if B2 was pressed longer than 3s then cancel the pomodoro
            if (the_b2->Duration() > 3000)
            {
                reset_timer();
                the_state = READY;
                the_b2->Reset();
            }
        }
        // b2 is off
        else if (the_b2->Released())
        {
            if (the_b2->Last_Duration() < 250)
            {
                continue_timer();
                the_state = RUNNING;
            }
        }
    }
}
