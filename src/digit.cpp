#include "long_arithmetic.hpp"

digit::digit(uint64_t v){
    value = v;
}

void digit::operator>>(int i){
    value = value>>i;
}

void digit::operator<<(int i){
    value = value<<i;
}

digit* digit::digit_split(){
    digit* split = new digit[2];
    split[0] = digit(value>>32);
    split[1] = digit(value&0xFFFFFFFF);

    return split;
}

digit* digit::digit_mult(digit in){
    digit* res = new digit[2];

    digit* temp_x = this->digit_split();
    digit* temp_y = in.digit_split();
    
    digit mid = digit(temp_x[0].value*temp_y[1].value + temp_x[1].value*temp_y[0].value);
    digit* mid_split = mid.digit_split();

    res[0] = digit(temp_x[1].value*temp_y[1].value + mid_split[1].value);
    res[1] = digit(temp_x[0].value*temp_y[0].value + mid_split[0].value);

    delete[] temp_x;
    delete[] temp_y;
    delete[] mid_split;
    return res;
}