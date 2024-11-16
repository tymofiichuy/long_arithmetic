#include "long_arithmetic.hpp"
#include<iostream>
using namespace std;

void modular_arithmetic::steins_algorithm(long_int in1, long_int in2, long_int& out){
    //check sizes
    //check for zero value
    long_int temp;
    out.set_bit(1, 0);
    int temp_length = in2.bit_length();

    while(temp_length != 0){
        while(in1.even() && in2.even()){
            in1>>1;
            in2>>1;
            out<<1;
            temp_length--;
        }
        while(in1.even()){
            in1>>1;
        }
        while(in2.even()){
            in2>>1;
            temp_length--;
        }
        if(!long_arithmetic::long_sub(in2, in1, temp)){
            long_arithmetic::long_sub(in2, in1, in2);
            temp_length = in2.bit_length();
        }
        else{
            // temp = move(in2);
            // in2 = move(in1);
            // in1 = move(temp);
            temp = in2;
            in2 = in1;
            in1 = temp;
            long_arithmetic::long_sub(in2, in1, in2);
            temp_length = in2.bit_length();
        }
    }
    long_arithmetic::long_multiply(out, in1, out);
}

void modular_arithmetic::lcm(long_int& in1, long_int& in2, long_int& out){
    int size = in1.get_size();

    long_int gcd, prod, rem(0, 2*size);
    steins_algorithm(in1, in2, gcd);
    long_arithmetic::long_multiply(in1, in2, prod);

    prod.resize(2*size);
    out.resize_erase(2*size);
    gcd.resize(2*size);
    long_arithmetic::long_divide(prod, gcd, rem, out);
}

void modular_arithmetic::mu_calc(long_int& in, long_int& modulo, long_int& mu){
    int len = modulo.digit_length();
    long_int temp;
    if(long_arithmetic::long_sub(in, modulo, temp)){
        mu.reset();
    }
    else{
        mu.resize_erase(2*(len+1));
        mu.set_bit(1, 128*len);
        //mu.set_bit(1,0);
        //mu.long_upper_super_shift(2*len);
        long_arithmetic::long_divide(mu, modulo, temp, mu);
    }
}

void modular_arithmetic::barrett_reduction(long_int& in, long_int& modulo, long_int& mu, long_int& rem){
    long_int quart(in);
    int len = modulo.digit_length();
    quart.long_lower_super_shift(len-1);
    long_arithmetic::long_multiply(quart, mu, quart);
    quart.long_lower_super_shift(len+1);
    long_arithmetic::long_multiply(quart, modulo, quart);
    long_arithmetic::long_sub(in, quart, rem);

    while(!long_arithmetic::long_sub(rem, modulo, quart)){
        long_arithmetic::long_sub(rem, modulo, rem);
    }

    rem.resize(len);
}



// void modular_arithmetic::mu_calc(long_int& in, long_int& modulo, long_int& mu){
//     int in_len, mod_len, shift;
//     long_int temp(0, in.get_size());
//     if(long_arithmetic::long_sub(in, modulo, temp)){
//         mu.reset();
//     }
//     else{
//         mu.resize_erase(2*in.size + 1);
//         in_len = in.bit_length();
//         mod_len = modulo.bit_length();
//         if(2*mod_len < in_len){
//             shift = in_len;
//         }
//         else{
//             shift = 2*mod_len;
//         }
//
//         mu.set_bit(1, 2*shift+1);
//         long_arithmetic::long_divide(mu, modulo, temp, mu);        
//     }
// }

// void modular_arithmetic::barrett_reduction(long_int& in, long_int& modulo, long_int& mu, long_int& rem){
//     if(mu.bit_length() == 0){
//         rem = in;     
//     }

//     int in_len, mod_len, shift;
//     long_int temp(0, in.get_size()), quart(in);
//     in_len = in.bit_length();
//     mod_len = modulo.bit_length();
//     if(long_arithmetic::long_sub(in, modulo, temp)){
//         rem = in;
//         quart.reset();
//     }
//     else{
//         if(2*mod_len < in_len){
//             shift = in_len;
//         }
//         else{
//             shift = 2*mod_len;
//         }

//         quart = in;
//         quart>>(mod_len-1);
//         long_arithmetic::long_multiply(quart, mu, quart);
//         quart>>(mod_len-1);
//         long_arithmetic::long_multiply(quart, modulo, temp);
//     }
// }