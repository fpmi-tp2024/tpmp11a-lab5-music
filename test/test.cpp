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
    EXPECT_EQ(date_to_number(31, 12, 2010), 1293753600);
}

TEST(DateToNumberTest, February29th2012)
{
    EXPECT_EQ(date_to_number(29, 2, 2012), 1330473600);
}

TEST(DateToNumberTest, April15th2015)
{
    EXPECT_EQ(date_to_number(15, 4, 2015), 1429056000);
}

TEST(DateToNumberTest, June30th2005)
{
    EXPECT_EQ(date_to_number(30, 6, 2005), 1120089600);
}

TEST(DateToNumberTest, September15th2006)
{
    EXPECT_EQ(date_to_number(15, 9, 2006), 1158278400);
}

TEST(DateToNumberTest, October20th2007)
{
    EXPECT_EQ(date_to_number(20, 10, 2007), 1192838400);
}

TEST(DateToNumberTest, November5th2008)
{
    EXPECT_EQ(date_to_number(5, 11, 2008), 1225843200);
}

TEST(DateToNumberTest, December31st2009)
{
    EXPECT_EQ(date_to_number(31, 12, 2009), 1262217600);
}

int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}


