#include <iostream>
#include "matrica.h"
#include <cmath>
#include <ctime>
using namespace std;

int main() {
    try {
        Matrica a, b, c;
//        cin >> a;
//        cout << a.determinanta() << endl;
//        cout << a.adjungovana() << endl;
//        cout << a.inverzna() << endl;
//        cin >> b;
//        cout << a+b << endl;
//        cout << a-b << endl;
//        cout << a*b;
        // [1 2;3 4]^3*(4*[1 2 3;4 5 6]+[7 8; 9 1; 2 3]^T)−[1 3;7 2]^−1 * [7 8 1;1 2 3] * E3
        // ([1 5 6; 2 7 8; 4 5 6]^T)^-1
        // ([1 5 6; 2 7 8; 4 5 6]^-1)^T
        // [1 4 6 8 3 4 6 7 9;5 7 3 5 9 0 3 5 2;3 4 5 6 8 3 3 1 0;3 2 1 0 0 9 4 5 2;3 3 3 7 4 5 6 7 6;1 1 1 3 4 5 6 7 8;0 9 8 4 3 2 8 6 4;2 2 3 4 3 4 2 1 8;1 8 0 6 1 9 7 5 3]^-1
//        cin >> c;
//        cout << c << endl;
        cin >> c;
        cout << c;
    } catch (const char* error) {
        cout << error;
    } catch (...) {
        cout << "Neocekivana greska!";
    }
    return 0;
}
