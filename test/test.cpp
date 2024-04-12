#include "gtest/gtest.h"
#include "../include/MusicManager.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "../sqlite/sqlite3.h"

TEST(Test, BasicTest)
{
    EXPECT_EQ(date_to_number(1, 1, 2000), 946684800);
}

int main()
{
    ::testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}


