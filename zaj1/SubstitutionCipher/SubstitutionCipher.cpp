#include <iostream>
#include <string>
#include <map>
#include <fstream>

using namespace std;

int main()
{
    string alphabet = "ABCDEFGHIJKLMNOPRSTQUVWXYZ0123456789";
    string message;
    string ciphered;
    string decrypted;
    int key;

    cout << "Enter key: ";
    cin >> key;

    ifstream file("enc.txt");
    ofstream result("encresult.txt");
    ofstream result2("decresult.txt");

    map<char, char> dict;
    for (int i = 0; i < alphabet.length(); i++) {
        dict[alphabet[i]] = alphabet[(i + key) % alphabet.length()];
    }
    
    map<char, char> dict2;
    for (int i = 0; i < alphabet.length(); i++) {
        dict2[alphabet[i]] = alphabet[(i - key) % alphabet.length()];
    }

    int choice;
    cout << "1 - Encrypt message / 2 - Decrypt message: ";
    cin >> choice;

    switch (choice) {
    case 1:
        while (getline(file, message)) {
            for (char& c : message) {
                if (alphabet.find(c) != string::npos) {
                    ciphered += dict[c];
                }
                else {
                    ciphered += c;
                }
            }
            result << ciphered << endl;
            ciphered = "";
        }
        file.close();

    case 2:
        while (getline(file, message)) {
            for (char& c : message) {
                if (alphabet.find(c) != string::npos) {
                    int index = alphabet.find(c) - key;
                    if (index < 0) {
                        index += alphabet.length();
                    }
                    decrypted += alphabet[index];
                }
                else {
                    decrypted += c;
                }
            }
            result2 << decrypted << endl;
            decrypted = "";
        }
        file.close();
        decrypted = "";
        file.close();
    }
    return 0;
}
