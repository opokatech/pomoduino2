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

#ifndef __POMODORO_HPP__
#define __POMODORO_HPP__

#include <stdint.h>

#include "Button_Logic.hpp"
#include "Timer.hpp"
#include "Period.hpp"
#include "State_IF.hpp"
#include "UI_IF.hpp"
#include "Eeprom_IF.hpp"

namespace MO
{
    /** Pomodoro logic.
     *
     * Uses a state machine for handling different states of the system.
     * As output of the state it uses an instance of UI_IF object which should
     * know how to present the state.
     * A state object is an instance of a class derived from the abstract (just
     * like UI_IF) State_IF class. This class implements the interface defined
     * in State_IF.
     *
     * As inputs it uses 2 buttons.
     */

    class Pomodoro: public State_IF
    {
        public:
            Pomodoro(UI_IF *a_ui, Button_Logic *a_b1, Button_Logic *a_b2,
                     Eeprom_IF *a_eeprom);

            /// Called once.
            void Setup();

            /// Called from main loop every 100ms.
            void Run(uint32_t a_time);

            // <State interface>
            uint8_t Get_Pomodoros() const { return the_pomodoros; }
            uint8_t Get_Current_Period_Minutes() const
            { return the_pom[the_timer_type]->Get_Time_In_Min(); }
            uint32_t Get_Time_Left_Ms() const
            { return the_timer.Get_Time_Left(); }
            uint32_t Get_Time_Max_Ms() const { return the_timer.Get_Max(); }
            bool Is_Pomodoro() const { return the_timer_type == T_POM25; }
            // </State interface>
        private:
            /// Shortcut for current period.
            const Period & p() { return *the_pom[the_timer_type]; }

            void run_ready();
            void run_running(uint32_t a_time);
            void run_finished();
            void run_pause();

            void reset_timer() { the_timer.Reset(p().Get_Time_In_Ms()); }
            void continue_timer() { the_timer.Reset(the_timer.Get_Time_Left()); }

            // type of pomodoro periods
            enum
            {
                T_POM25,
                T_POM5,
                T_POM15,

                T_SIZE
            };

            enum STATE
            {
                READY,
                RUNNING,
                FINISHED,
                PAUSED
            };

            uint8_t the_timer_type; //!< Current timer type (T_POM25, etc.)
            STATE   the_state;
            Timer   the_timer;
            uint8_t the_pomodoros;  //!< Number of pomodoros done so far.

            UI_IF        *the_ui;
            Button_Logic *the_b1;
            Button_Logic *the_b2;
            Eeprom_IF    *the_eeprom;

            Period  the_pom25;
            Period  the_pom5;
            Period  the_pom15;
            Period* the_pom[T_SIZE];
    };
}

#endif

