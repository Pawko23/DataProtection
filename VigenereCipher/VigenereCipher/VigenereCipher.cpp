#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

using namespace std;

int main()
{
    fstream file, res, dec;
    string alphabet = "ABCDEFGHIJKLMNOPRSTQUVWXYZ0123456789";
    string example;
    string password;
    int n;
    int choice;

    cout << "Enter password: ";
    cin >> password;

    for (int i = 0; i < password.length(); i++) {
        if (islower(password[i])) {
            password[i] = toupper(password[i]);
        }
    }

    cout << "1 - Encrypt / 2 - Decrypt: ";
    cin >> choice;

    n = alphabet.length();
    char** table = new char* [n];
    char temp;
    for (int i = 0; i < n; i++) {
        table[i] = new char[n];
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            table[i][j] = alphabet[j];
        }
        temp = alphabet[0];
        for (int k = 0; k < n; k++) {
            alphabet[k] = alphabet[k + 1];
        }
        alphabet[n - 1] = temp;
    }
    
    string result = "";
    int row = -1, column = -1;
    int password_index = 0;
    switch (choice) {
    case 1:
        result = "";
        file.open("data.txt");
        row = -1, column = -1;
        if (file.good() == true) {
            password_index = 0;
            while (getline(file, example)) {
                for (int h = 0; h < example.length(); h++) {
                    if (islower(example[h])) {
                        example[h] = toupper(example[h]);
                    }
                }
                for (int x = 0; x < example.length(); x++) {

                    if (alphabet.find(example[x]) != string::npos) {
                        for (int i = 0; i < n; i++) {
                            if (table[i][0] == example[x]) {
                                row = i;
                                break;
                            }
                        }
                        for (int j = 0; j < n; j++) {
                            if (table[0][j] == password[password_index]) {
                                column = j;
                                break;
                            }
                        }
                        if (row != -1 && column != -1) {
                            result += table[row][column];
                        }

                        if (password_index == password.length() - 1) {
                            password_index = 0;
                        }
                        else {
                            password_index++;
                        }

                        row = -1;
                        column = -1;
                    }
                    else {
                        result += example[x];
                    }
                }
                result += "\n";
            }
            file.close();
            res.open("encrypt.txt", ios::out | ios::trunc);
            if (res.good() == true) {
                res << result << endl;
            }
            res.close();
        }
        break;
    case 2:
        result = "";
        char column_name;
        file.open("data.txt");
        row = -1, column = -1;
        if (file.good() == true) {
            password_index = 0;
            while (getline(file, example)) {
                for (int h = 0; h < example.length(); h++) {
                    if (islower(example[h])) {
                        example[h] = toupper(example[h]);
                    }
                }
                for (int x = 0; x < example.length(); x++) {
                    if (alphabet.find(example[x]) != string::npos) {
                        for (int i = 0; i < n; i++) {
                            if (table[i][0] == password[password_index]) {
                                row = i;
                                break;
                            }
                        }
                        if (password_index <= password.length()) {
                            for (int j = 0; j < n; j++) {
                                if (table[row][j] == example[x]) {
                                    column = j;
                                    break;
                                }
                            }
                        }
                        if (row != -1 && column != -1) {
                            result += table[0][column];
                        }
                        else {
                            result += example[x];
                        }
                        if (password_index == password.length() - 1) {
                            password_index = 0;
                        }
                        else {
                            password_index++;
                        }
                        row = -1;
                        column = -1;
                    }
                    else {
                        result += example[x];
                    }
                }
                result += "\n";
            }
            file.close();
            dec.open("decrypt.txt", ios::out | ios::trunc);
            if (dec.good() == true) {
                dec << result << endl;
            }
            dec.close();
        }
        break;
    }
    return 0;
}
