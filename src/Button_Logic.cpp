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

#include "Button_Logic.hpp"
#include "Utils.hpp"

namespace MO
{
    void Button_Logic::Update(uint32_t a_time, bool a_pin_active)
    {
        uint8_t state = a_pin_active; // current state of the pin

        if (the_start_time == 0) // first run
        {
            the_start_time = a_time;
            the_state = state;
        }

        if (the_state == state) // most common condition first
        {
            the_duration = a_time - the_start_time;
            the_pressed = 0; // clear this since it is the same as before
            the_released = 0; // clear this since it is the same as before
        }
        else // state has changed
        {
            // as a last duraion we take the difference between now and last
            // set start time (before we change it in the next line).
            the_last_duration = a_time - the_start_time;
            the_start_time = a_time;
            the_duration = 0;

            if (state) // new state is ON
            {
                the_pressed = 1;
                the_released = 0;
                Utils::debug("PRESS");
            }
            else // new state is OFF
            {
                the_pressed = 0;
                the_released = 1;
                Utils::debug("RELEASE");
            }
            the_state = state;
        }
    }
}

