#include <bits/stdc++.h>

using namespace std;


vector<uint8_t> SHA256(vector<uint8_t> message) {
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


    uint32_t h0 = 0x6a09e667, h1 = 0xbb67ae85, h2 = 0x3c6ef372, h3 = 0xa54ff53a;
    uint32_t h4 = 0x510e527f, h5 = 0x9b05688c, h6 = 0x1f83d9ab, h7 = 0x5be0cd19;
    uint32_t k[64] = {
            0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
            0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
            0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
            0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
            0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
            0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
            0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
            0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};
    int top = message.size() * 8 / 512;
    for (int i = 0; i < top; i++) {
        uint32_t a = h0;
        uint32_t b = h1;
        uint32_t c = h2;
        uint32_t d = h3;
        uint32_t e = h4;
        uint32_t f = h5;
        uint32_t g = h6;
        uint32_t h = h7;

        uint32_t groups[64];
        for (int o = 0; o < 16; o++)
            groups[o] = ((uint32_t) message[i * 64 + o * 4] << 24) | ((uint32_t) message[i * 64 + o * 4 + 1] << 16) |
                        ((uint32_t) message[i * 64 + o * 4 + 2] << 8) |
                        ((uint32_t) message[i * 64 + o * 4 + 3]);
        for (int o = 16; o < 64; o++) {
            uint32_t s0 = ((groups[o - 15] >> 7) | (groups[o - 15] << 25)) ^
                          ((groups[o - 15] >> 18) | (groups[o - 15] << 14)) ^(groups[o - 15] >> 3);
            uint32_t s1 =
                    ((groups[o - 2] >> 17) | (groups[o - 2] << 15)) ^((groups[o - 2] >> 19) | (groups[o - 2] << 13)) ^
                    (groups[o - 2] >> 10);
            groups[o] = groups[o - 16] + s0 + groups[o - 7] + s1;
        }

        uint32_t s0, s1, t2, t1, ch, maj;
        for (int i = 0; i < 64; i++) {
            s0 = ((a >> 2) | (a << 30)) ^ ((a >> 13) | (a << 19)) ^ ((a >> 22) | (a << 10));
            maj = (a & b) ^ (a & c) ^ (b & c);
            t2 = s0 + maj;
            s1 = ((e >> 6) | (e << 26)) ^ ((e >> 11) | (e << 21)) ^ ((e >> 25) | (e << 7));
            ch = (e & f) ^ ((~e) & g);
            t1 = h + s1 + ch + k[i] + groups[i];
            h = g;
            g = f;
            f = e;
            e = d + t1;
            d = c;
            c = b;
            b = a;
            a = t1 + t2;
        }

        h0 += a;
        h1 += b;
        h2 += c;
        h3 += d;
        h4 += e;
        h5 += f;
        h6 += g;
        h7 += h;
    }

    while (!s.empty()) s.pop();
    for (int i = 0; i < 4; i++) {
        s.push(static_cast<unsigned char &&>(h0 & 0xff));
        h0 >>= 8;
    }
    while (!s.empty()) {
        ret.push_back(s.top());
        s.pop();
    }
    for (int i = 0; i < 4; i++) {
        s.push(static_cast<unsigned char &&>(h1 & 0xff));
        h1 >>= 8;
    }
    while (!s.empty()) {
        ret.push_back(s.top());
        s.pop();
    }
    for (int i = 0; i < 4; i++) {
        s.push(static_cast<unsigned char &&>(h2 & 0xff));
        h2 >>= 8;
    }
    while (!s.empty()) {
        ret.push_back(s.top());
        s.pop();
    }
    for (int i = 0; i < 4; i++) {
        s.push(static_cast<unsigned char &&>(h3 & 0xff));
        h3 >>= 8;
    }
    while (!s.empty()) {
        ret.push_back(s.top());
        s.pop();
    }
    for (int i = 0; i < 4; i++) {
        s.push(static_cast<unsigned char &&>(h4 & 0xff));
        h4 >>= 8;
    }
    while (!s.empty()) {
        ret.push_back(s.top());
        s.pop();
    }
    for (int i = 0; i < 4; i++) {
        s.push(static_cast<unsigned char &&>(h5 & 0xff));
        h5 >>= 8;
    }
    while (!s.empty()) {
        ret.push_back(s.top());
        s.pop();
    }
    for (int i = 0; i < 4; i++) {
        s.push(static_cast<unsigned char &&>(h6 & 0xff));
        h6 >>= 8;
    }
    while (!s.empty()) {
        ret.push_back(s.top());
        s.pop();
    }
    for (int i = 0; i < 4; i++) {
        s.push(static_cast<unsigned char &&>(h7 & 0xff));
        h7 >>= 8;
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
    auto q = SHA256(v);
    for (auto i:q)
        cout << fixed << setfill('0') << setw(2) << hex << (int) i;
    cout << endl;

    v.push_back('b');
    v.push_back('c');
    q = SHA256(v);
    for (auto i:q)
        cout << fixed << setfill('0') << setw(2) << hex << (int) i;
}
