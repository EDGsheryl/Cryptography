#include <bits/stdc++.h>

using namespace std;

vector<vector<char> > ReadFromFile(const char *name) {
    vector<vector<char> > ret;
    vector<char> now;

    ret.clear();
    now.clear();
    for (int i = 1; i <= 16; i++) now.push_back(0);

    ifstream file(name, ios::in | ios::binary);
    char *buffer = new char[17]{};
    int size = 16;
    while (1) {
        if (!file.read(buffer, size)) {
            if (file.gcount() != size) {
                for (int i = file.gcount(); i < size; i++) buffer[i] = 0;
                for (int i = 0; i < 16; i++) now[i] = buffer[i];
                ret.push_back(now);
                break;
            }
        }
        for (int i = 0; i < 16; i++) now[i] = buffer[i];
        ret.push_back(now);
    }
    file.close();
    return ret;
}

class CFB {
public:
    void encode(const char *from, const char *to, vector<char> IV, function<vector<char>(vector<char>)> f) {
        auto fromvalue = ReadFromFile(from);
        ofstream fout(to, ios::out | ios::binary);
        for (auto i:fromvalue) {
            IV = f(IV);
            char *ch = new char[17];
            for (int o = 0; o < 16; o++) ch[o] = i[o] ^ IV[o];
            fout.write(ch, 16);
            for (int o = 0; o < 16; o++) IV[o] = ch[o];
        }
        fout.close();
    }

    void decode(const char *from, const char *to, vector<char> IV, function<vector<char>(vector<char>)> f) {
        auto fromvalue = ReadFromFile(from);
        fromvalue.pop_back(); //WTF if delete this it will cause a bug.
        ofstream fout(to, ios::out | ios::binary);
        for (auto i:fromvalue) {
            auto oldi = i;
            IV = f(IV);
            char *ch = new char[17];
            for (int o = 0; o < 16; o++) ch[o] = i[o] ^ IV[o];
            fout.write(ch, 16);
            IV = oldi;
        }
        fout.close();
    }
};


int main() {
    CFB *test = new CFB();
    vector<char> iv;
    iv.clear();
    for (int i = 1; i <= 16; i++) iv.push_back(0);
    test->encode("1.txt", "2.txt", iv, [](vector<char> q) { return q; });
    test->decode("2.txt", "3.txt", iv, [](vector<char> q) { return q; });
}
