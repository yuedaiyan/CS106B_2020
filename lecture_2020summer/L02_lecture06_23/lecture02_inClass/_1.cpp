#include <iostream>
using namespace std;

int main() {
    const int a_int = 100;
    const long b_lon = 999;
    const double c_double = 9.99;
    const string d_string = "hello world";
    const char e_chat = 'd';

    cout << "a_int: " << a_int << endl;
    cout << "b_string: " << d_string << endl;
    cout << "c_double: " << c_double << endl;
    cout << "d_string: " << d_string << endl;
    cout << "e_chat: " << e_chat << endl;

    int b;
    b = 10;
    cout << "b: " << b << endl;
    b = 100;
    cout << "b: " << b << endl;

    double s = 999.999;
    cout << "s: " << s << endl;
    int k = s;
    cout << "k: " << k << endl;

    return 0;
}