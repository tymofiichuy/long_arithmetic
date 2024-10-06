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

int long_int::bit_length(){
    int i = 31;
    uint64_t temp = this->digits[i].value;
    while(temp == 0){
        i--;
        if(i == -1){
            return 0;
        }
        else{
            temp = this->digits[i].value;            
        }
    }
    int j = 0;
    while(temp != 0){
        temp = temp>>1;
        j++;
    }
    return i*64 + j;
}

void long_divide(long_int& in1, long_int& in2, long_int& rem, int& quart){
    if(!in2.bit_length()){
        throw invalid_argument("Divison by zero");
    }
    else{
        rem.reset();    
        int in_len = in2.bit_length();
        int rem_len;
        long_int sub_temp;
        long_int temp;
        rem = in1;
        quart = 0;
        while(!long_sub(rem, in2, sub_temp)){
            rem_len = rem.bit_length();
            temp = in2;
            temp<<(rem_len - in_len);
            if(long_sub(rem, temp, sub_temp)){
                rem_len--;
                temp>>(1);
            }
            long_sub(rem, temp, rem);
            quart += 1<<(rem_len - in_len);
        }        
    }
}

//not finished!
void long_power(long_int& in1, long_int& in2, long_int& out){
    out.reset();
    long_int powers[16];
    powers[0] = long_int(1);
    for(int i = 1; i < 16; i++){
        long_sub_multiply(powers[i-1], in1, powers[i]);
    }

    long_int res = long_int(1);
    int index;
    //can be improved!
    long_int temp = res;
    for(int i = 256; i >= 0; i--){
        for(int j = 0; j < 16; j++){
            long_sub_multiply(temp, temp, res);
            temp = res;
        }
        index = in2[31].value>>60;
        long_sub_multiply(temp, powers[index], res);
        in2<<4;
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