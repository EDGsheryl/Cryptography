#include <bits/stdc++.h>

using namespace std;

string encrypt(string plaintext, int offset) {
    string cipher;
    cipher.clear();
    for (int i = 0; i < plaintext.size(); i++) {
        cipher.push_back('A' + (plaintext[i] - 'a' + offset) % 26);
    }
    return cipher;
}

string decrypt(string ciphertext, int offset) {
    string plaintext;
    plaintext.clear();
    for (int i = 0; i < ciphertext.size(); i++) {
        plaintext.push_back('a' + (ciphertext[i] - 'A' - offset + 26) % 26);
    }
    return plaintext;
}

void bruteforce(string str) {
    for (int i = 0; i < 26; i++) {
        cout << str << " -> use key" << i << " -> " << decrypt(str, i) << endl;
    }
}

int main() {
    cout << encrypt("yoshiko", 3) << endl;
    cout << decrypt(encrypt("yoshiko", 3), 3) << endl;

    bruteforce("PELCGBTENCUL");
}

// Using uppercase letter to represent cipher
// Using lowercase letter to represent plaintext
