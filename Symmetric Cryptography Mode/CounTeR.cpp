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

class NewVector {
public:
    vector<char> nonce;
    vector<char> cnt;

    void add() {
        cnt[cnt.size() - 1]++;
        int j = cnt.size() - 1;
        while (j >= 0 && cnt[j] > 255) {
            cnt[j - 1]++;
            cnt[j] = 0;
        }
        return;
    }

    NewVector() {
        srand(time(NULL));
        for (int i = 1; i <= 8; i++) nonce.push_back(rand() % 256);
        for (int i = 1; i <= 8; i++) cnt.push_back(0);
    }
};

class CTR {
public:
    void encode(const char *from, const char *to, NewVector IV, function<vector<char>(vector<char>)> f) {
        auto fromvalue = ReadFromFile(from);
        ofstream fout(to, ios::out | ios::binary);
        for (auto i:fromvalue) {
            IV.add();
            vector<char> ivv;
            ivv.clear();
            for (auto o:IV.nonce) ivv.push_back(o);
            for (auto o:IV.cnt) ivv.push_back(o);
            ivv = f(ivv);
            char *ch = new char[17];
            for (int o = 0; o < 16; o++) ch[o] = i[o] ^ ivv[o];
            fout.write(ch, 16);
        }
        fout.close();
    }

    void decode(const char *from, const char *to, NewVector IV, function<vector<char>(vector<char>)> f) {
        auto fromvalue = ReadFromFile(from);
        fromvalue.pop_back(); //WTF if delete this it will cause a bug.
        ofstream fout(to, ios::out | ios::binary);
        for (auto i:fromvalue) {
            IV.add();
            vector<char> ivv;
            ivv.clear();
            for (auto o:IV.nonce) ivv.push_back(o);
            for (auto o:IV.cnt) ivv.push_back(o);
            ivv = f(ivv);
            char *ch = new char[17];
            for (int o = 0; o < 16; o++) ch[o] = i[o] ^ ivv[o];
            fout.write(ch, 16);
        }
        fout.close();
    }
};


int main() {
    CTR *test = new CTR();
    NewVector iv = *(new NewVector());
    test->encode("1.txt", "2.txt", iv, [](vector<char> q) { return q; });
    test->decode("2.txt", "3.txt", iv, [](vector<char> q) { return q; });
}
