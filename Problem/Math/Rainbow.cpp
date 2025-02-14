//https://www.spoj.com/problems/RAINBOW2/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const ll MOD = 1000002015;

struct Matrix {
    ll a[2][2];
};

Matrix multiply(const Matrix &A, const Matrix &B) {
    Matrix C;
    C.a[0][0] = (A.a[0][0] * B.a[0][0] + A.a[0][1] * B.a[1][0]) % MOD;
    C.a[0][1] = (A.a[0][0] * B.a[0][1] + A.a[0][1] * B.a[1][1]) % MOD;
    C.a[1][0] = (A.a[1][0] * B.a[0][0] + A.a[1][1] * B.a[1][0]) % MOD;
    C.a[1][1] = (A.a[1][0] * B.a[0][1] + A.a[1][1] * B.a[1][1]) % MOD;
    return C;
}

Matrix modPow(Matrix base, ll y) {
    Matrix res;
    res.a[0][0] = 1; res.a[0][1] = 0;
    res.a[1][0] = 0; res.a[1][1] = 1;
    while (y > 0) {
        if (y % 2) {
            res = multiply(res, base);
        }
        base = multiply(base, base);
        y /= 2;
    }
    return res;
}

int main() {
    //IOS;
    int n, k, d, q, m;
    while (cin >> n >> k >> d >> q >> m) {
        long long x = ((long long)n * (n - 1) / 2) % MOD;
        long long y = 1, z = 0;
        vector<long long> qpow(n);
        qpow[0] = 1;
        for (int i = 1; i < n; i++) {
            qpow[i] = (qpow[i - 1] * q) % MOD;
            y = (y + qpow[i]) % MOD;
            z = (z + (long long)i * qpow[i]) % MOD;
        }

        Matrix ans;
        ans.a[0][0] = y;
        ans.a[0][1] = n;
        ans.a[1][0] = d * z % MOD;
        ans.a[1][1] = d * x % MOD;
        ans = modPow(ans, k - 1);

        for (int i = 0; i < m; i++) {
            int r, c;
            cin >> r >> c;
            long long x = (ans.a[0][0] + (long long)r * ans.a[0][1] % MOD * d) % MOD;
            long long y = (ans.a[1][0] + (long long)r * ans.a[1][1] % MOD * d) % MOD;
            long long sum = (x * qpow[c] + y) % MOD;
            cout << sum << endl;
        }
    }
    return 0;
}
