//https://codeforces.com/contest/2056/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;
const ll M = 998244353;


ll inv[N];
ll fact[N];
ll factinv[N];
ll c[N];

ll binomial(ll n, ll k) {
    return fact[n] * factinv[k] % M * factinv[n - k] % M;
}

ll d[N];

int main() {
    IOS;
    fact[0] = 1, factinv[0] = 1;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
        fact[i] = fact[i - 1] * i % M;
        factinv[i] = factinv[i - 1] * inv[i] % M;
    }
    c[0] = 1;
    for (int i = 1; 2 * i < N; i++) {
        c[i] = binomial(2 * i, i) * inv[i + 1] % M;
    }
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        int ok = 0;
        vector<pair<int, int>> a;
        vector<int> o(n + 1);
        for (int i = 0; i < m; i++) {
            int l, r;
            cin >> l >> r;
            a.push_back({l, r});
            if (l == 1 && r == n) {
                ok = 1;
            }
            if (l == r) {
                o[l] = 1;
            }
        }
        if (!ok) {
            a.push_back({1, n});
        }
        for (int i = 1; i <= n; i++) {
            if (!o[i]) {
                a.push_back({i, i});
            }
        }
        sort(a.begin(), a.end(), [&](auto x, auto y) {
             if (x.first != y.first) {
                return x.first < y.first;
             }
             return x.second > y.second;
        });
        set<tuple<int, int, int>> nearest;
        priority_queue<pair<int, int>> pq;
        for (int i = 0; i < a.size(); i++) {
            auto [l, r] = a[i];
            while (pq.size() && -pq.top().first < l) {
                auto [_, j] = pq.top();
                nearest.erase(nearest.find({-a[j].first, a[j].second, j}));
                pq.pop();
            }
            if (nearest.size()) {
                auto [_, __, j] = *nearest.begin();
                d[j]++;
            }
            pq.push({-r, i});
            nearest.insert({-l, r, i});
        }
        ll ans = 1;
        for (int i = 0; i < a.size(); i++) {
            ans = ans * (d[i] == 0 ? 1 : c[d[i] - 1]) % M;
            d[i] = 0;
        }
        cout << ans << endl;
    }

    return 0;
}
