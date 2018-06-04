#include <bits/stdc++.h>

using namespace std;

#define F(x, y, z) (((x) & (y)) | ((~x) & (z)))
#define G(x, y, z) (((x) & (z)) | ((y) & (~z)))
#define H(x, y, z) ((x) ^ (y) ^ (z))
#define I(x, y, z) ((y) ^ ((x) | (~z)))

#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

#define FF(a, b, c, d, x, s, ac) { \
    (a) += F ((b), (c), (d)) + (x) + ac; \
    (a) = ROTATE_LEFT ((a), (s)); \
    (a) += (b); \
}
#define GG(a, b, c, d, x, s, ac) { \
    (a) += G ((b), (c), (d)) + (x) + ac; \
    (a) = ROTATE_LEFT ((a), (s)); \
    (a) += (b); \
}
#define HH(a, b, c, d, x, s, ac) { \
    (a) += H ((b), (c), (d)) + (x) + ac; \
    (a) = ROTATE_LEFT ((a), (s)); \
    (a) += (b); \
}
#define II(a, b, c, d, x, s, ac) { \
    (a) += I ((b), (c), (d)) + (x) + ac; \
    (a) = ROTATE_LEFT ((a), (s)); \
    (a) += (b); \
}

vector<uint8_t> MD5(vector<uint8_t> message) {
    vector<uint8_t> ret;
    ret.clear();

    uint64_t len = message.size() * 8;
    message.push_back(0x80);
    while ((message.size() * 8) % 512 != 448) {
        message.push_back(0);
    }

    for (int i = 0; i < 8; i++) {
        message.push_back(static_cast<unsigned char &&>(len & 0xff));
        len >>= 8;
    }

    assert(message.size() * 8 % 512 == 0);


#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21
    uint32_t A = 0x67452301ll, B = 0xEFCDAB89ll, C = 0x98BADCFEll, D = 0x10325476ll;
    int top = message.size() * 8 / 512;
    for (int i = 0; i < top; i++) {
        uint32_t a = A;
        uint32_t b = B;
        uint32_t c = C;
        uint32_t d = D;

        uint32_t groups[16];
        for (int o = 0; o < 16; o++)
            groups[o] = ((uint32_t) message[i * 64 + o * 4]) | ((uint32_t) message[i * 64 + o * 4 + 1] << 8) |
                        ((uint32_t) message[i * 64 + o * 4 + 2] << 16) |
                        ((uint32_t) message[i * 64 + o * 4 + 3] << 24);

        FF(a, b, c, d, groups[0], S11, 0xd76aa478ll); /* 1 */
        FF(d, a, b, c, groups[1], S12, 0xe8c7b756ll); /* 2 */
        FF(c, d, a, b, groups[2], S13, 0x242070dbll); /* 3 */
        FF(b, c, d, a, groups[3], S14, 0xc1bdceeell); /* 4 */
        FF(a, b, c, d, groups[4], S11, 0xf57c0fafll); /* 5 */
        FF(d, a, b, c, groups[5], S12, 0x4787c62all); /* 6 */
        FF(c, d, a, b, groups[6], S13, 0xa8304613ll); /* 7 */
        FF(b, c, d, a, groups[7], S14, 0xfd469501ll); /* 8 */
        FF(a, b, c, d, groups[8], S11, 0x698098d8ll); /* 9 */
        FF(d, a, b, c, groups[9], S12, 0x8b44f7afll); /* 10 */
        FF(c, d, a, b, groups[10], S13, 0xffff5bb1ll); /* 11 */
        FF(b, c, d, a, groups[11], S14, 0x895cd7bell); /* 12 */
        FF(a, b, c, d, groups[12], S11, 0x6b901122ll); /* 13 */
        FF(d, a, b, c, groups[13], S12, 0xfd987193ll); /* 14 */
        FF(c, d, a, b, groups[14], S13, 0xa679438ell); /* 15 */
        FF(b, c, d, a, groups[15], S14, 0x49b40821ll); /* 16 */

        GG(a, b, c, d, groups[1], S21, 0xf61e2562ll); /* 17 */
        GG(d, a, b, c, groups[6], S22, 0xc040b340ll); /* 18 */
        GG(c, d, a, b, groups[11], S23, 0x265e5a51ll); /* 19 */
        GG(b, c, d, a, groups[0], S24, 0xe9b6c7aall); /* 20 */
        GG(a, b, c, d, groups[5], S21, 0xd62f105dll); /* 21 */
        GG(d, a, b, c, groups[10], S22, 0x2441453ll); /* 22 */
        GG(c, d, a, b, groups[15], S23, 0xd8a1e681ll); /* 23 */
        GG(b, c, d, a, groups[4], S24, 0xe7d3fbc8ll); /* 24 */
        GG(a, b, c, d, groups[9], S21, 0x21e1cde6ll); /* 25 */
        GG(d, a, b, c, groups[14], S22, 0xc33707d6ll); /* 26 */
        GG(c, d, a, b, groups[3], S23, 0xf4d50d87ll); /* 27 */
        GG(b, c, d, a, groups[8], S24, 0x455a14edll); /* 28 */
        GG(a, b, c, d, groups[13], S21, 0xa9e3e905ll); /* 29 */
        GG(d, a, b, c, groups[2], S22, 0xfcefa3f8ll); /* 30 */
        GG(c, d, a, b, groups[7], S23, 0x676f02d9ll); /* 31 */
        GG(b, c, d, a, groups[12], S24, 0x8d2a4c8all); /* 32 */

        HH(a, b, c, d, groups[5], S31, 0xfffa3942ll); /* 33 */
        HH(d, a, b, c, groups[8], S32, 0x8771f681ll); /* 34 */
        HH(c, d, a, b, groups[11], S33, 0x6d9d6122ll); /* 35 */
        HH(b, c, d, a, groups[14], S34, 0xfde5380cll); /* 36 */
        HH(a, b, c, d, groups[1], S31, 0xa4beea44ll); /* 37 */
        HH(d, a, b, c, groups[4], S32, 0x4bdecfa9ll); /* 38 */
        HH(c, d, a, b, groups[7], S33, 0xf6bb4b60ll); /* 39 */
        HH(b, c, d, a, groups[10], S34, 0xbebfbc70ll); /* 40 */
        HH(a, b, c, d, groups[13], S31, 0x289b7ec6ll); /* 41 */
        HH(d, a, b, c, groups[0], S32, 0xeaa127fall); /* 42 */
        HH(c, d, a, b, groups[3], S33, 0xd4ef3085ll); /* 43 */
        HH(b, c, d, a, groups[6], S34, 0x4881d05ll); /* 44 */
        HH(a, b, c, d, groups[9], S31, 0xd9d4d039ll); /* 45 */
        HH(d, a, b, c, groups[12], S32, 0xe6db99e5ll); /* 46 */
        HH(c, d, a, b, groups[15], S33, 0x1fa27cf8ll); /* 47 */
        HH(b, c, d, a, groups[2], S34, 0xc4ac5665ll); /* 48 */
        
        II(a, b, c, d, groups[0], S41, 0xf4292244ll); /* 49 */
        II(d, a, b, c, groups[7], S42, 0x432aff97ll); /* 50 */
        II(c, d, a, b, groups[14], S43, 0xab9423a7ll); /* 51 */
        II(b, c, d, a, groups[5], S44, 0xfc93a039ll); /* 52 */
        II(a, b, c, d, groups[12], S41, 0x655b59c3ll); /* 53 */
        II(d, a, b, c, groups[3], S42, 0x8f0ccc92ll); /* 54 */
        II(c, d, a, b, groups[10], S43, 0xffeff47dll); /* 55 */
        II(b, c, d, a, groups[1], S44, 0x85845dd1ll); /* 56 */
        II(a, b, c, d, groups[8], S41, 0x6fa87e4fll); /* 57 */
        II(d, a, b, c, groups[15], S42, 0xfe2ce6e0ll); /* 58 */
        II(c, d, a, b, groups[6], S43, 0xa3014314ll); /* 59 */
        II(b, c, d, a, groups[13], S44, 0x4e0811a1ll); /* 60 */
        II(a, b, c, d, groups[4], S41, 0xf7537e82ll); /* 61 */
        II(d, a, b, c, groups[11], S42, 0xbd3af235ll); /* 62 */
        II(c, d, a, b, groups[2], S43, 0x2ad7d2bbll); /* 63 */
        II(b, c, d, a, groups[9], S44, 0xeb86d391ll); /* 64 */

        A += a;
        B += b;
        C += c;
        D += d;
    }

    for (int i = 0; i < 4; i++) {
        ret.push_back(static_cast<unsigned char &&>(A & 0xff));
        A >>= 8;
    }
    for (int i = 0; i < 4; i++) {
        ret.push_back(static_cast<unsigned char &&>(B & 0xff));
        B >>= 8;
    }
    for (int i = 0; i < 4; i++) {
        ret.push_back(static_cast<unsigned char &&>(C & 0xff));
        C >>= 8;
    }
    for (int i = 0; i < 4; i++) {
        ret.push_back(static_cast<unsigned char &&>(D & 0xff));
        D >>= 8;
    }

    return ret;
}

int main() {
    vector<uint8_t> v;
    v.clear();
    auto q = MD5(v);
    for (auto i:q)
        cout << fixed << setfill('0') << setw(2) << hex << (int) i;
    cout << endl;

    v.push_back('a');
    v.push_back('b');
    v.push_back('c');
    q = MD5(v);
    for (auto i:q)
        cout << fixed << setfill('0') << setw(2) << hex << (int) i;
}
