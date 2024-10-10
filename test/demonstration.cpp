#include<iostream>
#include<iomanip>
#include "long_arithmetic.hpp"

using namespace std;

void handle(int option){
    long_int x, y, out1, out2;
    string sx, sy;
    switch(option){
        case 1:
            cin >> sx;
            x.read_long_int(sx);
            cout << "\n";
            cin >> sy;
            y.read_long_int(sy);

            long_arithmetic::long_add(x, y, out1);
            cout << setfill('=') << setw(100) << "\n";
            out1.print_int();
            cout << "\n";
            break;
        case 2:
            cin >> sx;
            x.read_long_int(sx);
            cout << "\n";
            cin >> sy;
            y.read_long_int(sy);

            long_arithmetic::long_sub(x, y, out1);
            cout << setfill('=') << setw(100) << "\n";
            out1.print_int();
            cout << "\n";
            break;
        case 3:
            cin >> sx;
            x.read_long_int(sx);
            cout << "\n";
            cin >> sy;
            y.read_long_int(sy);

            long_arithmetic::long_multiply(x, y, out1, out2);
            cout << setfill('=') << setw(100) << "\n";            
            out2.print_int();
            cout << "\n";
            out1.print_int();
            cout << "\n";
            break;
        case 4:
            cin >> sx;
            x.read_long_int(sx);
            cout << "\n";
            cin >> sy;
            y.read_long_int(sy);

            long_arithmetic::long_divide(x, y, out1, out2);
            cout << setfill('=') << setw(100) << "\n";
            out2.print_int();
            cout << "\n";
            out1.print_int();
            cout << "\n";
            break;
        case 5:
            break;
    }
}

int main(){
    int option;
    cout << "1. Add\n2. Subtract\n3. Multiply\n4. Divide\n5. Exit\n\n";
    do {
		cout << "Option: ";
		cin >> option;
        cout << "\n";
		handle(option);
	} while (option != 5);
    return 0;
}