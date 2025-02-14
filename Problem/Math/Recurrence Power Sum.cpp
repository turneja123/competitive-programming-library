//https://www.spoj.com/problems/RECPWSUM/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const long long M = 1e9 + 7;

long long inv_i[N];
long long fact[N];
long long factinv[N];

long long D;

struct Field {
    long long a, b;
};

long long modPow(long long x, long long y, long long M) {
    if (x == 0 && y == 0) {
        return 1;
    }
    long long res = 1;
    x = x % M;
    if (x == 0) {
        return 0;
    }
    while (y > 0) {
        if (y & 1) {
            res = (res * x) % M;
        }
        y >>= 1;
        x = (x * x) % M;
    }
    return res;
}

long long modPow(long long a, long long y) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
}

long long binomial(long long n, long long k) {
    return fact[n] * factinv[k] % M * factinv[n - k] % M;
}

Field add(const Field &x, const Field &y) {
    return {(x.a + y.a) % M, (x.b + y.b) % M};
}

Field sub(const Field &x, const Field &y) {
    return{(x.a - y.a + M) % M, (x.b - y.b + M) % M};
}

Field mul(const Field &x, const Field &y) {
    long long na = (x.a * y.a + x.b * y.b % M * D) % M;
    long long nb = (x.a * y.b + x.b * y.a) % M;
    return {na, nb};
}

Field fpow(Field a, long long y) {
    Field res = {1, 0};
    while(y > 0){
        if(y % 2 == 1) {
            res = mul(res, a);
        }
        y /= 2;
        a = mul(a, a);
    }
    return res;
}

Field inv(const Field &x) {
    long long n = (x.a * x.a % M - x.b * x.b % M * D % M + M) % M;
    long long invn = modPow(n, M - 2);
    long long na = x.a;
    long long nb = (-x.b + M) % M;
    na = (na * invn) % M;
    nb = (nb * invn) % M;
    return {na, nb};
}

long long tonelli_shanks(long long a, long long p) {
    if (a == 0) {
        return 0;
    }
    if (modPow(a, (p - 1) / 2, p) != 1) {
        return -1;
    }
    if (p % 4 == 3) {
        return modPow(a, (p + 1) / 4, p);
    }
    long long s = p - 1, n = 2, r = 0;
    while (s % 2 == 0) {
        r++;
        s /= 2;
    }
    while (modPow(n, (p - 1) / 2, p) != p - 1) {
        n++;
    }
    long long x = modPow(a, (s + 1) / 2, p), b = modPow(a, s, p), g = modPow(n, s, p), m = 1;
    while (m) {
        long long t = b;
        m = 0;
        for (; m < r && t != 1; m++) {
            t = (t * t) % p;
        }
        if (m == 0) {
            return x;
        }
        long long gs = modPow(g, 1 << (r - m - 1), p);
        g = (gs * gs) % p;
        x = (x * gs) % p;
        b = (b * g) % p;
        r = m;
    }
    return 0;
}


int main() {
    IOS;
    fact[0] = 1, factinv[0] = 1;
    for (int i = 1; i < N; i++) {
        inv_i[i] = (i == 1 ? 1 : M - (M / i) * inv_i[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv_i[i] % M;
    }
    Field o = {1, 0};
    long long inv2 = modPow(2, M - 2);

    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        long long a, b, x, y, n;
        int k;
        cin >> a >> b >> x >> y >> n >> k;
        if (k == 0) {
            cout << (n + 1) % M << endl;
            continue;
        }
        if (a == 0 && b == 0) {
            if (n == 0) {
                cout << modPow(x % M, k) << endl;
            } else {
                cout << (modPow(x % M, k) + modPow(y % M, k)) % M << endl;
            }
            continue;
        }
        if (b == 0) {
            if (n == 0) {
                cout << modPow(x % M, k) << endl;
            } else {
                long long X = modPow(x % M, k);
                long long c = modPow(y % M, k);
                long long r = modPow(a % M, k);
                long long g;
                if (r == 1) {
                    g = n % M;
                } else {
                    g = (modPow(r, n) + M - 1) % M * modPow((r + M - 1) % M, M - 2) % M;
                }
                long long ans = (X + c * g) % M;
                cout << ans << endl;
            }
            continue;
        }
        D = (a * a % M + b * 4 % M) % M;
        long long sqr = tonelli_shanks(D, M);
        if (sqr != -1) {
            long long r = sqr;
            long long phi = ((a + r) % M) * inv2 % M;
            long long psi = ((a - r + M) % M) * inv2 % M;
            long long diff = (phi + M - psi) % M;
            long long A = ((y + M - (x * psi % M)) % M) * modPow(diff, M - 2) % M;
            long long B = (( (x * phi) % M + M - y) % M) * modPow(diff, M - 2) % M;
            long long S = 0;
            for (int j = 0; j <= k; j++){
                long long binom = binomial(k, j);
                long long c = modPow(A, j) * modPow(B, k - j) % M;
                long long r_c = modPow(phi, j) * modPow(psi, k - j) % M;
                long long g;
                if (r_c == 1) {
                    g = (n + 1) % M;
                } else {
                    g = (modPow(r_c, n + 1) + M - 1) % M * modPow((r_c + M - 1) % M, M - 2) % M;
                }
                long long cur = binom * c % M * g % M;
                S = (S + cur) % M;
            }
            cout << S << endl;
            continue;
        }
        ll inv2 = modPow(2, M - 2);
        Field phi = add(mul({a, 0}, {inv2, 0}), {0, inv2});
        Field psi = sub(mul({a, 0}, {inv2, 0}), {0, inv2});

        Field xf = {x, 0}, yf = {y, 0};
        Field diff = sub(phi, psi);
        Field a_c = mul(sub(yf, mul(xf, psi)), inv(diff));
        Field b_c = mul(sub(mul(xf, phi), yf), inv(diff));

        vector<Field> phipow(k + 1), psipow(k + 1);
        phipow[0] = {1, 0};
        psipow[0] = {1, 0};
        for (int j = 1; j <= k; j++){
            phipow[j] = mul(phipow[j - 1], phi);
            psipow[j] = mul(psipow[j - 1], psi);
        }
        vector<Field> apow(k + 1), bpow(k + 1);
        apow[0] = {1, 0};
        bpow[0] = {1, 0};
        for (int j = 1; j <= k; j++){
            apow[j] = mul(apow[j - 1], a_c);
            bpow[j] = mul(bpow[j - 1], b_c);
        }
        Field S = {0, 0};
        for (int j = 0; j <= k; j++){
            Field r = mul(phipow[j], psipow[k - j]);
            Field g;
            if (r.a == 1 && r.b == 0){
                g = {(n + 1) % M, 0};
            } else {
                Field num = sub(fpow(r, n + 1), o);
                Field denom = sub(r, o);
                g = mul(num, inv(denom));
            }
            long long binom = binomial(k, j);
            Field c = mul(apow[j], bpow[k - j]);

            Field cur = {c.a * binom % M, c.b * binom % M};
            cur = mul(cur, g);

            S = add(S, cur);
        }
        cout << S.a << endl;

    }

    return 0;
}
