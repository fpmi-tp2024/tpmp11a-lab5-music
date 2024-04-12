#include "gtest/gtest.h"
#include "../include/MusicManager.h"

TEST(DateToNumberTest, January1st2000)
{
    EXPECT_EQ(date_to_number(1, 1, 2000), 946674000);
}

TEST(DateToNumberTest, January1st2005)
{
    EXPECT_EQ(date_to_number(1, 1, 2005), 1104526800);
}

TEST(DateToNumberTest, December31st2010)
{
    EXPECT_EQ(date_to_number(31, 12, 2010), 1293742800);
}

TEST(DateToNumberTest, February29th2012)
{
    EXPECT_EQ(date_to_number(29, 2, 2012), 1330462800);
}

TEST(DateToNumberTest, April15th2015)
{
    EXPECT_EQ(date_to_number(15, 4, 2015), 1429045200);
}

TEST(DateToNumberTest, June30th2005)
{
    EXPECT_EQ(date_to_number(30, 6, 2005), 1120078800);
}

TEST(DateToNumberTest, September15th2006)
{
    EXPECT_EQ(date_to_number(15, 9, 2006), 1158267600);
}

TEST(DateToNumberTest, October20th2007)
{
    EXPECT_EQ(date_to_number(20, 10, 2007), 1192827600);
}

TEST(DateToNumberTest, November5th2008)
{
    EXPECT_EQ(date_to_number(5, 11, 2008), 1225832400);
}

TEST(DateToNumberTest, December31st2009)
{
    EXPECT_EQ(date_to_number(31, 12, 2009), 1262206800);
}

int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}


