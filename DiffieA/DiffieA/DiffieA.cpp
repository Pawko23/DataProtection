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
    //ALICE
    unsigned long long a, A;

    //PUBLIC AREA
    unsigned long int p, g;

    //BOB
    unsigned long long b, B;

    cout << "Enter p: ";
    cin >> p;
    cout << "Enter g: ";
    cin >> g;
    cout << "Enter a: ";
    cin >> a;

    //Now they are exchangind those variables A and B
    A = compute(g, a, p);
    cout << "A: " << A << endl;
    cout << "Enter B: ";
    cin >> B;

    cout << endl;
    cout << endl;

    //So Alicee gets public key B, and Bob gets public key A. Now compute symetric keys
    cout << "Alice (K): " << compute(B, a, p) << endl;
}