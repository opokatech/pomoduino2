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

#ifndef __STATE_IF_HPP__
#define __STATE_IF_HPP__

namespace MO
{
    /** State of the system - abstract class.
     *
     * It is uses to pass the state to an instance of UI.
     * It should contain enough information for the UI to show something.
     */
    class State_IF
    {
        public:
            virtual ~State_IF() { }

            virtual uint8_t  Get_Pomodoros() const = 0;
            virtual uint8_t  Get_Current_Period_Minutes() const = 0;
            virtual uint32_t Get_Time_Left_Ms() const = 0;
            virtual uint32_t Get_Time_Max_Ms() const = 0;
            virtual bool     Is_Pomodoro() const = 0;
    };
}

#endif
