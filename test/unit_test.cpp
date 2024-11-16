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
    EXPECT_EQ(x[i].value, 0);
  }
}

TEST(BasicFuncTest, SmallConstInitTest){
  uint64_t init_const = 0xFF;
  long_int x(init_const);

  EXPECT_EQ(x[0].value, init_const);
  for(int i = 1; i < 32; i++){
    EXPECT_EQ(x[i].value, 0);
  }
}

TEST(BasicFuncTest, InputTest){
  string input = "0x28a895cfd0200f098e2effaf19391c4a837ff1";
  uint64_t x0 = stoull("af19391c4a837ff1", nullptr, 16);
  uint64_t x1 = stoull("cfd0200f098e2eff", nullptr, 16);
  uint64_t x2 = stoull("28a895", nullptr, 16);
  long_int x;

  x.read_long_int(input);

  EXPECT_EQ(x[0].value, x0);
  EXPECT_EQ(x[1].value, x1);
  EXPECT_EQ(x[2].value, x2);
  for(int i = 3; i < 32; i++){
    EXPECT_EQ(x[i].value, 0);
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
  long_int x, y;
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
  long_int x, y;
  x.read_long_int(input);

  x.reset();

  EXPECT_TRUE(x == y);
}

TEST(BasicFuncTest, AssignmentTest){
  string input = "0x28a895cfd0200f098e2effaf19391c4a837ff1";
  long_int x, y;
  x.read_long_int(input);

  y = x;

  EXPECT_TRUE(x == y);
}

TEST(BasicFuncTest, UpperSuperShiftTest){
  string input = "0x28a895cfd0200f098e2effaf19391c4a837ff1";
  string shifted_input = "0x28a895cfd0200f098e2effaf19391c4a837ff100000000000000000000000000000000";
  long_int x, y;
  x.read_long_int(input);
  y.read_long_int(shifted_input);

  x.long_upper_super_shift(2);

  EXPECT_TRUE(x == y);
}

TEST(BasicFuncTest, LowerSuperShiftTest){
  string input = "0x28a895cfd0200f098e2effaf19391c4a837ff1";
  string shifted_input = "0x28a895";
  long_int x, y;
  x.read_long_int(input);
  y.read_long_int(shifted_input);

  x.long_lower_super_shift(2);

  EXPECT_TRUE(x == y);
}

TEST(BasicFuncTest, UpperShiftTest){
  string input = "0x28a895cfd0200f098e2effaf19391c4a837ff1";
  string shifted_input = "0x28a895cfd0200f098e2effaf19391c4a837ff100000000000000000";
  long_int x, y;
  x.read_long_int(input);
  y.read_long_int(shifted_input);

  x<<68;

  EXPECT_TRUE(x == y);
}

TEST(BasicFuncTest, LowerShiftTest){
  string input = "0x28a895cfd0200f098e2effaf19391c4a837ff1";
  string shifted_input = "0x28a895cfd0200f098e2ef";
  long_int x, y;
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
  long_int x, y, sum, exp_sum;
  x.read_long_int("0x20736a58fe16964aa40fbafbcb63175b370f70823dd4212");
  y.read_long_int("0x28a895cfd0200f098e2effaf19391c4a837ff1");
  exp_sum.read_long_int("0x20736a5900a11fa7a111bbec6446075628a30246e60c203");

  long_arithmetic::long_add(x, y, sum);

  EXPECT_TRUE(exp_sum == sum);
}

TEST(CoreFuncTest, SubTest){
  long_int x, y, dif, exp_dif;
  x.read_long_int("0x20736a58fe16964aa40fbafbcb63175b370f70823dd4212");
  y.read_long_int("0x28a895cfd0200f098e2effaf19391c4a837ff1");
  exp_dif.read_long_int("0x20736a58fb8c0ceda70dba0b32802760457bdebd959c221");

  long_arithmetic::long_sub(x, y, dif);

  EXPECT_TRUE(exp_dif == dif);
}

TEST(CoreFuncTest, DivTest){
  long_int x, y, quart, exp_quart, rem;
  x.read_long_int("0x20736a58fe16964aa40fbafbcb63175b370f70823dd4212");
  y.read_long_int("0x28a895cfd0200f098e2ef");
  exp_quart.read_long_int("0xcc5251a41ae5fc1717a0b6b139");

  long_arithmetic::long_divide(x, y, rem, quart);

  EXPECT_TRUE(quart == exp_quart);
}

TEST(CoreFuncTest, LowerEdgeDivTest){
  long_int x, quart, rem;
  long_int y(1);
  x.read_long_int("0x20736a58fe16964aa40fbafbcb63175b370f70823dd4212");

  long_arithmetic::long_divide(x, y, rem, quart);

  EXPECT_TRUE(quart == x);
}

TEST(CoreFuncTest, UpperEdgeDivTest){
  long_int x, quart, rem;
  long_int y(1);
  x.read_long_int("0x20736a58fe16964aa40fbafbcb63175b370f70823dd4212");

  long_arithmetic::long_divide(x, x, rem, quart);

  EXPECT_TRUE(quart == y);
}

TEST(CoreFuncTest, OneDigitMultTest){
  long_int x, carry, out, exp_out;
  digit y(~0ULL);
  x.read_long_int("0x20736a58fe16964aa40fbafbcb63175b370f70823dd4212");
  exp_out.read_long_int("0x20736a58fe16964a839c50a2cd4c811092ffb586727109c4c8f08f7dc22bdee");

  long_arithmetic::long_multiply_by_one_digit(x, y, carry, out);

  EXPECT_TRUE(out == exp_out);
}

TEST(CoreFuncTest, HalfMultTest){
  long_int x, y, out, exp_out;
  x.read_long_int("0x28a895cfd0200f098e2effaf19391c4a837ff199610c9bd4241b1a226effbc0ba1e4c9f81cd703a4212c02f96767adbc1e336b9d2cc5eccc98bd202bddc8fa5011f2df252fbb1843b3422db8f63129bad292c3b42a2402cf732500d8f0954fdc329c8a197a41fd984ca46b69caa59553ba92bacac9646d1a9c4508c3111f7ebf");
  y.read_long_int("0x20736a58fe16964aa40fbafbcb63175b370f70823dd4212ff42bfbc778478b757e15cb8f9eb1bc33ae07f2366f07c6bade3f8cb1745bd0622073c835d9ed17b9897730a542ab333ec3f25e91a36787064d30eb8c5a396d5345f580b8104249d9d90cf6a85a2ce2e09a2ef2df9308cc0c9f57ff7727e6b0f56294dafff4c3b994");
  exp_out.read_long_int("527675936b4e6e4773d22792fc1afce65449c28d4552f30b4eefa1011e5cb7f7011c54c47098fe75dfb16d7260590aec3974723a3544e1a7723f164029a68c5cec15489c1073f782952724d5a3cc3999a4c8f68b44bc2b0a63be922d554dd1a91e765e91d76008d0ad7b2653e32f0d6ff1ae6fe9bea0b8ec48d257d5a49c57bcefb27563e5d82fd3bc29951c8fe32ec1d0744aacbfb3ef4643ca9e98b25492e843b15aeffe55b28c0e49cbf850486b0133c9c65063e3fc28b0b919cd9b921b399b9ac12f6e33d9229c950a906a98d44b3ec67ef2d2b4834421d9c1cbff614a8aeb0b765d6c3e570683adeeab5d2f4b97d239cf3ab8d8ba818dffe32404a4d6c");
  
  long_arithmetic::long_half_multiply(x, y, out);

  EXPECT_TRUE(out == exp_out);
}

TEST(CoreFuncTest, ShortMultTest){
  long_int x, y, out, exp_out;
  x.read_long_int("0x28a895cfd0200f098e2effaf19391c4a837ff199610c9bd4241b1a226effbc0ba1e4c9f81cd703a4212c02f96767adbc1e336b9d2cc5eccc98bd202bddc8fa5011f2df252fbb1843b3422db8f63129bad292c3b42a2402cf732500d8f0954fdc329c8a197a41fd984ca46b69caa59553ba92bacac9646d1a9c4508c3111f7ebf");
  y.read_long_int("0x20736a58fe16964aa40fbafbcb63175b370f70823dd4212ff42bfbc778478b757e15cb8f9eb1bc33ae07f2366f07c6bade3f8cb1745bd0622073c835d9ed17b9897730a542ab333ec3f25e91a36787064d30eb8c5a396d5345f580b8104249d9d90cf6a85a2ce2e09a2ef2df9308cc0c9f57ff7727e6b0f56294dafff4c3b994");
  exp_out.read_long_int("527675936b4e6e4773d22792fc1afce65449c28d4552f30b4eefa1011e5cb7f7011c54c47098fe75dfb16d7260590aec3974723a3544e1a7723f164029a68c5cec15489c1073f782952724d5a3cc3999a4c8f68b44bc2b0a63be922d554dd1a91e765e91d76008d0ad7b2653e32f0d6ff1ae6fe9bea0b8ec48d257d5a49c57bcefb27563e5d82fd3bc29951c8fe32ec1d0744aacbfb3ef4643ca9e98b25492e843b15aeffe55b28c0e49cbf850486b0133c9c65063e3fc28b0b919cd9b921b399b9ac12f6e33d9229c950a906a98d44b3ec67ef2d2b4834421d9c1cbff614a8aeb0b765d6c3e570683adeeab5d2f4b97d239cf3ab8d8ba818dffe32404a4d6c");
  
  long_arithmetic::long_multiply(x, y, out);

  EXPECT_TRUE(out == exp_out);
}

TEST(CoreFuncTest, ShortMultReturnSizeTest){
  long_int x, y, out;
  x.read_long_int("0x28a895cfd0200f098e2effaf19391c4a837ff199610c9bd4241b1a226effbc0ba1e4c9f81cd703a4212c02f96767adbc1e336b9d2cc5eccc98bd202bddc8fa5011f2df252fbb1843b3422db8f63129bad292c3b42a2402cf732500d8f0954fdc329c8a197a41fd984ca46b69caa59553ba92bacac9646d1a9c4508c3111f7ebf");
  y.read_long_int("0x20736a58fe16964aa40fbafbcb63175b370f70823dd4212ff42bfbc778478b757e15cb8f9eb1bc33ae07f2366f07c6bade3f8cb1745bd0622073c835d9ed17b9897730a542ab333ec3f25e91a36787064d30eb8c5a396d5345f580b8104249d9d90cf6a85a2ce2e09a2ef2df9308cc0c9f57ff7727e6b0f56294dafff4c3b994");

  long_arithmetic::long_multiply(x, y, out);

  EXPECT_TRUE(out.get_size() == 32);
}

TEST(CoreFuncTest, GeneralMultTest){
  long_int x, y, out, exp_out(0, 64);
  x.read_long_int("0x28a895cfd0200f098e2effaf19391c4a837ff199610c9bd4241b1a226effbc0ba1e4c9f81cd703a4212c02f96767adbc1e336b9d2cc5eccc98bd202bddc8fa5011f2df252fbb1843b3422db8f63129bad292c3b42a2402cf732500d8f0954fdc329c8a197a41fd984ca46b69caa59553ba92bacac9646d1a9c4508c3111f7ebf20736a58fe16964aa40fbafbcb63175b370f70823dd4212ff42bfbc778478b757e15cb8f9eb1bc33ae07f2366f07c6bade3f8cb1745bd0622073c835d9ed17b9897730a542ab333ec3f25e91a36787064d30eb8c5a396d5345f580b8104249d9d90cf6a85a2ce2e09a2ef2df9308cc0c9f57ff7727e6b0f56294dafff4c3b994");
  y.read_long_int("0x57e15cb8f9eb1bc33ae07f2c0c9f57ff7727e6b0f56294dafff4c3b994");
  exp_out.read_long_int("0xdf515cf42147e5403ee4c1e1f7f65f7c690cde3c7bac983fb0f75267dba5154ef1725f22857c22911bc08ae20aac2d843436aaec588db3cedbefd856cc2a0a43af67eeb087805af52f5c138ad142f7a1c742ed565976a49777fa189f9ead30e4f266ca0d262b890d9737cd37af47a08a15dd7beda6c312da8fec7305dccb0dd6d99ab47aea24fbd2d6bfe43c132312a9426904d6e7f59d8b8c6c2f9ceb516c950cfeb2850be8edda06c40a6f732d1c1e226e2820948216d98b2805bd25ee197a84e8bfee1ee4fbc9f875d4af2db4a75055037623a4a3893b8ee1444421e48bfa49ac013a539f41b81c86f6b34b5931391466163880f9027ac0c77021dc6cb190ae66dbafa3f19ef431d2697f778c43e86166e7e72c321743e5dff3d90");

  long_arithmetic::long_multiply(x, y, out);

  EXPECT_TRUE(out == exp_out);
}

TEST(CoreFuncTest, GeneralMultReturnSizeTest){
  long_int x, y, out, exp_out(0, 64);
  x.read_long_int("0x28a895cfd0200f098e2effaf19391c4a837ff199610c9bd4241b1a226effbc0ba1e4c9f81cd703a4212c02f96767adbc1e336b9d2cc5eccc98bd202bddc8fa5011f2df252fbb1843b3422db8f63129bad292c3b42a2402cf732500d8f0954fdc329c8a197a41fd984ca46b69caa59553ba92bacac9646d1a9c4508c3111f7ebf20736a58fe16964aa40fbafbcb63175b370f70823dd4212ff42bfbc778478b757e15cb8f9eb1bc33ae07f2366f07c6bade3f8cb1745bd0622073c835d9ed17b9897730a542ab333ec3f25e91a36787064d30eb8c5a396d5345f580b8104249d9d90cf6a85a2ce2e09a2ef2df9308cc0c9f57ff7727e6b0f56294dafff4c3b994");
  y.read_long_int("0x57e15cb8f9eb1bc33ae07f2c0c9f57ff7727e6b0f56294dafff4c3b994");

  long_arithmetic::long_multiply(x, y, out);

  EXPECT_TRUE(out.get_size() == 64);
}

TEST(ModFuncTest, GCDTest){
  long_int x, y, out, exp_out(4);
  x.read_long_int("0x28a895cfd0200f098e2effaf19391c4a837ff199610c9bd4241b1a226effbc0ba1e4c9f81cd703a4212c02f96767adbc1e336b9d2cc5eccc98bd202bddc8fa5011f2df252fbb1843b3422db8f63129bad292c3b42a2402cf732500d8f0954fdc329c8a197a41fd984ca46b69caa59553ba92bacac9646d1a9c4508c3111f7ebf20736a58fe16964aa40fbafbcb63175b370f70823dd4212ff42bfbc778478b757e15cb8f9eb1bc33ae07f2366f07c6bade3f8cb1745bd0622073c835d9ed17b9897730a542ab333ec3f25e91a36787064d30eb8c5a396d5345f580b8104249d9d90cf6a85a2ce2e09a2ef2df9308cc0c9f57ff7727e6b0f56294dafff4c3b994");
  y.read_long_int("0x57e15cb8f9eb1bc33ae07f2c0c9f57ff7727e6b0f56294dafff4c3b994");

  modular_arithmetic::steins_algorithm(x, y, out);

  EXPECT_TRUE(out == exp_out);
}

TEST(ModFuncTest, LCMTest){
  long_int x, y, out, exp_out(0, 64);
  x.read_long_int("0x28a895cfd0200f098e2effaf19391c4a837ff199610c9bd4241b1a226effbc0ba1e4c9f81cd703a4212c02f96767adbc1e336b9d2cc5eccc98bd202bddc8fa5011f2df252fbb1843b3422db8f63129bad292c3b42a2402cf732500d8f0954fdc329c8a197a41fd984ca46b69caa59553ba92bacac9646d1a9c4508c3111f7ebf20736a58fe16964aa40fbafbcb63175b370f70823dd4212ff42bfbc778478b757e15cb8f9eb1bc33ae07f2366f07c6bade3f8cb1745bd0622073c835d9ed17b9897730a542ab333ec3f25e91a36787064d30eb8c5a396d5345f580b8104249d9d90cf6a85a2ce2e09a2ef2df9308cc0c9f57ff7727e6b0f56294dafff4c3b994");
  y.read_long_int("0x57e15cb8f9eb1bc33ae07f2c0c9f57ff7727e6b0f56294dafff4c3b994");
  exp_out.read_long_int("0x37d4573d0851f9500fb930787dfd97df1a43378f1eeb260fec3dd499f6e94553bc5c97c8a15f08a446f022b882ab0b610d0daabb16236cf3b6fbf615b30a8290ebd9fbac21e016bd4bd704e2b450bde871d0bb55965da925ddfe8627e7ab4c393c99b283498ae24365cdf34debd1e82285775efb69b0c4b6a3fb1cc17732c375b666ad1eba893ef4b5aff90f04c8c4aa509a4135b9fd6762e31b0be73ad45b25433faca142fa3b7681b1029bdccb4707889b8a08252085b662ca016f497b865ea13a2ffb87b93ef27e1d752bcb6d29d41540dd88e928e24ee3b85111087922fe926b004e94e7d06e0721bdacd2d64c4e4519858e203e409eb031dc08771b2c642b99b6ebe8fc67bd0c749a5fdde310fa1859b9f9cb0c85d0f977fcf64");

  modular_arithmetic::lcm(x, y, out);

  EXPECT_TRUE(out == exp_out);
}

TEST(ModFuncTest, LongModBarrettTest){
  long_int x, mod, mu, out, exp_out;
  x.read_long_int("0x28a895cfd0200f098e2effaf19391c4a837ff199610c9bd4241b1a226effbc0ba1e4c9f81cd703a4212c02f96767adbc1e336b9d2cc5eccc98bd202bddc8fa5011f2df252fbb1843b3422db8f63129bad292c3b42a2402cf732500d8f0954fdc329c8a197a41fd984ca46b69caa59553ba92bacac9646d1a9c4508c3111f7ebf20736a58fe16964aa40fbafbcb63175b370f70823dd4212ff42bfbc778478b757e15cb8f9eb1bc33ae07f2366f07c6bade3f8cb1745bd0622073c835d9ed17b9897730a542ab333ec3f25e91a36787064d30eb8c5a396d5345f580b8104249d9d90cf6a85a2ce2e09a2ef2df9308cc0c9f57ff7727e6b0f56294dafff4c3b994");
  mod.read_long_int("0xf252fbb1843b3422db8f63129bad292c3b42a2402cf732500d8f0954fdc329c8a197a41fd984ca46b69caa59553ba92bacac9646d1a9c4508c3111f7ebf20736a58fe16964aa40fbafbcb63175b370f70823dd4212ff42bfbc778478b757e15cb8f9eb1bc33ae07f2366f07c6bade3f8cb1745bd0622073c835d9ed17b989773391c4a837ff199610c9bd4241b1a226effbc0ba1e4c9");
  exp_out.read_long_int("0x6eb9b87fc7fc2e1f15392733ea8e7395cfea70223278a9d2f56e6bb80fe9b80a97320c741688277bf3f1f1cf7b630d27d487f6251ef74beef4889aed705d43f95dd610aefa8d599d8d7975535c80b02877291cde67d55da6ef98298c6c4aaecb0bbac2fc126948e3138c271e020b7309e7d3c33a2531553dcf1f853574ace4d65ac11530126f9b4ff237c05cdd236997ef6c1003fbd2");
  
  modular_arithmetic::mu_calc(x, mod, mu);
  modular_arithmetic::barrett_reduction(x, mod, mu, out);
  
  EXPECT_TRUE(out == exp_out);
}

TEST(ModFuncTest, GetHighTest){
  long_int x, out, exp_out;
  x.read_long_int("0x28a895cfd0200f098e2effaf19391c4a837ff199610c9bd4241b1a226effbc0ba1e4c9f81cd703a4212c02f96767adbc1e336b9d2cc5eccc98bd202bddc8fa5011f2df252fbb1843b3422db8f63129bad292c3b42a2402cf732500d8f0954fdc329c8a197a41fd984ca46b69caa59553ba92bacac9646d1a9c4508c3111f7ebf20736a58fe16964aa40fbafbcb63175b370f70823dd4212ff42bfbc778478b757e15cb8f9eb1bc33ae07f2366f07c6bade3f8cb1745bd0622073c835d9ed17b9897730a542ab333ec3f25e91a36787064d30eb8c5a396d5345f580b8104249d9d90cf6a85a2ce2e09a2ef2df9308cc0c9f57ff7727e6b0f56294dafff4c3b994");
  exp_out.read_long_int("0x28a895cfd0200f098e2effaf19391c4a"); 
  
  x.get_high(out, 2);

  EXPECT_TRUE(out==exp_out);
}

TEST(ModFuncTest, RewriteHighTest){
  long_int x, y(0, 2), exp_out;
  x.read_long_int("0x28a895cfd0200f098e2effaf19391c4a837ff199610c9bd4241b1a226effbc0ba1e4c9f81cd703a4212c02f96767adbc1e336b9d2cc5eccc98bd202bddc8fa5011f2df252fbb1843b3422db8f63129bad292c3b42a2402cf732500d8f0954fdc329c8a197a41fd984ca46b69caa59553ba92bacac9646d1a9c4508c3111f7ebf20736a58fe16964aa40fbafbcb63175b370f70823dd4212ff42bfbc778478b757e15cb8f9eb1bc33ae07f2366f07c6bade3f8cb1745bd0622073c835d9ed17b9897730a542ab333ec3f25e91a36787064d30eb8c5a396d5345f580b8104249d9d90cf6a85a2ce2e09a2ef2df9308cc0c9f57ff7727e6b0f56294dafff4c3b994");
  y.read_long_int("0x38a895cfd0200f098e2effaf19391c4a");
  exp_out.read_long_int("0x38a895cfd0200f098e2effaf19391c4a837ff199610c9bd4241b1a226effbc0ba1e4c9f81cd703a4212c02f96767adbc1e336b9d2cc5eccc98bd202bddc8fa5011f2df252fbb1843b3422db8f63129bad292c3b42a2402cf732500d8f0954fdc329c8a197a41fd984ca46b69caa59553ba92bacac9646d1a9c4508c3111f7ebf20736a58fe16964aa40fbafbcb63175b370f70823dd4212ff42bfbc778478b757e15cb8f9eb1bc33ae07f2366f07c6bade3f8cb1745bd0622073c835d9ed17b9897730a542ab333ec3f25e91a36787064d30eb8c5a396d5345f580b8104249d9d90cf6a85a2ce2e09a2ef2df9308cc0c9f57ff7727e6b0f56294dafff4c3b994"); 
  
  x.rewrite_high(y);
  
  EXPECT_TRUE(x==exp_out);
}

TEST(ModFuncTest, ShortModBarrettTest){
  long_int x, mod, mu, out, exp_out;
  x.read_long_int("0x28a895cfd0200f098e2effaf19391c4a837ff199610c9bd4241b1a226effbc0ba1e4c9f81cd703a4212c02f96767adbc1e336b9d2cc5eccc98bd202bddc8fa5011f2df252fbb1843b3422db8f63129bad292c3b42a2402cf732500d8f0954fdc329c8a197a41fd984ca46b69caa59553ba92bacac9646d1a9c4508c3111f7ebf20736a58fe16964aa40fbafbcb63175b370f70823dd4212ff42bfbc778478b757e15cb8f9eb1bc33ae07f2366f07c6bade3f8cb1745bd0622073c835d9ed17b9897730a542ab333ec3f25e91a36787064d30eb8c5a396d5345f580b8104249d9d90cf6a85a2ce2e09a2ef2df9308cc0c9f57ff7727e6b0f56294dafff4c3b994");
  mod.read_long_int("0xfe16964aa40fbafbcb63175b370f70823dd4212ff42bfbc778478b757e15cb8f9eb1bc33ae07f2366f07c6bade3f8cb1745bd0622073c835d9ed17b989773391c4a837ff199610c9bd4241b1a226effbc0ba1e4c9");
  exp_out.read_long_int("0xa61c4c88c6decc318c2fd5c6f514f32febd2c96ad61ead7fda270983f083abcba797855bf664edd846e91806f3dbb691f03ee9ef33b49c7dcf45734dfed7e989c5f593dfa193a273618c3feedd8d02d24d709b66b");
  modular_arithmetic::mu_calc(x, mod, mu);
  modular_arithmetic::barrett_reduction(x, mod, mu, out);
  EXPECT_TRUE(out == exp_out);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}