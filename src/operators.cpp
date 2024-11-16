#include "long_arithmetic.hpp"
#include <iostream>

using namespace std;

long_int::long_int(uint64_t init_value, uint8_t init_size){
    size = init_size;
    this->digits = new digit[size];
    for(int i = 0; i < size; i++){
        this->digits[i].value = 0;
    }
    if(init_value != 0){
        this->digits[0].value = init_value;
    }
}

long_int::long_int(long_int& in){
    size = in.size;
    this->digits = new digit[size];
    for(int i = 0; i < size; i++){
        this->digits[i].value = in[i].value;
    }
}

void long_int::reset(){
    for(int i = 0; i < size; i++){
        this->digits[i].value = 0;
    } 
}

long_int::~long_int(){
    delete[] digits;
}

bool long_int::operator==(long_int& in){
    // if(size != in.size){
    //     return false;
    // }
    // int inner_size;
    // if(size == in.size){

    // }
    // for(int i = 0; i < size; i++){
    //     if(this->digits[i].value != in.digits[i].value){
    //         return false;
    //     }
    // }
    // return true;

    long_int temp;
    if(!long_arithmetic::long_sub(*this, in, temp) && !long_arithmetic::long_sub(in, *this, temp)){
        return true;
    }
    else{
        return false;
    }
}

digit& long_int::operator[](int i){
    return this->digits[i];
}

void long_int::long_upper_super_shift(int shift){
    if(shift>size || shift<0){
        throw invalid_argument("Attempt to shift an invalid number of digits");
    }
    else{
        for(int i = size-1; i >= 0; i--){
            digits[i].value = digits[i-shift].value;
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
    else if(shift == 0){
        return;
    }
    else{
        uint64_t carry_in = 0;
        uint64_t carry_out = 0;
        for(int i = 0; i<size; i++){
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
    if(shift>size || shift<0){
        throw invalid_argument("Attempt to shift an invalid number of digits");
    }
    else{
        for(int i = 0; i < size-shift; i++){
            digits[i].value = digits[i+shift].value;
        }  
        for(int i = size-1; i >= size-shift; i--){
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
        for(int i = size-1; i >= 0; i--){
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
    //check sizes!
    if (this == &in){
        return *this;
    }
    else{
        this->resize_erase(in.size);
        for(int i = 0; i < size; i++){
            this->digits[i].value = in[i].value;
        }
        return *this;
    }
}

long_int& long_int::operator=(long_int&& in){
    if (this == &in){
        return *this;
    }
    else{
        if(digits){
            delete[] digits;            
        }
        digits = in.digits;
        size = in.size;
        in.digits = nullptr;
        in.size = 0;

        return *this;
    }
}

void long_int::set_bit(int value, int position){
    if(value != 0 && value != 1){
        throw invalid_argument("Incorrect bit value");
    }
    //shold change boundaries!
    // else if(position > 2048 || position < 0){
    //     throw out_of_range("long_int lenght is 2048 bit");
    // }
    else{
        int digit = position/64;
        int bit = position%64;
        switch (value){
        case 1:
            this->digits[digit].value|=1ULL<<bit;
            break;
        case 0:
            this->digits[digit].value&=~(1ULL<<bit);        
            break;
        }     
    }    
}

bool long_int::even(){
    if(digits[0].value<<63 == 0){
        return true;
    }
    else{
        return false;
    }
}

void long_int::resize_erase(int new_size){
    if(size != new_size){
        delete[] digits;
        digits = new digit[new_size];
        size = new_size;        
    }
    else{
        this->reset();
    }
}

void long_int::resize(int new_size){
    if(size != new_size){
        digit* temp = new digit[new_size];
        int iter = 0;
        while(iter < size && iter < new_size){
            temp[iter].value = digits[iter].value;
            iter++;
        }
        
        delete[] digits;
        digits = temp;
        size = new_size;        
    }
}

void long_int::get_high(long_int& out, int part){
    if(part > size){
        throw invalid_argument("Part can't be larger then the number");
    }
    else{
        int digit_size = digit_length(); 
        out.resize_erase(part);
        for(int i = 0; i < part; i++){
            out[i].value = digits[digit_size-part+i].value;
        }      
    }
}

//!!!
void long_int::rewrite_high(long_int& in){
    int digit_size = digit_length();
    for(int i = 0; i < in.size; i++){
        digits[digit_size-in.size+i].value = in[i].value;
    }
}