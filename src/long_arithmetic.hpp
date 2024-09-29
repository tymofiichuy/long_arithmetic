#pragma once

#include<stdint.h>

class long_int{
public:
    digit* digits;
    // unsigned char sign = true;

    // void operator>>(int);
    // void operator<<(int);
    bool operator==(long_int&);
    digit operator[](int);

    void reset();

    long_int();
    ~long_int();
};

class digit{
public:
    uint64_t value;

    void operator>>(int);
    void operator<<(int);
    //dynamic allocated memory!
    digit* digit_split();
    //dynamic allocated memory!
    digit* digit_mult(digit);

    digit(uint64_t = 0);
};

//next functions return is a new carry/borrow bit
unsigned char long_add(long_int&, long_int&, unsigned char, long_int&);
//unsigned char long_add(long_int& in1, long_int& in2, unsigned char carry_bit = 0, long_int& out);
unsigned char long_sub(long_int&, long_int&, unsigned char, long_int&);
//unsigned char long_sub(long_int& in1, long_int& in2, unsigned char borrow_bit = 0, long_int& out);

//void long_multiply_by_one_digit(long_int& long_in, digit digit_in, long_int& out);
void long_multiply_by_one_digit(long_int&, digit, long_int&);
// void long_sub_multiply(long_int& in1, long_int& in2, long_int& out);
// void long_super_multiply(long_int& in1, long_int& in2, long_int& out);
void long_multiply(long_int& in1, long_int& in2, long_int& out);