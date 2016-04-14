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

#ifndef __TIMER_HPP__
#define __TIMER_HPP__

#include "Counter.hpp"

namespace MO
{
    /** Capped Counter class.
     *
     * It extends the Counter class with a maximum value and methods for
     * checking if timer elapsed and how much time is left.
     */
    class Timer: public Counter
    {
        public:
            Timer(uint32_t a_max): the_max(a_max) { }

            /// True if current counter last at least the given maximum.
            bool Elapsed() const { return Duration() >= the_max; }

            /// Resets the timer to new maximum.
            void Reset(uint32_t a_max)
            {
                Counter::Reset();
                the_max = a_max;
            }

            /// Returns the maximum.
            uint32_t Get_Max() const { return the_max; }

            /// Returns left time or 0 if the timer elapsed.
            uint32_t Get_Time_Left() const
            {
                if (Duration() < the_max)
                    return the_max - Duration();
                else
                    return 0;
            }

        private:
            uint32_t the_max;
    };
}

#endif
