#include<iostream>
#include<iomanip>
#include "long_arithmetic.hpp"

using namespace std;

void main_test(){
    long_int x, y, mod, mu, out, temp;
    string sx, sy, sm;

    cout << "x: ";
    cin >> sx;
    x.read_long_int(sx);
    cout << "\ny: ";
    cin >> sy;
    y.read_long_int(sy);
    cout << "\nmod: ";
    cin >> sm;
    mod.read_long_int(sm);
    cout << "\n\n";

    modular_arithmetic::mu_calc(y, mu);
    modular_arithmetic::barrett_reduction(x, y, mu, out);
    cout << "x mod y:\n";
    out.print_int();
    cout << "\n";

    modular_arithmetic::steins_algorithm(x, y, out);
    cout << "gcd(x, y):\n";
    out.print_int();
    cout << "\n";

    modular_arithmetic::lcm(x, y, out);
    cout << "lcm(x, y):\n";
    out.print_int();
    cout << "\n";

    modular_arithmetic::mu_calc(mod, mu);

    modular_arithmetic::long_mod_add(x, y, mod, mu, out);
    cout << "(x + y)mod:\n";
    out.print_int();
    cout << "\n";

    modular_arithmetic::long_mod_sub(x, y, mod, mu, out);
    cout << "(x - y)mod:\n";
    out.print_int();
    cout << "\n";

    modular_arithmetic::long_mod_multiply(x, y, mod, mu, out);
    cout << "(x*y)mod:\n";
    out.print_int();
    cout << "\n";

    modular_arithmetic::long_mod_square(x, mod, mu, out);
    cout << "(x^2)mod:\n";
    out.print_int();
    cout << "\n";

    modular_arithmetic::long_mod_power(x, y, mod, out);
    cout << "(x^y)mod:\n";
    out.print_int();
    cout << "\n";
}

//7fffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffffff
//7fffffffffffffffffffffffffffffff
void prime_test(){
    long_int x;
    string str;
    bool prime;

    cout << "x: ";
    cin >> str;
    x.read_long_int(str);

    prime = modular_arithmetic::miller_rabin_test(x);
    if(prime){
        cout << "\nx is probably prime\n\n";
    }
    else{
        cout << "\nx is probably composite\n\n";
    }
}

void handle(int option){
    switch(option){
        case 1:
            main_test();
            break;
        case 2:
            prime_test();
            break;
        case 3:
            break;
    }
}

int main(){
    int option;
    cout << "1 - Modular arithmetic test\n2 - Miller-Rabin test\n3 - Exit\n\n";
    do {
        cout << "Option: ";
        cin >> option;
        cout << "\n";
        if(option < 1 || option > 3){
            break;
        }
        handle(option);
    } while (option != 3);
    return 0;
}