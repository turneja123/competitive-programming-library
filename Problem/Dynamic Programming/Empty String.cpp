//https://cses.fi/problemset/task/1080/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 505;
const long long M = 1e9 + 7;

long long dp[N][N];

long long inv[N];
long long fact[N];
long long factinv[N];

long long binomial(long long n, long long k) {
    return fact[n] * factinv[k] % M * factinv[n - k] % M;
}


int main() {
    IOS;
    fact[0] = 1, factinv[0] = 1;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
    }
    string a;
    cin >> a;
    int n = a.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j + i < n; j++) {
            if (i % 2 == 0) {
                continue;
            }
            if (i == 1) {
                dp[j][j + 1] = a[j] == a[j + 1];
                continue;
            }
            for (int k = j + 1; k <= j + i; k++) {
                if (a[j] == a[k]) {
                    dp[j][j + i] = (dp[j][j + i] + ((j + 1 > k - 1) ? 1 : dp[j + 1][k - 1]) * ((k + 1 > j + i) ? 1 : dp[k + 1][j + i]) % M * binomial((i + 1) / 2, (k - j + 1) / 2)) % M;
                }
            }
        }
    }
    cout << dp[0][n - 1] << endl;
    return 0;
}
