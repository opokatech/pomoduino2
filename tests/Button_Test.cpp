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

#include <gtest/gtest.h>
#include "Button_Logic.hpp"

using namespace testing;

// -----------------------------------------------------------------------------

TEST(button, pressing_releasing)
{
    MO::Button_Logic btn;

    ASSERT_EQ(btn.Duration(), 0);
    ASSERT_FALSE(btn.Pressed());
    ASSERT_FALSE(btn.Released());
    ASSERT_FALSE(btn.On());

    uint32_t now = 100;
    btn.Update(now, false); // calling it first time sets up internal starting point

    now += 10;
    btn.Update(now, false);
    ASSERT_EQ(btn.Duration(), 10);
    ASSERT_FALSE(btn.Pressed());
    ASSERT_FALSE(btn.Released());
    ASSERT_FALSE(btn.On());

    now += 30;
    btn.Update(now, true);
    ASSERT_EQ(btn.Duration(), 0);
    ASSERT_EQ(btn.Last_Duration(), 40); // between first update and changing state
    ASSERT_TRUE(btn.Pressed());
    ASSERT_FALSE(btn.Released());
    ASSERT_TRUE(btn.On());

    now += 1;
    btn.Update(now, true);
    ASSERT_EQ(btn.Duration(), 1);
    ASSERT_EQ(btn.Last_Duration(), 40); // no diff
    ASSERT_FALSE(btn.Pressed()); // updated
    ASSERT_FALSE(btn.Released());
    ASSERT_TRUE(btn.On());

    now += 1;
    btn.Update(now, false);
    ASSERT_EQ(btn.Duration(), 0);
    ASSERT_EQ(btn.Last_Duration(), 2); // last duration + new time shift
    ASSERT_FALSE(btn.Pressed()); // updated
    ASSERT_TRUE(btn.Released());
    ASSERT_FALSE(btn.On());

    now += 1;
    btn.Update(now, false);
    ASSERT_EQ(btn.Duration(), 1);
    ASSERT_EQ(btn.Last_Duration(), 2); // no diff
    ASSERT_FALSE(btn.Pressed());
    ASSERT_FALSE(btn.Released()); // updated
    ASSERT_FALSE(btn.On());
}

// -----------------------------------------------------------------------------

TEST(button, duration)
{
    MO::Button_Logic btn;

    ASSERT_EQ(btn.Duration(), 0);
    ASSERT_EQ(btn.Last_Duration(), 0);

    uint32_t now = 100;
    btn.Update(now, false); // calling it first time sets up internal starting point

    now += 10;
    btn.Update(now, false);
    ASSERT_EQ(btn.Duration(), 10);
    ASSERT_EQ(btn.Last_Duration(), 0);

    now += 30;
    btn.Update(now, false);
    ASSERT_EQ(btn.Duration(), 40);
    ASSERT_EQ(btn.Last_Duration(), 0);

    now += 10;
    btn.Update(now, true);
    ASSERT_EQ(btn.Duration(), 0);
    ASSERT_EQ(btn.Last_Duration(), 50);

    now += 5;
    btn.Update(now, true);
    ASSERT_EQ(btn.Duration(), 5);
    ASSERT_EQ(btn.Last_Duration(), 50);
}

