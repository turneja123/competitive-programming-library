//https://codeforces.com/contest/1549/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e6 + 5;
const ll M = 1e9 + 7;

ll inv[N];
ll fact[N];
ll factinv[N];
ll dp[N][3];

ll binomial(ll n, ll k) {
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
    int n, q;
    cin >> n;
    dp[0][0] = n, dp[0][1] = n, dp[0][2] = n;
    for (int i = 1; i <= 3 * n; i++) {
        ll s = binomial(3 * n + 1, i + 1);
        dp[i][1] = (s - 2 * dp[i - 1][1] % M - dp[i - 1][2] + M + M) * (M + 1) / 3 % M;
        dp[i][2] = (dp[i][1] + dp[i - 1][1]) % M;
        dp[i][0] = (s - dp[i][2] - dp[i][1] + M + M) % M;
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        int x;
        cin >> x;
        cout << dp[x][0] << endl;
    }


    return 0;
}
