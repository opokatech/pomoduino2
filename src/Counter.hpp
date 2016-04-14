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

#ifndef __COUNTER_HPP__
#define __COUNTER_HPP__

#include <stdint.h>

namespace MO
{
    /** Counts elapsed time.
     *
     * When Update(time) is called an object of this class updates its duration
     * value, so it can tell for how long it is counting.
     */
    class Counter
    {
        public:
            Counter() { Reset(); }
            virtual ~Counter() { } // virtual because Timer derives from it

            void Update(uint32_t a_time)
            {
                if (the_start_time == 0) // first run
                {
                    the_start_time = a_time;
                }

                // so it will be 0 when we just started (see above)
                the_duration = a_time - the_start_time;
            }

            void Reset()
            {
                the_start_time = 0;
                the_duration = 0;
            }

            uint32_t Duration() const { return the_duration; }

        private:
            uint32_t the_start_time;
            uint32_t the_duration;
    };
}

#endif
