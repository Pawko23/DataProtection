#include <iostream>
#include <cmath>
#include <string>
#include <sstream>

using namespace std;

long long invmod(long long a, long long b) {
    long long b0 = b, t, q;
    long long x0 = 0, x1 = 1;

    if (b == 1)
        return 1;

    while (a > 1) {
        q = a / b;
        t = b;
        b = a % b;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += b0;

    return x1;
}

int main()
{
    long long p, q, n, fi, e, d;
    string m;

    cout << "Enter p: ";
    cin >> p;
    cout << "Enter q: ";
    cin >> q;
    cout << endl;

    n = p * q;
    fi = ((p - 1) * (q - 1));
    cout << "n = " << n << endl;
    cout << "fi(n) = " << fi << endl;
    cout << endl;

    cout << "Enter e: ";
    cin >> e;
    d = invmod(e, fi);
    cout << "d = " << d << endl;
    cout << endl;

    cout << "Enter text: ";
    cin.ignore();
    cin.clear();
    getline(cin, m);
    cout << "Encrypted (m) = ";
    string result = "";
    string decryptResult = "";
    for (char ch : m) {
        int ascii = static_cast<int>(ch);
        result += to_string(ascii) + " ";
    }
    cout << result << endl;
    string code;
    for (char ch : result) {
        if (ch != ' ') {
            code += ch;
        }
        else {
            int asciiCode = stoi(code);
            char character = static_cast<char>(asciiCode);
            decryptResult += character;
            code = "";
        }
    }
    cout << "Decrypted: " << decryptResult << endl;
    
    return 0;
}
