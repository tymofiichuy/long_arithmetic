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
    split[1] = digit(value>>32);
    split[0] = digit(value&0xFFFFFFFF);

    return split;
}

// missed shift
// missed carry bit
// _addcarry_u64(carry_bit, in1[i].value, in2[i].value, &out[i].value)
digit* digit::digit_mult(digit in){
    digit* res = new digit[2];
    unsigned char carry = 0;
    uint64_t temp1, temp2, out;

    digit* temp_x = this->digit_split();
    digit* temp_y = in.digit_split();

    temp1 = temp_x[0].value*temp_y[1].value;
    temp2 = temp_x[1].value*temp_y[0].value;
    carry = _addcarry_u64(carry, temp1, temp2, &out);
    digit mid(out);
    //digit mid = digit(temp_x[0].value*temp_y[1].value + temp_x[1].value*temp_y[0].value);
    digit* mid_split = mid.digit_split();
    if(carry == 1){
        mid_split[1].value += (1ULL<<32);
    }
    carry = 0;

    temp1 = temp_x[0].value*temp_y[0].value;
    temp2 = mid_split[0].value<<32;
    carry = _addcarry_u64(carry, temp1, temp2, &out);
    res[0] = digit(out);
    //res[0] = digit(temp_x[0].value*temp_y[0].value + (mid_split[0].value<<32));

    temp1 = temp_x[1].value*temp_y[1].value;
    temp2 = mid_split[1].value;
    carry = _addcarry_u64(carry, temp1, temp2, &out);
    res[1] = digit(out);
    //res[1] = digit(temp_x[1].value*temp_y[1].value + mid_split[1].value);

    delete[] temp_x;
    delete[] temp_y;
    delete[] mid_split;
    return res;
}