#include "long_arithmetic.hpp"
#include<intrin.h>

using namespace std;
uint64_t base = 1<<64;

long_int::long_int(){
    this->digits = new uint64_t[32];
    for(int i = 0; i < 32; i++){
        this->digits[i] = 0;
    }
}

long_int::~long_int(){
    delete[] digits;
}

unsigned char long_add(long_int& in1, long_int& in2, unsigned char carry_bit = 0, long_int& out){
    for(int i = 0; i < 32; i++){
        carry_bit = _addcarry_u64(carry_bit, in1.digits[i], in2.digits[i], &out.digits[i]);
    }
    return carry_bit;
}

//problem: uint is always positive
unsigned char long_sub(long_int& in1, long_int& in2, unsigned char borrow_bit = 0, long_int& out){
    uint64_t temp;
    for(int i = 0; i < 32; i++){
        temp = in1.digits[i] - in2.digits[i] - borrow_bit;
        if(temp >= 0){
            out.digits[i] = temp;
            borrow_bit = 0;
        }
        else{
            out.digits[i] = temp + base;
            borrow_bit = 1;
        }
    }
    return borrow_bit;
}