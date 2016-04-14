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

#include "Const.hpp"
#include "Pomodoro.hpp"
#include "Button.hpp"
#include "Eeprom.hpp"

// using "user interface" depending on UI_SERIAL define
#ifdef UI_SERIAL
#include "ui/UI_Serial.hpp"

MO::UI_Serial the_ui;
#else
#include "ui/UI_Full.hpp"

MO::UI_Full the_ui;
#endif

MO::Button the_b1(MO::Const::PIN_B1);
MO::Button the_b2(MO::Const::PIN_B2);
MO::Eeprom the_eeprom;

// for MO::Pomodoro it does not matter what UI it uses
MO::Pomodoro the_pomodoro(&the_ui, &the_b1, &the_b2, &the_eeprom);
uint32_t the_time = 0;

void setup()
{
    the_b1.Setup();
    the_b2.Setup();
    the_pomodoro.Setup();
#ifdef MO_DEBUG
    Serial.begin(9600);
#endif
}

void loop()
{
    the_time = millis();

    the_b1.Update(the_time);
    the_b2.Update(the_time);
    the_pomodoro.Run(the_time);

    delay(100);
}
