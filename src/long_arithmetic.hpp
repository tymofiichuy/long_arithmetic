#pragma once

#include<stdint.h>

class long_int{
public:
    //!
    uint64_t* digits;
    // bool sign = true;

    void operator>>(int step);
    void operator<<(int step);

    long_int();
    ~long_int();
};

//next functions return is a new carry/borrow bit
bool long_add(long_int& in1, long_int& in2, bool carry_bit, long_int& out);
bool long_sub(long_int& in1, long_int& in2, bool borrow_bit, long_int& out);
//here must be comparison declaration
void long_multiply_by_one_digit(long_int& long_in, uint64_t digit_in, long_int& out);
void long_multiply(long_int& in1, long_int& in2, long_int& out);