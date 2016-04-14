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

#ifndef __UI_IF_HPP__
#define __UI_IF_HPP__

#include <stdint.h>

namespace MO
{
    class State_IF;

    /// Interface class for UI - the pomodoro class will use that for showing something.
    class UI_IF
    {
        public:
            virtual ~UI_IF() { }

            /// Visualize states.
            virtual void Show_Ready(const State_IF &) = 0;
            virtual void Show_Running(const State_IF &) = 0;
            virtual void Show_Paused(const State_IF &) = 0;
            virtual void Show_Finished(const State_IF &) = 0;

            /// Sets up the beeper of the UI object.
            virtual void Set_Beeper(uint8_t) = 0;

            /// True if the state is being shown (it can take some time).
            virtual bool Showing() const = 0;

            /// Called once at startup.
            virtual void Setup() = 0;
    };
}

#endif
