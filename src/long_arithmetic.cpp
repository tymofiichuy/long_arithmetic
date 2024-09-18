#include "long_arithmetic.hpp"

#include<intrin.h>

long_int::long_int(){
    this->digits = new uint64_t[32];
    for(int i = 0; i < 32; i++){
        this->digits[i] = 0;
    }
}

long_int::~long_int(){
    delete[] digits;
}