#include <iostream>
#include <cmath>

using namespace std;

unsigned long long compute(unsigned long long g, unsigned long long y, unsigned long long p) {
    unsigned long long result = 1;
    while (y > 0) {
        if (y % 2 == 1) {
            result = (result * g) % p;
        }
        g = (g * g) % p;
        y = y / 2;
    }
    return result;
}


int main()
{
    unsigned long long a, A;
    unsigned long long p, g;
    unsigned long long b, B;

    cout << "Enter p: ";
    cin >> p;
    cout << "Enter g: ";
    cin >> g;
    cout << "Enter a: ";
    cin >> b;

    B = compute(g, b, p);
    cout << "B: " << B << endl;
    cout << endl;
    cout << "Enter A: ";
    cin >> A;
    
    cout << "Bob (K): " << compute(A, b, p) << endl;
}
