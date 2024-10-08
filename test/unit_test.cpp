#include <iostream>
#include <gtest/gtest.h>
#include "long_arithmetic.hpp"

using namespace std;

TEST(StructureTest, LNKTest){
  EXPECT_EQ(1, 1);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}