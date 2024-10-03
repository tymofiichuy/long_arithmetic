#include "long_arithmetic.hpp"
#include<intrin.h>
#include <iostream>

using namespace std;
//uint64_t base = 1<<64;

//can be optimized (if needed) by reducing tmp size to 64 bits and using flag to capture overflow
unsigned char long_add(long_int& in1, long_int& in2, long_int& out, unsigned char carry_bit = 0){
    for(int i = 0; i < 32; i++){
        carry_bit = _addcarry_u64(carry_bit, in1[i].value, in2[i].value, &out[i].value);
    }
    return carry_bit;
}
//can be optimized (if needed) by reducing tmp size to 64 bits and using flag to capture overflow
unsigned char long_sub(long_int& in1, long_int& in2, long_int& out, unsigned char borrow_bit = 0){
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
    long_add(out, carry, out);
}

void long_sub_multiply(long_int& in1, long_int& in2, long_int& out){
    out.reset();
    long_int temp;
    long_int carry;
    for(int i = 0; i < 32; i++){
        carry.reset();
        long_multiply_by_one_digit(in1, in2[i], carry, temp);
        temp.long_upper_super_shift(i);
        long_add(out, temp, out);
    }
}

// void long_int::split(long_int* out, int iter){
//     out[0].reset();
//     out[1].reset();
//     int upper = 32<<iter;
//     int lower = 16<<iter;

//     for(int i = 0; i < lower; i++){
//         out[0][i] = this->digits[i];
//     }

//     for(int i = lower; i < upper; i++){
//         out[1][i-lower] = this->digits[i];
//     }
// }

// void long_super_multiply(long_int& in1, long_int& in2, long_int& out, int iter){
//     long_int split_1[2];
//     long_int split_2[2];
//     in1.split(split_1, iter);
//     in2.split(split_2, iter);

// }

// void long_int::split(long_int* out){
//     for(int i = 0; i < 8; i++){
//         for (int j = 0; j < 4; j++){
//             out[i][j] = this->digits[i*4+j];
//         }
//     }
// }