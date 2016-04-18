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

#ifndef __DISPLAY_HPP__
#define __DISPLAY_HPP__

#include <stdint.h>
#include <LiquidCrystal.h>

namespace MO
{
    /** Wrapper class for writing to LCD display 16x2.
     *
     * It allows calling Write() with any number of arguments, like printf(...)
     * for writing something to the LCD display.
     * One version of Write takes both x and y starting position. Onother one
     * takes just y (i.e. the line).
     * It also keeps track of what what written at given line before so if new
     * content is the same as previous then it does not really writes it again.
     * This needs to be improved to take in account "x" position when comparing
     * strings.
     */
    class Display
    {
        public:
            enum
            {
                MAX_LINES = 2,
                MAX_CHARS = 16,
                BUF_SIZE = MAX_CHARS + 1
            };

            /// Initialize the object.
            Display();

            /// Called once.
            void Setup();

            /// Allows setting up a_char with given dot matrix of size 8.
            void Setup_Char(uint8_t a_char, uint8_t *a_matrix);

            /// Writes a string at (a_x, a_y) location.
            void Write(uint8_t a_x, uint8_t a_y, const char *a_format, ...);

            /// Writes a string at (0, a_y) location.
            void Write(uint8_t a_y, const char *a_format, ...);
        private:
            void write(uint8_t a_x, uint8_t a_y, const char *a_format, va_list &a_vl);

            LiquidCrystal the_lcd;
            char          the_buf[BUF_SIZE];                 //!< Tmp buffer.
            char          the_old_line[MAX_LINES][BUF_SIZE]; //!< Old strings.
    };
}

#endif
