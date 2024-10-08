#include "long_arithmetic.hpp"
#include <iostream>

using namespace std;

long_int::long_int(uint64_t init_value){
    this->digits = new digit[32];
    for(int i = 0; i < 32; i++){
        this->digits[i].value = 0;
    }
    if(!init_value){
        this->digits[0].value = init_value;
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

void long_int::long_upper_super_shift(int shift){
    if(shift>32 || shift<0){
        throw invalid_argument("Attempt to shift an invalid number of digits");
    }
    else{
        for(int i = 0; i < 32-shift; i++){
            digits[i+shift].value = digits[i].value;
        }  
        for(int i = 0; i < shift; i++){
            digits[i].value = 0; 
        } 
    }
}

void long_int::long_upper_sub_shift(int shift){
    if(shift>64 || shift<0){
        throw invalid_argument("Attempt to shift an invalid number of bits");
    }
    else{
        uint64_t carry_in = 0;
        uint64_t carry_out = 0;
        for(int i = 0; i<32; i++){
            carry_out = this->digits[i].value>>(64-shift);
            this->digits[i].value = (this->digits[i].value<<shift)|carry_in;
            carry_in = carry_out;
        }
    }
}

void long_int::operator<<(int shift){
    int super_shift = shift/64;
    int sub_shift = shift%64;
    this->long_upper_super_shift(super_shift);
    this->long_upper_sub_shift(sub_shift);
}

void long_int::long_lower_super_shift(int shift){
    if(shift>32 || shift<0){
        throw invalid_argument("Attempt to shift an invalid number of digits");
    }
    else{
        for(int i = 0; i < 32-shift; i++){
            digits[i].value = digits[i+shift].value;
        }  
        for(int i = 31; i >= 32-shift; i--){
            digits[i].value = 0; 
        } 
    }
}

void long_int::long_lower_sub_shift(int shift){
    if(shift>64 || shift<0){
        throw invalid_argument("Attempt to shift an invalid number of bits");
    }
    else{
        uint64_t carry_in = 0;
        uint64_t carry_out = 0;
        for(int i = 31; i >= 0; i--){
            carry_out = this->digits[i].value<<(64-shift);
            this->digits[i].value = (this->digits[i].value>>shift)|carry_in;
            carry_in = carry_out;
        }
    }
}

void long_int::operator>>(int shift){
    int super_shift = shift/64;
    int sub_shift = shift%64;
    this->long_lower_super_shift(super_shift);
    this->long_lower_sub_shift(sub_shift);
}

long_int& long_int::operator=(long_int& in){
    if (*this == in){
        return *this;
    }
    else{
        for(int i = 0; i < 32; i++){
            this->digits[i].value = in[i].value;
        }
        return *this;
    }
}