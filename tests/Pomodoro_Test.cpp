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

#include <gmock/gmock.h>
#include "Pomodoro.hpp"
#include "Const.hpp"

using namespace testing;

namespace MO
{
    class UI_Mock: public UI_IF
    {
        public:
            MOCK_METHOD1(Show_Ready, void(const State_IF&));
            MOCK_METHOD1(Show_Running, void(const State_IF&));
            MOCK_METHOD1(Show_Paused, void(const State_IF&));
            MOCK_METHOD1(Show_Finished, void(const State_IF&));

            MOCK_METHOD1(Set_Beeper, void(uint8_t));
            MOCK_CONST_METHOD0(Showing, bool(void));
            MOCK_METHOD0(Setup, void(void));
    };

    class Eeprom_Mock: public Eeprom_IF
    {
        public:
            MOCK_CONST_METHOD1(Read, uint8_t(int));
            MOCK_METHOD2(Write, void(int, uint8_t));
    };
}

// -----------------------------------------------------------------------------

TEST(pomodoro, pressing_b1)
{
    MO::UI_Mock ui;
    MO::Eeprom_Mock eeprom;
    MO::Button_Logic b1, b2;

    EXPECT_CALL(eeprom, Read(_));

    MO::Pomodoro pom(&ui, &b1, &b2, &eeprom);

    uint32_t now = 100;

    b1.Update(now, false);
    b2.Update(now, false);
    EXPECT_CALL(ui, Show_Ready(_));
    pom.Run(now);

    ASSERT_EQ(pom.Get_Pomodoros(), 0);
    ASSERT_TRUE(pom.Is_Pomodoro()); // type of timer
    ASSERT_EQ(pom.Get_Current_Period_Minutes(), MO::Const::POM_WORK_MIN);

    // press b1
    now += 1;
    b1.Update(now, true);
    b2.Update(now, false);
    EXPECT_CALL(ui, Show_Ready(_));
    pom.Run(now);

    ASSERT_TRUE(pom.Is_Pomodoro()); // type of timer
    ASSERT_EQ(pom.Get_Current_Period_Minutes(), MO::Const::POM_WORK_MIN);

    // release b1
    now += 1;
    b1.Update(now, false);
    b2.Update(now, false);
    EXPECT_CALL(ui, Show_Ready(_));
    pom.Run(now);

    ASSERT_FALSE(pom.Is_Pomodoro()); // type of timer
    ASSERT_EQ(pom.Get_Current_Period_Minutes(), MO::Const::POM_BREAK_SHORT_MIN);

    // again press and release b1

    // press b1
    now += 1;
    b1.Update(now, true);
    b2.Update(now, false);
    EXPECT_CALL(ui, Show_Ready(_));
    pom.Run(now);

    ASSERT_FALSE(pom.Is_Pomodoro());
    ASSERT_EQ(pom.Get_Current_Period_Minutes(), MO::Const::POM_BREAK_SHORT_MIN);

    // release b1
    now += 1;
    b1.Update(now, false);
    b2.Update(now, false);
    EXPECT_CALL(ui, Show_Ready(_));
    pom.Run(now);

    ASSERT_FALSE(pom.Is_Pomodoro());
    ASSERT_EQ(pom.Get_Current_Period_Minutes(), MO::Const::POM_BREAK_LONG_MIN);

    // again press and release b1

    // press b1
    now += 1;
    b1.Update(now, true);
    b2.Update(now, false);
    EXPECT_CALL(ui, Show_Ready(_));
    pom.Run(now);

    ASSERT_FALSE(pom.Is_Pomodoro());
    ASSERT_EQ(pom.Get_Current_Period_Minutes(), MO::Const::POM_BREAK_LONG_MIN);

    // release b1
    now += 1;
    b1.Update(now, false);
    b2.Update(now, false);
    EXPECT_CALL(ui, Show_Ready(_));
    pom.Run(now);

    ASSERT_TRUE(pom.Is_Pomodoro());
    ASSERT_EQ(pom.Get_Current_Period_Minutes(), MO::Const::POM_WORK_MIN);
}

// -----------------------------------------------------------------------------

