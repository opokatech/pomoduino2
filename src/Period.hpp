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

#ifndef __PERIOD_HPP__
#define __PERIOD_HPP__

#include <stdint.h>

namespace MO
{
    /** Stores data for each period of pomodoro technique.
     * Those data are time in minutes and number of beeps for notification about
     * finishing.
     */
    class Period
    {
        public:
            Period(uint8_t a_time = 0, uint8_t a_beeps = 0):
                the_time_in_minutes(a_time), the_beeps(a_beeps)
            {
            }

            /// Returns plain number of minutes.
            uint8_t Get_Time_In_Min() const { return the_time_in_minutes; }

            /// Returns the number of minutes but in msec.
            uint32_t Get_Time_In_Ms() const
            {
#ifdef MO_DEBUG
                return (uint32_t)the_time_in_minutes * 1000;
#else
                return (uint32_t)the_time_in_minutes * 60 * 1000;
#endif
            }

            /// Returns the beeps count for the period.
            uint8_t Get_Beeps() const { return the_beeps; }
        private:
            uint8_t the_time_in_minutes;
            uint8_t the_beeps;           //!< How many beeps to emit at the end
    };
}

#endif
