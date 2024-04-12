#include "gtest/gtest.h"
#include "../include/MusicManager.h"

TEST(Test, BasicTest)
{
    EXPECT_EQ(testFunc1(5), 15);
}

int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}


