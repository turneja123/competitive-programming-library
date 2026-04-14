//https://atcoder.jp/contests/arc217/tasks/arc217_c
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 105;
const ll M = 998244353;

ll inv[N];
ll fact[N];
ll factinv[N];

ll dp[N][N][N];

ll binomial(ll n, ll k) {
    return fact[n] * factinv[k] % M * factinv[n - k] % M;
}

ll modPow(ll a, ll y) {
    ll res = 1;
    while (y > 0) {
        if (y % 2 != 0) {
            res = res * a % M;
        }
        y /= 2;
        a = a * a % M;
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
        int n, c;
        cin >> n >> c;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        vector<tuple<int, int, int>> v;
        v.push_back({-1, -1, -1});
        if (a[0] != 1) {
            v.push_back({1, a[0] - 1, 0});
        }
        for (int i = 0; i < n;) {
            int last = a[i];
            while (i < n && last == a[i]) {
                i++;
            }
            int r = (i == n ? c : a[i] - 1);
            v.push_back({last, r, i});
        }
        dp[0][0][0] = 1;
        int m = v.size();
        for (int i = 1; i < m; i++) {
            auto [l, r, mx] = v[i];
            int picks = r - l + 1;
            for (int j = 0; j <= n; j++) {
                for (int k = 0; k <= j; k++) {
                    ll prod = 1;
                    for (int add = 0; j + add <= n; add++) {
                        dp[i][j + add][min(mx, k + add)] = (dp[i][j + add][min(mx, k + add)] + dp[i - 1][j][k] * prod % M * binomial(n - j, add)) % M;
                        prod = prod * picks % M;
                    }
                }
            }
        }
        for (int k = 0; k <= n; k++) {
            cout << dp[m - 1][n][k] * modPow(modPow(c, n), M - 2) % M<< " ";
        }
        cout << endl;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j <= n; j++) {
                for (int k = 0; k <= n; k++) {
                    dp[i][j][k] = 0;
                }
            }
        }
    }


    return 0;
}
