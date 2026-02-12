//https://codeforces.com/contest/2034/problem/F1
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const int K = 505;
const ll M = 998244353;

ll inv[N];
ll fact[N];
ll factinv[N];
ll dp[N];
ll ways[K][K];

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

ll binomial(ll n, ll k) {
    return fact[n] * factinv[k] % M * factinv[n - k] % M;
}

bool comp(pair<int, int> a, pair<int, int> b) {
    if (a.first == b.first) {
        return a.second < b.second;
    }
    return a.first < b.first;
}

ll prob(int x, int y, int n, int m) {
    return binomial(x + y - 2, x - 1) * binomial(n + m - x - y, n - x) % M * modPow(binomial(n + m - 2, n - 1), M - 2) % M;
}

ll paths(int x1, int y1, int x2, int y2) {
    return binomial(x2 - x1 + y2 - y1, x2 - x1);
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
        int n, m, k;
        cin >> n >> m >> k;
        n++, m++;
        int ok = 0;
        vector<pair<int, int>> a;
        for (int i = 0; i < k; i++) {
            int x, y;
            cin >> x >> y;
            x = n - x, y = m - y;
            if (x == 1 && y == 1) {
                continue;
            }
            a.push_back({x, y});
            if (x == n && y == m) {
                ok = 1;
            }
        }
        if (!ok) {
            a.push_back({n, m});
        }
        a.push_back({1, 1});
        k = a.size();
        sort(a.begin(), a.end(), comp);
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                ways[i][j] = 0;
            }
            dp[i] = 0;
        }
        for (int i = 0; i < k; i++) {
            auto [x1, y1] = a[i];
            for (int j = i + 1; j < k; j++) {
                auto [x, y] = a[j];
                if (y1 > y) {
                    continue;
                }
                ways[i][j] = paths(x1, y1, x, y);
                for (int z = i + 1; z < j; z++) {
                    auto [x2, y2] = a[z];
                    if (!(y2 >= y1 && y2 <= y)) {
                        continue;
                    }
                    ways[i][j] = (ways[i][j] - ways[i][z] * paths(x2, y2, x, y) % M + M) % M;
                }
            }
        }

        for (int i = 1; i < k; i++) {
            auto [x, y] = a[i];
            int mul = 2;
            if (!ok && x == n && y == m) {
                mul = 1;
            }
            for (int j = 0; j < i; j++) {
                auto [x1, y1] = a[j];
                if (y1 > y) {
                    continue;
                }
                int add = ((x - x1) * 2 + y - y1);
                ll p_j = prob(x1, y1, n, m);
                ll p_ji = prob(x - x1 + 1, y - y1 + 1, n - x1 + 1, m - y1 + 1) * ways[j][i] % M * modPow(paths(x1, y1, x, y), M - 2) % M;
                dp[i] = (dp[i] + (dp[j] * p_ji + add * p_j % M * p_ji) * mul) % M;
            }
        }
        cout << dp[k - 1] << endl;
    }


    return 0;
}
