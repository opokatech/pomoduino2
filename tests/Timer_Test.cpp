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
#include "Timer.hpp"

using namespace testing;

// -----------------------------------------------------------------------------

TEST(timer, basic_functions)
{
 	MO::Timer t(10);

 	ASSERT_EQ(t.Duration(), 0);
 	ASSERT_FALSE(t.Elapsed());
 	ASSERT_EQ(t.Get_Time_Left(), 10);

    uint32_t now = 100;
    t.Update(now); // calling it first time sets up internal starting point

 	ASSERT_EQ(t.Duration(), 0);
 	ASSERT_FALSE(t.Elapsed());
 	ASSERT_EQ(t.Get_Time_Left(), 10);

    t.Update(now + 5); // 5 units (ms, s, etc) later
 	ASSERT_EQ(t.Duration(), 5);
 	ASSERT_FALSE(t.Elapsed());
 	ASSERT_EQ(t.Get_Time_Left(), 5);

    t.Update(now + 10); // 10 units later
 	ASSERT_EQ(t.Duration(), 10);
 	ASSERT_TRUE(t.Elapsed()); // now we reached max time
 	ASSERT_EQ(t.Get_Time_Left(), 0); // nothing left

    t.Update(now + 20); // much later
 	ASSERT_EQ(t.Duration(), 20);
 	ASSERT_TRUE(t.Elapsed()); // still true
 	ASSERT_EQ(t.Get_Time_Left(), 0); // nothing left
}

