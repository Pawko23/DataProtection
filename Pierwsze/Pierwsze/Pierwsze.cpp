#include <iostream>
#include <cmath>
#include <fstream>

using namespace std;

void TDM_in_range() {
    fstream file;
    long int n1 = 18000000;
    long int n2 = 19000000;
    long int counter = 0;

    file.open("result.txt", ios::out);
    if (!file.is_open()) {
        cerr << "Error opening file" << endl;
        return;
    }

    for (long int i = n1; i <= n2; i++) {
        double squareRoot = sqrt(i);
        bool prime = true;
        for (long int j = 2; j <= squareRoot; j++) {
            if (i % j == 0) {
                prime = false;
                break;
            }
        }
        if (prime) {
            counter++;
            file << i << endl;
        }
    }
    file.close();
    cout << "Number of prime numbers in range " << n1 << " <--> " << n2 << " = " << counter << endl;
}

bool PrimeTDM(long int n) {
    if (n <= 1) {
        return false;
    }
    for (long int i = 2; i < sqrt(n); i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}


bool lucas_lehmer(int p) {
    unsigned long long int S = 4;
    long int M = pow(2, p) - 1;
    for (long int i = 0; i < p - 2; i++) {
        S = (S * S - 2) % M;
    }
    return S == 0;
}

bool isPrime(int n)
{
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i < n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}


int main()
{
    TDM_in_range();
    cout << endl;
    cout << endl;

    for (int i = 3; i < 42; i++) {
        if (isPrime(i)) {
            long int M = pow(2, i) - 1;
            cout << "Number: " << i << endl;
            if (PrimeTDM(M)) {
                cout << "TDM: PRIME!" << endl;
            }
            else {
                cout << "TDM: NOT PRIME!" << endl;
            }
            if (lucas_lehmer(i)) {
                cout << "LL: PRIME!" << endl;
            }
            else {
                cout << "LL: NOT PRIME!" << endl;
            }
            cout << endl;
        }
    }

    return 0;
}
