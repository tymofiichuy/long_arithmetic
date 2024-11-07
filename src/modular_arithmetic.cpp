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

void modular_arithmetic::LCM(long_int& in1, long_int& in2, long_int& out){
    int size = in1.get_size();

    long_int gcd, prod, rem(0, 2*size);
    steins_algorithm(in1, in2, gcd);
    long_arithmetic::long_multiply(in1, in2, prod);

    prod.resize(2*size);
    out.resize_erase(2*size);
    gcd.resize(2*size);
    long_arithmetic::long_divide(prod, gcd, rem, out);
}