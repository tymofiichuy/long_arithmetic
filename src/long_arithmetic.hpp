#pragma once

#include<stdint.h>
#include<string>

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

class long_int{
public:
    digit* digits;
    int size = 32;

    //shift whithin digits
    void long_upper_sub_shift(int);
    void long_lower_sub_shift(int);
    //digit shift
    void long_upper_super_shift(int);
    void long_lower_super_shift(int);

    void read_long_int(std::string);
    void print_int();

    void operator>>(int);
    void operator<<(int);
    bool operator==(long_int&);
    long_int& operator=(long_int&);
    digit& operator[](int);

    //void split(long_int* out, int iter);

    void reset();
    int bit_length();

    long_int(uint64_t init_value = 0);
    ~long_int();
};

//next functions return is a last carry/borrow bit
unsigned char long_add(long_int& in1, long_int& in2, long_int& out, unsigned char carry_bit = 0);
//unsigned char long_add(long_int& in1, long_int& in2, unsigned char carry_bit = 0, long_int& out);
unsigned char long_sub(long_int& in1, long_int& in2, long_int& out, unsigned char borrow_bit = 0);
//unsigned char long_sub(long_int& in1, long_int& in2, unsigned char borrow_bit = 0, long_int& out);

//return carry from long_add?
void long_multiply_by_one_digit(long_int&, digit, long_int&, long_int&);
//digit multiplication
void long_sub_multiply(long_int& in1, long_int& in2, long_int& out);
//karatsuba multiplication
//void long_super_multiply(long_int& in1, long_int& in2, long_int& out, int iter);
//optimized combined method
//void long_multiply(long_int& in1, long_int& in2, long_int& out);

void long_divide(long_int& in1, long_int& in2, long_int& remainder, int& quarter);

//window method, 4 bit
void long_power(long_int& in1, long_int& in2, long_int& out);