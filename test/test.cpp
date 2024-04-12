#include "gtest/gtest.h"
#include "../include/MusicManager.h"

TEST(DateToNumberTest, BasicTest)
{
    EXPECT_EQ(date_to_number(1, 1, 2000), 946684800);
}

int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}


