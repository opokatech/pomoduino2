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

#include <stdarg.h>
#include <Arduino.h>
#include "Display.hpp"
#include "Const.hpp"

namespace MO
{
    Display::Display():
        the_lcd(Const::PIN_RS, Const::PIN_ENABLE,
                Const::PIN_D4, Const::PIN_D5, Const::PIN_D6, Const::PIN_D7)
    {
        for (uint8_t i = 0; i < MAX_LINES; ++i)
            memset(the_old_line[i], 0, BUF_SIZE);
    }

    // -------------------------------------------------------------------------

    void Display::Setup()
    {
        the_lcd.begin(MAX_CHARS, MAX_LINES);   // 16x2 format
        pinMode(MO::Const::PIN_LCD_BRIGHTNESS, OUTPUT); // uses PWM pin
        pinMode(MO::Const::PIN_LCD_CONTRAST, OUTPUT); // uses PWM pin

        // delivers 80/255 duty cycle PWM
        analogWrite(MO::Const::PIN_LCD_BRIGHTNESS, 80);

        // for contrast we should deliver real analog signal.
        // Putting PWM instead may work, but sometimes the result is
        // flickering. To prevent that some simple RC filter needs to be added.
        // Alternatively just R will do, however it is a waste of energy.
        //
        // If you want try PWM uncomment the line below and replace resistor
        // with RC (another R in serie and a capacitor parallel).
        // analogWrite(MO::Const::PIN_LCD_CONTRAST, 128);
    }

    // -------------------------------------------------------------------------

    void Display::Setup_Char(uint8_t a_char, uint8_t *a_matrix)
    {
        the_lcd.createChar(a_char, a_matrix);
    }

    // -------------------------------------------------------------------------

    void Display::Write(uint8_t a_x, uint8_t a_y, const char *a_format, ...)
    {
        va_list vl;
        va_start(vl, a_format);
        write(a_x, a_y, a_format, vl);
        va_end(vl);
    }

    // -------------------------------------------------------------------------

    void Display::Write(uint8_t a_y, const char *a_format, ...)
    {
        va_list vl;
        va_start(vl, a_format);
        write(0, a_y, a_format, vl);
        va_end(vl);
    }

    // -------------------------------------------------------------------------

    void Display::write(uint8_t a_x, uint8_t a_y, const char *a_format, va_list &a_vl)
    {
        if (a_y >= MAX_LINES)
            return;

        int written = vsnprintf(the_buf, BUF_SIZE, a_format, a_vl);

        if (written >= 0) // even if we don't write chars - we still clean the line
        {
            // fill up the rest with spaces
            for (int i = written; i < MAX_CHARS; ++i)
                the_buf[i] = ' ';
            the_buf[MAX_CHARS] = 0;
        }
        else
        {
            memset(the_buf, 0, BUF_SIZE);
        }

        if (strcmp(the_buf, the_old_line[a_y]) != 0)
        {
            the_lcd.setCursor(0, a_y);
            the_lcd.print(the_buf);
            memcpy(the_old_line[a_y], the_buf, BUF_SIZE);
        }
    }
}

