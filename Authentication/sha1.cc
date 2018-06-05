#include <bits/stdc++.h>

using namespace std;


vector<uint8_t> SHA1(vector<uint8_t> message) {
    vector<uint8_t> ret;
    ret.clear();

    uint64_t len = message.size() * 8;
    message.push_back(0x80);
    while ((message.size() * 8) % 512 != 448) {
        message.push_back(0);
    }

    stack<uint8_t> s;
    while (!s.empty()) s.pop();
    for (int i = 0; i < 8; i++) {
        s.push(static_cast<unsigned char &&>(len & 0xff));
        len >>= 8;
    }
    while (!s.empty()) {
        message.push_back(s.top());
        s.pop();
    }

    assert(message.size() * 8 % 512 == 0);


    uint32_t A = 0x67452301ll, B = 0xEFCDAB89ll, C = 0x98BADCFEll, D = 0x10325476ll, E = 0xc3d2e1f0;
    int top = message.size() * 8 / 512;
    for (int i = 0; i < top; i++) {
        uint32_t a = A;
        uint32_t b = B;
        uint32_t c = C;
        uint32_t d = D;
        uint32_t e = E;

        uint32_t groups[80];
        for (int o = 0; o < 16; o++)
            groups[o] = ((uint32_t) message[i * 64 + o * 4] << 24) | ((uint32_t) message[i * 64 + o * 4 + 1] << 16) |
                        ((uint32_t) message[i * 64 + o * 4 + 2] << 8) |
                        ((uint32_t) message[i * 64 + o * 4 + 3]);
        for (int o = 16; o < 80; o++) {
            groups[o] = (groups[o - 3] ^ groups[o - 8] ^ groups[o - 14] ^ groups[o - 16]);
            groups[o] = (groups[o] >> 31) | (groups[o] << 1);
        }

        uint32_t f, k, temp;
        for (int i = 0; i < 80; i++) {
            if (i >= 0 && i <= 19) {
                f = (b & c) | ((~b) & d);
                k = 0x5A827999;
            } else if (i >= 20 && i <= 39) {
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
            } else if (i >= 40 && i <= 59) {
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
            } else if (i >= 60 && i <= 79) {
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
            }
            temp = ((a >> 27) | (a << 5)) + f + e + k + groups[i];
            e = d;
            d = c;
            c = ((b >> 2) | (b << 30));
            b = a;
            a = temp;
        }

        A += a;
        B += b;
        C += c;
        D += d;
        E += e;
    }

    while (!s.empty()) s.pop();
    for (int i = 0; i < 4; i++) {
        s.push(static_cast<unsigned char &&>(A & 0xff));
        A >>= 8;
    }
    while (!s.empty()) {
        ret.push_back(s.top());
        s.pop();
    }
    for (int i = 0; i < 4; i++) {
        s.push(static_cast<unsigned char &&>(B & 0xff));
        B >>= 8;
    }
    while (!s.empty()) {
        ret.push_back(s.top());
        s.pop();
    }
    for (int i = 0; i < 4; i++) {
        s.push(static_cast<unsigned char &&>(C & 0xff));
        C >>= 8;
    }
    while (!s.empty()) {
        ret.push_back(s.top());
        s.pop();
    }
    for (int i = 0; i < 4; i++) {
        s.push(static_cast<unsigned char &&>(D & 0xff));
        D >>= 8;
    }
    while (!s.empty()) {
        ret.push_back(s.top());
        s.pop();
    }
    for (int i = 0; i < 4; i++) {
        s.push(static_cast<unsigned char &&>(E & 0xff));
        E >>= 8;
    }
    while (!s.empty()) {
        ret.push_back(s.top());
        s.pop();
    }

    return ret;
}

int main() {
    vector<uint8_t> v;
    v.clear();
    v.push_back('a');
    auto q = SHA1(v);
    for (auto i:q)
        cout << fixed << setfill('0') << setw(2) << hex << (int) i;
    cout << endl;
    
    v.push_back('b');
    v.push_back('c');
    q = SHA1(v);
    for (auto i:q)
        cout << fixed << setfill('0') << setw(2) << hex << (int) i;
}
