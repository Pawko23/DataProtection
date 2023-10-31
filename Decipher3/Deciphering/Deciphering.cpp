#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <cctype>
#include <vector>

using namespace std;

map<char, int>dictionary(string text) {
    int n = text.length();
    map<char, int> dictionary;
    for (char c : text) {
        if (dictionary.find(c) == dictionary.end()) {
            dictionary[c] = 1;
        }
        else {
            dictionary[c]++;
        }

    }
    return dictionary;
}

string skipChar(string example) {
    string result = "";
    for (char c : example) {
        if (isalnum(c)) {
            result += c;
        }
    }
    return result;
}

string transformToUpper(string str) {
    string result;
    for (char c : str) {
        if (isalpha(c)) {
            result += toupper(c);
        }
        else {
            result += c;
        }
    }
    return result;
}

double IC(string text, map<char, int>& dict) {
    double sum = 0.0;
    long long N = text.length();
    if (N <= 1) {
        return 0.0;
    }
    for (auto it = dict.begin(); it != dict.end(); it++) {
        long long ni = it->second;
        sum += (double)ni * (ni - 1);
    }
    return sum / (N * (N - 1));
}

double maxAvg(string cipheredText) {
    double maxAvgIC = 0.0;
    int maxKeyValue = 0;
    for (int h = 2; h <= 20; h++) {
        vector<string> groups(h);
        //Podzial na grupy
        for (int j = 0; j < cipheredText.length(); j++) {
            int index = j % h;
            groups[index] += cipheredText[j];
        }

        //srednie IC
        double avgIC = 0.0;
        for (const string& group : groups) {
            map<char, int> groupDict = dictionary(group);
            avgIC += IC(group, groupDict);
        }
        avgIC /= h;
        cout << "Avg IC for " << h << " group is: " << avgIC << endl;
        //cout << "Max Key Value for " << h << " group is: " << maxKeyValue << endl;
        //Update wartosci
        if (avgIC > maxAvgIC) {
            maxAvgIC = avgIC;
            maxKeyValue = h;
        }
    }
    return maxAvgIC;
}

int main()
{
    string text, text2;
    string ciphered;
    fstream file;
    cout << "<-----------------------------------------BASE FILE----------------------------------------->" << endl;
    file.open("base.txt", ios::in);
    if (file.good() == true) {
        string line;
        while (getline(file, line)) {
            text += line + " ";
        }

        //cout << "Base text from file: " << text;
        text = transformToUpper(text);
        map<char, int> baseDictionary = dictionary(text);
        //cout << endl;
        //cout << "Model (base) IC: " << IC(text, baseDictionary) << endl;
        for (auto it = baseDictionary.begin(); it != baseDictionary.end(); it++) {
            cout << it->first << ": " << it->second << endl;
        }
    }
    else {
        cout << "ERROR LOADING THE FILE" << endl;
    }
    file.close();
    cout << "<--------------------------------------------------------------------------------------------------->" << endl;
    cout << endl;
    cout << endl;
    cout << "<-----------------------------------------CIPHERED VIGENERE----------------------------------------->" << endl;
    /*for (auto it = percentageShare.begin(); it != percentageShare.end(); it++) {
        it->second = it->second / static_cast<double>(n) * 100;
    }*/

    //model IC jest punktem odniesienia dla innych tekstów. Obliczamy go dla tekstu bazowego
    //i następne teksty porównujemy do niego aby określić czy dany tekst jest napisany językiem
    //zbliżonym lub nie

    file.open("example.txt", ios::in);
    if (file.good() == true) {
        string line2;
        while (getline(file, line2)) {
            text2 += line2 + "";
        }
        text2 = skipChar(text2);
        ciphered = transformToUpper(text2);
        cout << ciphered;
        map<char, int> cipheredDictionary = dictionary(ciphered);
        cout << endl;
        //cout << "Model (Vigenere Ciphered) IC: " << IC(ciphered, cipheredDictionary) << endl;
        cout << "Max avg for h = 2...20: " << maxAvg(ciphered) << endl;
        for (auto it = cipheredDictionary.begin(); it != cipheredDictionary.end(); it++) {
            cout << it->first << ": " << it->second << endl;
        }
    }
    else {
        cout << "ERROR LOADING THE FILE" << endl;
    }
    file.close();
    cout << "<--------------------------------------------------------------------------------------------------->" << endl;
    return 0;
}
