#include "gtest/gtest.h"
#include "../include/MusicManager.h"

TEST(DateToNumberTest, January1st2000)
{
    EXPECT_EQ(date_to_number(1, 1, 2000), 946684800);
}

TEST(DateToNumberTest, January1st2005)
{
    EXPECT_EQ(date_to_number(1, 1, 2005), 1104537600);
}

TEST(DateToNumberTest, December31st2010)
{
    EXPECT_EQ(date_to_number(31, 12, 2010), 1293840000);
}

TEST(DateToNumberTest, February29th2012)
{
    EXPECT_EQ(date_to_number(29, 2, 2012), 1330512000);
}

TEST(DateToNumberTest, April15th2015)
{
    EXPECT_EQ(date_to_number(15, 4, 2015), 1429046400);
}

TEST(DateToNumberTest, September8th2020)
{
    EXPECT_EQ(date_to_number(8, 9, 2020), 1599532800);
}

TEST(DateToNumberTest, October17th2023)
{
    EXPECT_EQ(date_to_number(17, 10, 2023), 1676550400);
}

TEST(DateToNumberTest, January1st2024)
{
    EXPECT_EQ(date_to_number(1, 1, 2024), 1672531200);
}

TEST(DateToNumberTest, November30th2024)
{
    EXPECT_EQ(date_to_number(30, 11, 2024), 1706691200);
}

TEST(DateToNumberTest, December31st2024)
{
    EXPECT_EQ(date_to_number(31, 12, 2024), 1707356800);
}

int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}