TEST(pomodoro, pressing_b2)
{
    MO::UI_Mock ui;
    MO::Eeprom_Mock eeprom;
    MO::Button_Logic b1, b2;

    EXPECT_CALL(eeprom, Read(_));

    MO::Pomodoro pom(&ui, &b1, &b2, &eeprom);

    uint32_t now = 100;

    b1.Update(now, false);
    b2.Update(now, false);
    EXPECT_CALL(ui, Show_Ready(_));
    pom.Run(now);

    ASSERT_EQ(pom.Get_Pomodoros(), 0);
    ASSERT_TRUE(pom.Is_Pomodoro()); // type of timer
    ASSERT_EQ(pom.Get_Current_Period_Minutes(), MO::Const::POM_WORK_MIN);

    // press b2
    now += 1;
    b2.Update(now, false);
    b2.Update(now, true);
    EXPECT_CALL(ui, Show_Ready(_));
    pom.Run(now);

    ASSERT_TRUE(pom.Is_Pomodoro()); // type of timer
    ASSERT_EQ(pom.Get_Current_Period_Minutes(), MO::Const::POM_WORK_MIN);

    // release b2
    now += 1;
    b1.Update(now, false);
    b2.Update(now, false);
    EXPECT_CALL(ui, Show_Ready(_)); // still ready but we move to next state
    EXPECT_CALL(ui, Set_Beeper(MO::Const::POM_WORK_BEEPS));
    pom.Run(now);

    ASSERT_TRUE(pom.Is_Pomodoro()); // type of timer
    ASSERT_EQ(pom.Get_Current_Period_Minutes(), MO::Const::POM_WORK_MIN);

    // next step
    now += 1;
    b1.Update(now, false);
    b2.Update(now, false);
    EXPECT_CALL(ui, Show_Running(_));
    pom.Run(now);

    ASSERT_TRUE(pom.Is_Pomodoro()); // type of timer
    ASSERT_EQ(pom.Get_Current_Period_Minutes(), MO::Const::POM_WORK_MIN);
    ASSERT_EQ(pom.Get_Time_Left_Ms(), MO::Const::POM_WORK_MIN * 60 * 1000);

    // next step
    now += 10; // 10ms later
    b1.Update(now, false);
    b2.Update(now, false);
    EXPECT_CALL(ui, Show_Running(_));
    pom.Run(now);

    ASSERT_TRUE(pom.Is_Pomodoro()); // type of timer
    ASSERT_EQ(pom.Get_Current_Period_Minutes(), MO::Const::POM_WORK_MIN);
    ASSERT_EQ(pom.Get_Time_Left_Ms(), MO::Const::POM_WORK_MIN * 60 * 1000 - 10);

    // fast forward to the end
    now += MO::Const::POM_WORK_MIN * 60 * 1000 - 10;
    b1.Update(now, false);
    b2.Update(now, false);
    EXPECT_CALL(ui, Show_Running(_));
    pom.Run(now);

    ASSERT_TRUE(pom.Is_Pomodoro()); // type of timer
    ASSERT_EQ(pom.Get_Current_Period_Minutes(), MO::Const::POM_WORK_MIN);
    ASSERT_EQ(pom.Get_Time_Left_Ms(), 0);
    ASSERT_EQ(pom.Get_Pomodoros(), 0);

    // next step is the finished state
    now += 10; // 10ms later
    b1.Update(now, false);
    b2.Update(now, false);
    EXPECT_CALL(ui, Show_Finished(_));
    EXPECT_CALL(ui, Showing()).WillRepeatedly(Return(true));
    pom.Run(now);

    ASSERT_TRUE(pom.Is_Pomodoro()); // don't change type yet
    ASSERT_EQ(pom.Get_Current_Period_Minutes(), MO::Const::POM_WORK_MIN);
    ASSERT_EQ(pom.Get_Time_Left_Ms(), 0);
    ASSERT_EQ(pom.Get_Pomodoros(), 0); // don't update number yet

    // enough showing, move on
    now += 10; // 10ms later
    b1.Update(now, false);
    b2.Update(now, false);
    EXPECT_CALL(ui, Show_Finished(_));
    EXPECT_CALL(ui, Showing()).WillRepeatedly(Return(false)); // finished
    EXPECT_CALL(eeprom, Write(MO::Const::POM_SAVE_ADDRESS, 1));
    pom.Run(now);

    // we move to ready state, ready to fire short break
    ASSERT_FALSE(pom.Is_Pomodoro()); // don't change type yet
    ASSERT_EQ(pom.Get_Current_Period_Minutes(), MO::Const::POM_BREAK_SHORT_MIN);
    ASSERT_EQ(pom.Get_Time_Left_Ms(), MO::Const::POM_BREAK_SHORT_MIN * 60 * 1000);
    ASSERT_EQ(pom.Get_Pomodoros(), 1); // now the counter is up
}


