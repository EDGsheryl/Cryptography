#include <bits/stdc++.h>

using namespace std;

int gcdEx(int a, int b, int &x, int &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    } else {
        int r = gcdEx(b, a % b, x, y); /* r = GCD(a, b) = GCD(b, a%b) */
        int t = x;
        x = y;
        y = t - a / b * y;
        return r;
    }
}

int ModReserve(int a, int MOD) {
    int ret, ret2;
    gcdEx(a, MOD, ret, ret2);
    return (ret % MOD + MOD) % MOD;
}


class ECC {
public:
    int MOD, a, b;

    ECC(int _a, int _b, int _MOD) : a(_a), b(_b), MOD(_MOD) {};

    class point {
    public:
        int x, y;
        int MOD, a;

        point(int _x, int _y, int _a, int _MOD) : x(_x), y(_y), a(_a), MOD(_MOD) {};

        friend point &operator+=(point &lhs, point &rhs);

        friend point operator+(point lhs, point &rhs);

        friend point operator*(int lhs, point &rhs);

        point operator-();
    };
};

ECC::point &operator+=(ECC::point &lhs, ECC::point &rhs) {
    assert(lhs.a = rhs.a);
    assert(lhs.MOD == rhs.MOD);
    int lambda = (lhs.x == rhs.x && rhs.y == lhs.y) ? (((3 * lhs.x * lhs.x) % lhs.MOD + lhs.a) *
                                                       ModReserve(lhs.y, lhs.MOD)) : ((rhs.y - lhs.y) *
                                                                                      ModReserve(rhs.x - lhs.x,
                                                                                                 lhs.MOD));
    lambda = (lambda % lhs.MOD + lhs.MOD) % lhs.MOD;
    int newx = (lambda * lambda) - lhs.x - rhs.x;
    newx = (newx % lhs.MOD + lhs.MOD) % lhs.MOD;
    int newy = lambda * (lhs.x - newx) - lhs.y;
    newy = (newy % lhs.MOD + lhs.MOD) % lhs.MOD;
    lhs.x = newx % lhs.MOD;
    lhs.y = newy % lhs.MOD;
    return lhs;
}

ECC::point operator+(ECC::point lhs, ECC::point &rhs) {
    return lhs += rhs;
}

ECC::point ECC::point::operator-() {
    return ECC::point(this->x, -this->y, this->a, this->MOD);
}

ECC::point operator*(int lhs, ECC::point &rhs) {
    assert(lhs != 0);
    ECC::point ret = rhs;
    lhs--;
    ECC::point now = rhs;
    while (lhs) {
        if (lhs & 1) ret += now;
        lhs >>= 1;
        now = now + now;
    }
    return ret;
}

int main() {
    ECC test(1, 1, 23);
    ECC::point p(3, 10, 1, 23);
    ECC::point q(9, 7, 1, 23);
    p = p + q;
    cout << p.x << " " << p.y;

}
