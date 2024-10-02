#include "long_arithmetic.hpp"
#include<intrin.h>

using namespace std;
//uint64_t base = 1<<64;

long_int::long_int(){
    this->digits = new digit[32];
    for(int i = 0; i < 32; i++){
        this->digits[i].value = 0;
    }
}

void long_int::reset(){
    for(int i = 0; i < 32; i++){
        this->digits[i].value = 0;
    } 
}

long_int::~long_int(){
    delete[] digits;
}

//use subtraction instead?
bool long_int::operator==(long_int& in){
    for(int i = 0; i < 32; i++){
        if(this->digits[i].value != in.digits[i].value){
            return false;
        }
    }
    return true;
}

digit& long_int::operator[](int i){
    return this->digits[i];
}

//can be optimized (if needed) by reducing tmp size to 64 bits and using flag to capture overflow
unsigned char long_add(long_int& in1, long_int& in2, unsigned char carry_bit = 0, long_int& out){
    for(int i = 0; i < 32; i++){
        carry_bit = _addcarry_u64(carry_bit, in1[i].value, in2[i].value, &out[i].value);
    }
    return carry_bit;
}
//can be optimized (if needed) by reducing tmp size to 64 bits and using flag to capture overflow
unsigned char long_sub(long_int& in1, long_int& in2, unsigned char borrow_bit = 0, long_int& out){
    for(int i = 0; i < 32; i++){
        borrow_bit = _subborrow_u64(borrow_bit, in1[i].value, in2[i].value, &out[i].value);
    }    
    return borrow_bit;
}

void long_multiply_by_one_digit(long_int& long_in, digit digit_in, long_int& carry, long_int& out){
    out.reset();
    digit* temp;

    for(int i = 0; i < 32; i++){
        temp = digit_in.digit_mult(long_in[i]);
        out[i] = temp[0];
        if (i != 31){
            carry[i+1] = temp[1];
        }
        delete[] temp;
    }
    long_add(out, carry, 0, out);
}

void long_sub_multiply(long_int& in1, long_int& in2, long_int& out){
    
}