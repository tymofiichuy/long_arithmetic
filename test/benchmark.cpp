#include<iostream>
#include<chrono>

#include "long_arithmetic.hpp"

using namespace std;

int main(){
    long_int x, y, mod, mu, out, temp;
    random_device rd;
    mt19937_64 mt (rd());


    chrono::microseconds barret_total(0);
    chrono::microseconds add_mod_total(0);
    chrono::microseconds sub_mod_total(0);
    chrono::microseconds div_total(0);   
    chrono::microseconds mult_mod_total(0);
    chrono::microseconds stain_total(0);   
    chrono::microseconds lcm_total(0);
    chrono::microseconds square_total(0);   
    chrono::microseconds power_total(0);
    chrono::microseconds miller_total(0);   

    for(int j = 2; j <= 32; j=2*j){
        barret_total = chrono::microseconds(0);
        add_mod_total = chrono::microseconds(0);
        sub_mod_total = chrono::microseconds(0);
        div_total= chrono::microseconds(0);
        mult_mod_total = chrono::microseconds(0);
        stain_total = chrono::microseconds(0);
        lcm_total = chrono::microseconds(0);
        square_total = chrono::microseconds(0);
        power_total = chrono::microseconds(0);
        miller_total = chrono::microseconds(0);

        for(int i = 0; i < 1000; i++){
            x.random_integer(mt, j);
            y.random_integer(mt, j);
            mod.random_integer(mt, j);
            modular_arithmetic::mu_calc(mod, mu);

            auto start = chrono::high_resolution_clock::now();
            modular_arithmetic::barrett_reduction(x, mod, mu, out);
            auto end = chrono::high_resolution_clock::now();
            barret_total += chrono::duration_cast<chrono::microseconds>(end - start);

            start = chrono::high_resolution_clock::now();
            modular_arithmetic::long_mod_add(x, y, mod, mu, out);
            end = chrono::high_resolution_clock::now();
            add_mod_total += chrono::duration_cast<chrono::microseconds>(end - start);

            start = chrono::high_resolution_clock::now();
            modular_arithmetic::long_mod_sub(x, y, mod, mu, out);
            end = chrono::high_resolution_clock::now();
            sub_mod_total += chrono::duration_cast<chrono::microseconds>(end - start);

            start = chrono::high_resolution_clock::now();
            long_arithmetic::long_divide(x, y, temp, out);
            end = chrono::high_resolution_clock::now();
            div_total += chrono::duration_cast<chrono::microseconds>(end - start);

            start = chrono::high_resolution_clock::now();
            modular_arithmetic::long_mod_multiply(x, y, mod, mu, out);
            end = chrono::high_resolution_clock::now();
            mult_mod_total += chrono::duration_cast<chrono::microseconds>(end - start);

            start = chrono::high_resolution_clock::now();
            modular_arithmetic::steins_algorithm(x, y, out);
            end = chrono::high_resolution_clock::now();
            stain_total += chrono::duration_cast<chrono::microseconds>(end - start);

            start = chrono::high_resolution_clock::now();
            modular_arithmetic::lcm(x, y, out);
            end = chrono::high_resolution_clock::now();
            lcm_total += chrono::duration_cast<chrono::microseconds>(end - start);

            start = chrono::high_resolution_clock::now();
            modular_arithmetic::long_mod_square(x, mod, mu, out);
            end = chrono::high_resolution_clock::now();
            square_total += chrono::duration_cast<chrono::microseconds>(end - start);
        }

        cout << barret_total.count()/1000 << " " << add_mod_total.count()/1000 << " " << sub_mod_total.count()/1000 << " "
        << div_total.count()/1000 << " " << mult_mod_total.count()/1000 << " " << stain_total.count()/1000 << " "
        << lcm_total.count()/1000 << " " << square_total.count()/1000 << "\n";

        for(int i = 0; i < 10; i++){
            auto start = chrono::high_resolution_clock::now();
            modular_arithmetic::long_mod_power(x, y, mod, out);
            auto end = chrono::high_resolution_clock::now();
            power_total += chrono::duration_cast<chrono::microseconds>(end - start);

            start = chrono::high_resolution_clock::now();
            modular_arithmetic::miller_rabin_test(x);
            end = chrono::high_resolution_clock::now();
            miller_total += chrono::duration_cast<chrono::microseconds>(end - start);
        }

        cout << power_total.count()/10 << " " << miller_total.count()/10 << "\n\n";
    }
    return 0;              
}