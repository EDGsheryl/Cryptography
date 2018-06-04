#include <bits/stdc++.h>

using namespace std;

class OneTimePad {
    vector<char> v;
public:
    OneTimePad() {
        v.clear();
    }

    vector<char> encrypt(vector<char> plain) {
        srand(time(NULL));
        while (v.size() < plain.size()) v.push_back(rand());
        vector<char> ret;
        ret.clear();
        for (int i = 0; i < plain.size(); i++)
            ret.push_back(v[i] ^ plain[i]);
        return ret;
    }

    vector<char> decrypt(vector<char> cipher) {
        vector<char> ret;
        ret.clear();
        for (int i = 0; i < cipher.size(); i++)
            ret.push_back(v[i] ^ cipher[i]);
        return ret;
    }
};

int main() {
    OneTimePad otp = *(new OneTimePad());
    auto test = otp.decrypt(otp.encrypt(*(new vector<char>({'1', '2', '3'}))));
    for (auto i:test)
        cout << i << " ";
}
