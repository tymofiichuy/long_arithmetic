#pragma once

#include<stdint.h>
#include<string>

class digit{
private:
    void operator>>(int);
    void operator<<(int);
    //dynamic allocated memory!
    digit* digit_split();
    //dynamic allocated memory!
    digit* digit_mult(digit);
public:
    uint64_t value;
    digit(uint64_t = 0);

    friend class long_arithmetic;
    friend class long_int;
};

class long_int{
private:
    digit* digits;
    //should make adaptive size!
    int size;
public:
//Shifts and bit/digit operations
    //shift whithin digits
    void long_upper_sub_shift(int);
    void long_lower_sub_shift(int);
    //digit shift
    void long_upper_super_shift(int);
    void long_lower_super_shift(int);
    void set_bit(int value, int position);
    bool even();
    void reset();
    int digit_length();
    int bit_length();
    int get_size();  

//IO
    void read_long_int(std::string);
    void print_int();

//Adaptive size
    void resize(int new_size);
    void resize_erase(int new_size);

//Operators
    void operator>>(int);
    void operator<<(int);
    bool operator==(long_int&);
    long_int& operator=(long_int&);
    //recheck
    long_int& operator=(long_int&&);
    digit& operator[](int);

//Integer split
    void split(long_int& out1, long_int& out2);

//Partition
    void get_high(long_int& out, int part);
    void rewrite_high(long_int& in);

//Constructors/Destructor
    //make size a power of 2?
    long_int(uint64_t init_value = 0, uint8_t init_size = 32);
    long_int(long_int&);
    ~long_int();

    friend class long_arithmetic;
    friend class modular_arithmetic;
};

class long_arithmetic{
public:
    static void adjust_size(long_int& in1, long_int& in2);
    //next functions return is a last carry/borrow bit
    static unsigned char long_add(long_int in1, long_int in2, long_int& out, unsigned char carry_bit = 0);
    static unsigned char long_sub(long_int in1, long_int in2, long_int& out, unsigned char borrow_bit = 0);

    //needs adjustment!
    static void long_multiply_by_one_digit(long_int& long_in, digit digit_in, long_int& carry, long_int& out);
    static void long_half_multiply(long_int& in1, long_int& in2, long_int& out);
    static void long_multiply(long_int in1, long_int in2, long_int& out);

    static void long_divide(long_int in1, long_int in2, long_int& remainder, long_int& quarter);

    //window method, 4 bit
    //static void long_power(long_int& in1, long_int& in2, long_int& out);
};

class modular_arithmetic{
public:
    //calculate u/v coefficients?
    //return a bool value: 1 if numbers are coprime, 0 if not?
    static void steins_algorithm(long_int in1, long_int in2, long_int& out);
    static void lcm(long_int& in1, long_int& in2, long_int& out);
    static void mu_calc(long_int& in, long_int& modulo, long_int& mu);
    static void barrett_reduction(long_int in, long_int& modulo, long_int& mu, long_int& rem);
};