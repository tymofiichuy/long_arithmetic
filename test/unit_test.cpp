#include <iostream>
#include <gtest/gtest.h>
#include <fstream>
#include <sstream>
#include "long_arithmetic.hpp"

using namespace std;

TEST(StructureTest, LNKTest){
  EXPECT_EQ(1, 1);
}

TEST(BasicFuncTest, InitTest){
  long_int x;

  for(int i = 0; i < 32; i++){
    EXPECT_EQ(x.digits[i].value, 0);
  }
}

TEST(BasicFuncTest, SmallConstInitTest){
  uint64_t init_const = 0xFF;
  long_int x(init_const);

  EXPECT_EQ(x.digits[0].value, init_const);
  for(int i = 1; i < 32; i++){
    EXPECT_EQ(x.digits[i].value, 0);
  }
}

TEST(BasicFuncTest, InputTest){
  string input = "0x28a895cfd0200f098e2effaf19391c4a837ff1";
  uint64_t x0 = stoull("af19391c4a837ff1", nullptr, 16);
  uint64_t x1 = stoull("cfd0200f098e2eff", nullptr, 16);
  uint64_t x2 = stoull("28a895", nullptr, 16);
  long_int x;

  x.read_long_int(input);

  EXPECT_EQ(x.digits[0].value, x0);
  EXPECT_EQ(x.digits[1].value, x1);
  EXPECT_EQ(x.digits[2].value, x2);
  for(int i = 3; i < 32; i++){
    EXPECT_EQ(x.digits[i].value, 0);
  }
}

TEST(BasicFuncTest, OutputTest){
  string input = "0x28a895cfd0200f098e2effaf19391c4a837ff1";
  string exp_output = "0x28a895cfd0200f098e2effaf19391c4a837ff1\n";
  long_int x;
  x.read_long_int(input);

  streambuf* oldCoutStreamBuf = cout.rdbuf();
	stringstream stringStream;
	cout.rdbuf(stringStream.rdbuf());

  x.print_int();

  string content = stringStream.str();
	cout.rdbuf(oldCoutStreamBuf);

  EXPECT_EQ(content, exp_output);
}

TEST(BasicFuncTest, EqualtyOperatorTest){
  string input = "0x28a895cfd0200f098e2effaf19391c4a837ff1";
  long_int x;
  long_int y;
  x.read_long_int(input);
  y.read_long_int(input);

  EXPECT_TRUE(x == y);
}

TEST(BasicFuncTest, SubscriptOperatorTest){
  string input = "0x28a895cfd0200f098e2effaf19391c4a837ff1";
  long_int x;
  x.read_long_int(input);
  uint64_t x1 = stoull("cfd0200f098e2eff", nullptr, 16);

  EXPECT_EQ(x[1].value, x1);
}

TEST(BasicFuncTest, ResetTest){
  string input = "0x28a895cfd0200f098e2effaf19391c4a837ff1";
  long_int x;
  long_int y;
  x.read_long_int(input);

  x.reset();

  EXPECT_TRUE(x == y);
}

TEST(BasicFuncTest, AssignmentTest){
  string input = "0x28a895cfd0200f098e2effaf19391c4a837ff1";
  long_int x;
  long_int y;
  x.read_long_int(input);

  y = x;

  EXPECT_TRUE(x == y);
}

TEST(BasicFuncTest, UpperSuperShiftTest){
  string input = "0x28a895cfd0200f098e2effaf19391c4a837ff1";
  string shifted_input = "0x28a895cfd0200f098e2effaf19391c4a837ff100000000000000000000000000000000";
  long_int x;
  long_int y;
  x.read_long_int(input);
  y.read_long_int(shifted_input);

  x.long_upper_super_shift(2);

  EXPECT_TRUE(x == y);
}

