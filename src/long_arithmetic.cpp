#include "long_arithmetic.hpp"
#include<intrin.h>
#include<iostream>
#include<string>
#include<iomanip>

using namespace std;
//uint64_t base = 1<<64;

//can be optimized by reducing tmp size to 64 bits and using flag to capture overflow
unsigned char long_arithmetic::long_add(long_int& in1, long_int& in2, long_int& out, unsigned char carry_bit){
    for(int i = 0; i < 32; i++){
        carry_bit = _addcarry_u64(carry_bit, in1[i].value, in2[i].value, &out[i].value);
    }
    return carry_bit;
}
//can be optimized by reducing tmp size to 64 bits and using flag to capture overflow
unsigned char long_arithmetic::long_sub(long_int& in1, long_int& in2, long_int& out, unsigned char borrow_bit){
    for(int i = 0; i < 32; i++){
        borrow_bit = _subborrow_u64(borrow_bit, in1[i].value, in2[i].value, &out[i].value);
    }    
    return borrow_bit;
}

void long_arithmetic::long_multiply_by_one_digit(long_int& long_in, digit digit_in, long_int& carry, long_int& out){
    out.reset();
    digit* temp;

    for(int i = 0; i < 32; i++){
        temp = digit_in.digit_mult(long_in[i]);
        if(long_in[i].value == 0){
            temp[1].value = 0;
        }
        out[i] = temp[0];
        if (i != 31){
            carry[i+1] = temp[1];
        }
        delete[] temp;
    }
    long_add(out, carry, out);
}


void long_int::split(long_int& out1, long_int& out2){
    out1.reset();
    out2.reset();

    for(int i = 0; i < 16; i++){
        out1[i] = this->digits[i];
    }

    for(int i = 16; i < 32; i++){
        out2[i-16] = this->digits[i];
    }
}

void long_arithmetic::long_half_multiply(long_int& in1, long_int& in2, long_int& out){
    out.reset();
    long_int temp, carry;
    unsigned char sub_carry = 0;
    
    for(int i = 0; i < 16; i++){
        //carry.reset();
        long_multiply_by_one_digit(in1, in2[i], carry, temp);
        temp.long_upper_super_shift(i);
        sub_carry = long_add(out, temp, out, sub_carry);
    }
}

void long_arithmetic::long_multiply(long_int& in1, long_int& in2, long_int& out1, long_int& out2){
    out1.reset();
    out2.reset();

    long_int mid_split1, mid_split2, split1_1, split1_2, split2_1, split2_2, mid, temp1, temp2;
    unsigned char sub_carry = 0;
    
    in1.split(split1_1, split1_2);
    in2.split(split2_1, split2_2);

    long_half_multiply(split1_1, split2_2, temp1);
    long_half_multiply(split1_2, split2_1, temp2);
    sub_carry = long_add(temp1, temp2, mid);
    mid.split(mid_split1, mid_split2);
    if(sub_carry == 1){
        mid_split2[16].value = 1;
    }
    sub_carry = 0;
    mid_split1.long_upper_super_shift(16);

    long_half_multiply(split1_1, split2_1, temp1);
    long_half_multiply(split1_2, split2_2, temp2);
    sub_carry = long_add(temp1, mid_split1, out1, sub_carry);
    sub_carry = long_add(temp2, mid_split2, out2, sub_carry);
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

void long_arithmetic::long_divide(long_int& in1, long_int& in2, long_int& rem, long_int& quart){
    if(!in2.bit_length()){
        throw invalid_argument("Divison by zero");
    }
    else{
        rem.reset();
        quart.reset();
        int in_len = in2.bit_length();
        int rem_len;
        long_int sub_temp;
        long_int temp;
        rem = in1;
        while(long_sub(rem, in2, sub_temp) == 0){
            temp = in2;
            rem_len = rem.bit_length();
            temp<<(rem_len - in_len);
            if(long_sub(rem, temp, sub_temp) == 1){
                rem_len--;
                temp>>(1);
            }
            long_sub(rem, temp, rem);
            quart.set_bit(1, rem_len - in_len);
        }        
    }
}

void long_int::read_long_int(string in){
    this->reset();
    if(in.substr(0,2) == "0x"){
        in.erase(0,2);
    }
    int len = static_cast<int>(in.length());
    int start = len-16;
    int quart = len/16;
    int rem = len%16;

    for(int i = 0; i < quart; i++){
        this->digits[i].value = stoull(in.substr(start, 16), nullptr, 16);
        start -= 16;
    }

    if(rem){
        this->digits[quart].value = stoull(in.substr(0, rem), nullptr, 16);
    }
}

void long_int::print_int(){
    cout << "0x";
    int i = 31;
    while(this->digits[i].value == 0 && i >= 0){
        i--;
    }
    if(i == -1){
        cout << 0;
    }
    else{
        cout << hex << this->digits[i].value;
        i--;
        for(i; i >= 0; i--){
            cout << setfill('0') << setw(16) << hex << this->digits[i].value;            
        }   
    }       
    cout << "\n";
}

// not finished!
// can be skiped
// void long_power(long_int& in1, long_int& in2, long_int& out){
//     out.reset();
//     long_int powers[16];
//     powers[0] = long_int(1);
//     for(int i = 1; i < 16; i++){
//         long_sub_multiply(powers[i-1], in1, powers[i]);
//     }

//     long_int res = long_int(1);
//     int index;
//     long_int temp = res;
//     for(int i = 256; i >= 0; i--){
//         for(int j = 0; j < 16; j++){
//             long_sub_multiply(temp, temp, res);
//             temp = res;
//         }
//         index = in2[31].value>>60;
//         long_sub_multiply(temp, powers[index], res);
//         in2<<4;
//     }
// }

// void long_super_multiply(long_int& in1, long_int& in2, long_int& out, int iter){
//     long_int split_1[2];
//     long_int split_2[2];
//     in1.split(split_1, iter);
//     in2.split(split_2, iter);

// }