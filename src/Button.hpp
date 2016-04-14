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

#ifndef __BUTTON_HPP__
#define __BUTTON_HPP__

#include <Arduino.h>
#include "Button_Logic.hpp"

namespace MO
{
    /** Wrappers a digital pin with button functionality.
     *
     * It adds a hardware layer (setting up pin, reading its value) to a logical
     * button class.
     */
    class Button: public Button_Logic
    {
        public:
            Button(uint8_t a_pin): the_pin(a_pin) { }

            /// Called once to setup pin mode.
            virtual void Setup() { pinMode(the_pin, INPUT_PULLUP); }

            /// Sets internal state given the current time and state of the pin.
            virtual void Update(uint32_t a_time)
            {
                // since it is PULLUP then active (pressed) state is when we
                // read LOW
                Button_Logic::Update(a_time, digitalRead(the_pin) == LOW);
            }

        private:
            uint8_t  the_pin;           //!< Used digital input pin.
    };
}

#endif
