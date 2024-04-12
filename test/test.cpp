#include <gtest/gtest.h>

extern "C"
{
    #include "../include/MusicManager.h"
}

TEST(Authorization, return_dest)
{

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);

  std::cout << "TEST_DIR '" << TEST_DIR << "'" << std::endl;
  for (int i = 1; i < argc; ++i) {
      std::cout << "Input[" << i << "]: "<< argv[i] << std::endl;
  }

  return RUN_ALL_TESTS();
}
