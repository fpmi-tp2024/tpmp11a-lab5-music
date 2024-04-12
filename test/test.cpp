#include "gtest/gtest.h"
#include "../include/MusicManager.h"

TEST(DateToNumberTest, January1st2000)
{
    EXPECT_EQ(date_to_number(1, 1, 2000), 946684800);
}

TEST(DateToNumberTest, January1st1970)
{
    EXPECT_EQ(date_to_number(1, 1, 1970), 0);
}

TEST(DateToNumberTest, December31st2037)
{
    EXPECT_EQ(date_to_number(31, 12, 2037), 2147483647);
}

TEST(DateToNumberTest, February29th2000)
{
    EXPECT_EQ(date_to_number(29, 2, 2000), 951868800);
}

TEST(DateToNumberTest, March31st2024)
{
    EXPECT_EQ(date_to_number(31, 3, 2024), 1707756800);
}

TEST(DateToNumberTest, November15th1995)
{
    EXPECT_EQ(date_to_number(15, 11, 1995), 815905200);
}

TEST(DateToNumberTest, August8th1988)
{
    EXPECT_EQ(date_to_number(8, 8, 1988), 586051200);
}

TEST(DateToNumberTest, October17th2038)
{
    EXPECT_EQ(date_to_number(17, 10, 2038), 2147483647);
}

TEST(DateToNumberTest, January1st1601)
{
    EXPECT_EQ(date_to_number(1, 1, 1601), -11644547200);
}

TEST(DateToNumberTest, December31st9999)
{
    EXPECT_EQ(date_to_number(31, 12, 9999), 253402300799);
}

int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}


