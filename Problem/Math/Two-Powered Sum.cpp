//https://atcoder.jp/contests/arc221/tasks/arc221_b
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 705;
ll M;

ll inv[N];
ll fact[N];
ll factinv[N];
ll pw[N];

ll ans[N];

ll binomial(ll n, ll k) {
    return fact[n] * factinv[k] % M * factinv[n - k] % M;
}

int main() {
    IOS;
    int n;
    cin >> n >> M;
    fact[0] = 1, factinv[0] = 1, pw[0] = 1;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
        pw[i] = pw[i - 1] * 2  % M;
    }
    ans[0] = 1;
    ll sum = 1;
    for (int i = 1; i <= n; i++) {
        vector<ll> dp(n + 1, 0);
        for (int j = i; j <= n; j++) {
            dp[j - i + 1] = pw[i - 1];
            for (int k = 1; k <= j - i; k++) {
                dp[j - i + 1] = (dp[j - i + 1] - dp[k] * binomial(j - i, k) % M * pw[i - 1] % M + M) % M;
            }
            ans[j] = (ans[j] + ans[i - 1] * binomial(j, j - i + 1) % M * dp[j - i + 1]) % M;
        }
        sum = (sum + ans[i] * binomial(n, i)) % M;
    }
    cout << sum;
    return 0;
}
