//https://www.spoj.com/problems/FIBPSUM2/
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

struct Field {
    long long a, b;
};

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
    long long na = (x.a * y.a + x.b * y.b * 5) % M;
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
    long long n = (x.a * x.a % M - 5 * x.b * x.b % M + M) % M;
    long long invn = modPow(n, M - 2);
    long long na = x.a;
    long long nb = (-x.b + M) % M;
    na = (na * invn) % M;
    nb = (nb * invn) % M;
    return {na, nb};
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
    Field sqrt5 = {0, 1};

    long long inv2 = modPow(2, M - 2);
    Field phi = {inv2, inv2};
    Field psi = {inv2, ((M - 1) * inv2) % M};

    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        long long n, c; int k;
        cin >> n >> c >> k;
        cout << "Case " << tt << ": ";
        if (k == 0) {
            cout << (n + 1) % M << endl;
            continue;
        }
        Field a = fpow(phi, c);
        Field b = fpow(psi, c);

        Field binv = inv(b);
        Field x = mul(a, binv);

        Field y = fpow(b, k);

        vector<Field> xpow(k + 1);
        xpow[0] = o;
        for (int j = 1; j <= k; j++){
            xpow[j] = mul(xpow[j - 1], x);
        }
        Field z = fpow(x, n + 1);
        vector<Field> zpow(k + 1);
        zpow[0] = o;
        for (int j = 1; j <= k; j++){
            zpow[j] = mul(zpow[j - 1], z);
        }
        Field yn = fpow(y, n + 1);
        Field S = {0,0};

        for (int j = 0; j <= k; j++){
            Field r = mul(y, xpow[j]);
            Field g;
            if (r.a == 1 && r.b == 0){
                g = {(n + 1) % M, 0};
            } else {
                Field num = sub(mul(yn, zpow[j]), o);
                Field denom = sub(r, o);
                g = mul(num, inv(denom));
            }
            long long binom = binomial(k, j);
            long long sgn = (((k - j) % 2) ? (M - 1) : 1);

            Field cur = {g.a * binom % M, g.b * binom % M};
            cur.a = (cur.a * sgn) % M;
            cur.b = (cur.b * sgn) % M;

            S = add(S, cur);
        }
        Field ans = mul(inv(fpow(sqrt5, k)), S);
        cout << ans.a << endl;
    }

    return 0;
}
