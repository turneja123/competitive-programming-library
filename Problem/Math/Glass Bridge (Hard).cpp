//https://www.codechef.com/problems/SQUIDGAME2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 1e9 + 7;
const int N = 5e5 + 5;

long long inv[N];
long long fact[N];
long long factinv[N];

long long binomial(long long n, long long k) {
    return fact[n] * factinv[k] % M * factinv[n - k] % M;
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

int main() {
    IOS;
    fact[0] = 1, factinv[0] = 1;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
    }
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        long long inv = modPow(2, M - 2);
        /*dp[1][1] = inv, dp[1][2] = inv;
        for (int i = 2; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                dp[i][j] = (dp[i - 1][j] * inv + dp[i - 1][j - 1] * inv) % M;
            }
        }
        for (int i = 1; i <= m; i++) {
            if (i < n) {
                cout << 0 << " ";
                continue;
            }
            long long ans = 1;
            for (int j = 1; j <= n; j++) {
                ans = (ans - dp[i][j] + M) % M;
            }
            cout << ans << " ";
        }
        cout << endl;*/

        long long f = 0, pw = 1;
        for (int i = 0; i < min(m + 1, n); i++) {
            f = (f + binomial(n, i)) % M;
            pw = pw * inv % M;
            if (i != 0) {
                cout << 0 << " ";
            }
        }
        // f(n, k) = C(n, 0) + C(n, 1) + ... + C(n, k)
        // f(n + 1, k) = 2 * f(n, k) - C(n, k)
        for (int i = n; i <= m; i++) {
            cout << (1 - f * pw % M + M) % M << " ";
            pw = pw * inv % M;
            f = (f * 2 - binomial(i, n - 1) + M) % M;
        }
        cout << endl;
    }
    return 0;
}
