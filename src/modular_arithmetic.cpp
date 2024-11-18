#include "long_arithmetic.hpp"
#include<iostream>
using namespace std;

void modular_arithmetic::steins_algorithm(long_int in1, long_int in2, long_int& out){
    //check sizes
    //check for zero value
    long_int temp;
    out.reset();
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

void modular_arithmetic::mu_calc(long_int& modulo, long_int& mu){
    int len = modulo.digit_length();
    long_int temp;
    mu.resize_erase(2*(len+1));
    mu.set_bit(1, 128*len);
    long_arithmetic::long_divide(mu, modulo, temp, mu);
}

void modular_arithmetic::barrett_reduction(long_int in, long_int modulo, long_int& mu, long_int& rem){
    long_int temp;
    if(long_arithmetic::long_sub(in, modulo, temp)){
        rem = in;
    }
    else{
        int len = modulo.digit_length();

        temp.resize_erase(2*len);
        while(in.digit_length() > 2*modulo.digit_length()){
            in.get_high(temp, 2*len);
            barrett_reduction(temp, modulo, mu, temp);
            in.rewrite_high(temp);
        }
        long_int quart(in);
        quart.long_lower_super_shift(len-1);
        long_arithmetic::long_multiply(quart, mu, quart);
        quart.long_lower_super_shift(len+1);
        long_arithmetic::long_multiply(quart, modulo, quart);
        long_arithmetic::long_sub(in, quart, rem);
        while(!long_arithmetic::long_sub(rem, modulo, quart)){
            long_arithmetic::long_sub(rem, modulo, rem);
        }

        rem.resize(2*len);        
    }
}

void modular_arithmetic::long_mod_add(long_int& in1, long_int& in2, long_int& modulo, long_int& mu, long_int& out, unsigned char carry_bit){
    unsigned char last_carry = long_arithmetic::long_add(in1, in2, out, carry_bit);
    if(last_carry){
        out.resize(out.size+2);
        out.set_bit(1, 64*(out.size-2));
    }

    barrett_reduction(out, modulo, mu, out);
}

void modular_arithmetic::long_mod_sub(long_int& in1, long_int& in2, long_int& modulo, long_int& mu,long_int& out, unsigned char borrow_bit){
    unsigned char last_borrow = long_arithmetic::long_sub(in1, in2, out, borrow_bit);
    if(!last_borrow){
        barrett_reduction(out, modulo, mu, out);
    }
    else{
        long_arithmetic::long_sub(in2, in1, out, borrow_bit);
        barrett_reduction(out, modulo, mu, out);
        long_arithmetic::long_sub(modulo, out, out);
    }
}

void modular_arithmetic::long_mod_multiply(long_int& in1, long_int& in2, long_int& modulo, long_int& mu, long_int& out){
    long_arithmetic::long_multiply(in1, in2, out);
    barrett_reduction(out, modulo, mu, out);
}

void modular_arithmetic::long_mod_square(long_int& in, long_int& modulo, long_int& mu, long_int& out){
    long_mod_multiply(in, in, modulo, mu, out);
}

void modular_arithmetic::long_mod_power(long_int in, long_int& power, long_int& modulo, long_int& out){
    out.resize_erase(2*modulo.digit_length());
    out.set_bit(1, 0);
    long_int mu;
    mu_calc(modulo, mu);
    for(int i = 0; i < power.bit_length(); i++){
        if(power.get_bit(i)){
            long_mod_multiply(out, in, modulo, mu, out);
        }
        long_mod_square(in, modulo, mu, in);
    }
}

bool modular_arithmetic::miller_rabin_test(long_int& in){
    if(in.even() || in.bit_length() == 0){
        return false;
    }
    random_device rd;
    mt19937_64 mt (rd());
    int counter = 0, size = in.size;
    long_int temp(1, size), x(0, size), pow(0, size), mu;
    long_arithmetic::long_sub(in, temp, pow);
    x.random_integer(1, pow, mt);

    //temp now is gcd(x, in)
    steins_algorithm(x, in, temp);
    if(temp.bit_length() != 1){
        return false;
    }
    while(pow.even()){
        pow>>1;
        counter++;
    }
    if(pow.bit_length() == 0){
        return false;
    }

    //temp now is -1 mod in
    temp.reset();
    long_arithmetic::long_sub(in, temp, temp, 1);
    long_mod_power(x, pow, in, x);
    if(x.bit_length() == 1 || x == temp){
        return true;
    }

    mu_calc(in, mu);
    for(counter; counter > 1; counter--){
        long_mod_square(x, in, mu, x);
        if(x == temp){
            return true;
        }
        else if(x.bit_length() == 1){
            return false;
        }
    }
    return false;
}