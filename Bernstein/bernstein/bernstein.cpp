#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <unordered_map>
#include <algorithm>
#include <functional>

using namespace std;

string generateRandomString(int n) {
    string randomString;
    for (int i = 0; i < n; i++) {
        char randomChar = 'a' + (rand() % 26);
        randomString += randomChar;
    }
    return randomString;
}

unsigned long bernstein(const string& str) {
    unsigned long hash = 5381;
    for (char c : str) {
        hash = (hash << 5) + hash + c;
    }
    return hash;
}

unsigned long adler32Checksum(const string& str) {
    const unsigned long MOD_ADLER = 65521;
    unsigned long a = 1, b = 0;

    for (char c : str) {
        a = (a + c) % MOD_ADLER;
        b = (b + a) % MOD_ADLER;
    }
    return (b << 16) | a;
}

void printCollissions(const vector<string>& strings, const vector<unsigned long>& hashes, vector<pair<unsigned long, string>>& sampleCollisions) {
    unordered_map<unsigned long, vector<unsigned long>>hashIndices;
    for (int i = 0; i < strings.size(); i++) {
        hashIndices[hashes[i]].push_back(i);
    }
    unsigned long sum = 0;
    for (const auto& entry : hashIndices) {
        if (entry.second.size() > 1) {
            //cout << "Number of colissions: " << entry.second.size() << endl;
            /*sum += entry.second.size();*/
            //cout << "Sample colissions: " << endl;
            for (int index : entry.second) {
                cout << "Hash: " << hashes[index] << endl;
                cout << "String: " << strings[index] << endl;
                sampleCollisions.push_back(make_pair(hashes[index], strings[index]));
            }
            cout << "-----------------------------------------" << endl;
            sum += entry.second.size();
        }
    }
}

int main()
{
    srand(time(NULL));

    vector<pair<unsigned long, string>> sampleCollisions;

    //generating 100 000 strings 8-char
    vector<string>c1Strings;
    for (int i = 0; i < 100000; i++) {
        string randomString = generateRandomString(8);
        c1Strings.push_back(randomString);
    }
    //DEBUG
    /*for (string str : c1Strings) {
        cout << str << endl;
    }*/


    //generating 100 000 strings 100-char
    vector<string> c2Strings;
    for (int i = 0; i < 100000; i++) {
        string randomString = generateRandomString(100);
        c2Strings.push_back(randomString);
    }
    //DEBUG
    /*for (string str : c2Strings) {
        cout << str << endl;
    }*/


    //calculating bernstein hash for C1
    vector<unsigned long>c1BernsteinHashes;
    for (const string& str : c1Strings) {
        unsigned long hash = bernstein(str);
        c1BernsteinHashes.push_back(hash);
    }
    /*for (unsigned int i : c1BernsteinHashes) {
        cout << i << endl;
    }*/

    //calculating bernstein hash for C2
    vector<unsigned long>c2BernsteinHashes;
    for (const string& str : c2Strings) {
        unsigned long hash = bernstein(str);
        c2BernsteinHashes.push_back(hash);
    }
    /*for (unsigned long long i : c1BernsteinHashes) {
        cout << i << endl;
    }*/

    //calculating adler32checksum for C1
    vector<unsigned long> c1Adler32Checksums;
    for (const string& str : c1Strings) {
        unsigned long checksum = adler32Checksum(str);
        c1Adler32Checksums.push_back(checksum);
    }

    //calculating adler32checksum for C2
    vector<unsigned long> c2Adler32Checksums;
    for (const string& str : c2Strings) {
        unsigned long checksum = adler32Checksum(str);
        c2Adler32Checksums.push_back(checksum);
    }

    //printing info
    cout << "Colissions for Bernstein hash in C1: " << endl;
    printCollissions(c1Strings, c1BernsteinHashes, sampleCollisions);
    cout << "Colissions for Bernstein hash in C2: " << endl;
    printCollissions(c2Strings, c2BernsteinHashes, sampleCollisions);
    cout << "Colissions for Adler in C1: " << endl;
    printCollissions(c1Strings, c1Adler32Checksums, sampleCollisions);
    cout << "Colissions for Adler in C2: " << endl;
    printCollissions(c2Strings, c2Adler32Checksums, sampleCollisions);
}