TEST(BasicFuncTest, LowerSuperShiftTest){
  string input = "0x28a895cfd0200f098e2effaf19391c4a837ff1";
  string shifted_input = "0x28a895";
  long_int x;
  long_int y;
  x.read_long_int(input);
  y.read_long_int(shifted_input);

  x.long_lower_super_shift(2);

  EXPECT_TRUE(x == y);
}

TEST(BasicFuncTest, UpperShiftTest){
  string input = "0x28a895cfd0200f098e2effaf19391c4a837ff1";
  string shifted_input = "0x28a895cfd0200f098e2effaf19391c4a837ff100000000000000000";
  long_int x;
  long_int y;
  x.read_long_int(input);
  y.read_long_int(shifted_input);

  x<<68;

  EXPECT_TRUE(x == y);
}

TEST(BasicFuncTest, LowerShiftTest){
  string input = "0x28a895cfd0200f098e2effaf19391c4a837ff1";
  string shifted_input = "0x28a895cfd0200f098e2ef";
  long_int x;
  long_int y;
  x.read_long_int(input);
  y.read_long_int(shifted_input);

  x>>68;

  EXPECT_TRUE(x == y);
}

TEST(BasicFuncTest, BitLengthTest){
  long_int x(1);
  x<<175;

  EXPECT_TRUE(x.bit_length() == 176);
}

TEST(BasicFuncTest, SetBitTest){
  long_int x(1);
  long_int y;
  x<<68;
  y.set_bit(1, 68);

  EXPECT_TRUE(x == y);
}

TEST(BasicFuncTest, SetLastDigitBitTest){
  long_int x(1);
  long_int y;
  x<<64;
  y.set_bit(1, 64);

  EXPECT_TRUE(x == y);
}

TEST(CoreFuncTest, AddTest){
  long_int x;
  long_int y;
  long_int sum;
  long_int exp_sum;
  x.read_long_int("0x20736a58fe16964aa40fbafbcb63175b370f70823dd4212");
  y.read_long_int("0x28a895cfd0200f098e2effaf19391c4a837ff1");
  exp_sum.read_long_int("0x20736a5900a11fa7a111bbec6446075628a30246e60c203");

  long_add(x, y, sum);

  EXPECT_TRUE(exp_sum == sum);
}

TEST(CoreFuncTest, SubTest){
  long_int x;
  long_int y;
  long_int dif;
  long_int exp_dif;
  x.read_long_int("0x20736a58fe16964aa40fbafbcb63175b370f70823dd4212");
  y.read_long_int("0x28a895cfd0200f098e2effaf19391c4a837ff1");
  exp_dif.read_long_int("0x20736a58fb8c0ceda70dba0b32802760457bdebd959c221");

  long_sub(x, y, dif);

  EXPECT_TRUE(exp_dif == dif);
}

TEST(CoreFuncTest, DivTest){
  long_int x;
  long_int y;
  long_int quart;
  long_int exp_quart;
  long_int rem;
  x.read_long_int("0x20736a58fe16964aa40fbafbcb63175b370f70823dd4212");
  y.read_long_int("0x28a895cfd0200f098e2ef");
  exp_quart.read_long_int("0xcc5251a41ae5fc1717a0b6b139");

  long_divide(x, y, rem, quart);

  EXPECT_TRUE(quart == exp_quart);
}

TEST(CoreFuncTest, LowerEdgeDivTest){
  long_int x;
  long_int y(1);
  long_int quart;
  long_int rem;
  x.read_long_int("0x20736a58fe16964aa40fbafbcb63175b370f70823dd4212");

  long_divide(x, y, rem, quart);

  EXPECT_TRUE(quart == x);
}

TEST(CoreFuncTest, UpperEdgeDivTest){
  long_int x;
  long_int y(1);
  long_int quart;
  long_int rem;
  x.read_long_int("0x20736a58fe16964aa40fbafbcb63175b370f70823dd4212");

  long_divide(x, x, rem, quart);

  EXPECT_TRUE(quart == y);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}