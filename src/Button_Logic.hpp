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

#ifndef __BUTTON_LOGIC_HPP__
#define __BUTTON_LOGIC_HPP__

#include <stdint.h>

namespace MO
{
    /** Button functionality - a logical layer.
     *
     * It wraps a logic around activation and deactivation some input.
     *
     * It should be called with Update(time) where time is a current time (can
     * be in ms).  It comes handy for detecting presses, releases, state and
     * times of current and previous state. See comments at particular methods.
     *
     * The time can be given in ms or any other units. The whole computation of
     * Duration is using those units too.
     */
    class Button_Logic
    {
        public:
            Button_Logic() { Reset(); }
            virtual ~Button_Logic() { }

            /// Called once.
            virtual void Setup() { }

            /// The logic always sets state false - overwritten in Button.
            virtual void Update(uint32_t a_time) { Update(a_time, false); }

            /// Sets internal state using the current time and given new state.
            void Update(uint32_t a_time, bool a_pin_active);

            /// Returns true on rising edge - cleared with next call of Update.
            bool Pressed() const { return the_pressed == 1; }

            /// Returns true on falling edge - cleared with next call of Update.
            bool Released() const { return the_released == 1; }

            /// Actual state of the pin.
            bool On() const { return the_state; }

            /// Reset status to the initial.
            void Reset()
            {
                the_state = 0;
                the_pressed = 0;
                the_released = 0;
                the_start_time = 0;
                the_duration = 0;
                the_last_duration = 0;
            }

            /// Duration of current state.
            uint32_t Duration() const { return the_duration; }

            /// Duration of previous state.
            uint32_t Last_Duration() const { return the_last_duration; }

        private:
            uint8_t  the_state:1;
            uint8_t  the_pressed:1;
            uint8_t  the_released:1;

            uint32_t the_start_time;
            uint32_t the_duration;      //!< Duration of current state.
            uint32_t the_last_duration; //!< Duration of previous state.
    };
}

#endif
