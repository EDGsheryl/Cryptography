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
    while (size) {
        try {
            if (!file.read(buffer, size)) {
                if (file.gcount() != size) {
                    for (int i = file.gcount(); i < size; i++) buffer[i] = 0;
                    for (int i = 0; i < size; i++) now[i] = buffer[i];
                    ret.push_back(now);
                    size = 0;
                    continue;
                } else {
                    throw 1;
                }
            }
            for (int i = 0; i < 16; i++) now[i] = buffer[i];
            ret.push_back(now);
        }
        catch (int i) {
            break;
        }
    }
    return ret;
}

class ECB {
public:
    void encode(const char* from,const char* to,function<vector<char>(vector<char>)> f) {
        auto fromvalue = ReadFromFile(from);
        ofstream fout(to,ios::out|ios::binary);
        for (auto i:fromvalue) {
            for (auto o:f(i))
                fout<<o;
        }
    }

    void decode(const char* from,const char* to,function<vector<char>(vector<char>)> f) {
        auto fromvalue = ReadFromFile(from);
        ofstream fout(to,ios::out|ios::binary);
        for (auto i:fromvalue) {
            for (auto o:f(i))
                fout<<o;
        }
    }
};



int main() {
    ECB* test = new ECB();
    test->encode("1.txt","2.txt",[](vector<char> q){return q;});
}
