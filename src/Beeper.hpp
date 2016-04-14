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

#ifndef __BEEPER_HPP__
#define __BEEPER_HPP__

#include <Arduino.h>

namespace MO
{
    /** Handles switching on and off a few times some digital output.
     *
     * It can be used for example with a buzzer like TMB12A05 or a LED to turn
     * it on/off predefined number of times.
     *
     * Everytime Update() is called it switches state between on and off.
     */

    class Beeper
    {
        public:
            Beeper(uint8_t a_pin, uint16_t a_max_beeps):
                the_pin(a_pin), the_cycle(0), the_max_beeps(a_max_beeps)
            {
            }

            void Setup() { pinMode(the_pin, OUTPUT); }

            bool Done() const { return the_cycle >= (the_max_beeps << 1); }

            void Update()
            {
                if (!Done())
                {
                    digitalWrite(the_pin, (the_cycle & 1)? LOW : HIGH);
                    the_cycle += 1;
                }
            }

            void Reset(uint16_t a_max_beeps = 0)
            {
                the_cycle = 0;
                if (a_max_beeps > 0)
                {
                    the_max_beeps = a_max_beeps;
                }
                digitalWrite(the_pin, LOW);
            }
        private:
            uint8_t  the_pin;        //!< Used digital input.
            uint16_t the_cycle;      //!< Counts calls of Update().
            uint16_t the_max_beeps;  //!< Stores maximum of allowed 'beeps'.
    };
}

#endif
