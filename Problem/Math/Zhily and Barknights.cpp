//https://codeforces.com/contest/2223/problem/B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2005;
const ll M = 998244353;

ll inv[N];
ll fact[N];
ll factinv[N];

bool comp(pair<int, int> a, pair<int, int> b) {
    return (ll)a.first * b.second < (ll)a.second * b.first;
}

vector<pair<int, int>> rle(vector<int> &a) {
    int n = a.size();
    vector<pair<int, int>> v;
    int last = -1, ct = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] != last) {
            if (ct) {
                v.push_back({last, ct});
            }
            last = a[i];
            ct = 1;
        } else {
            ct++;
        }
    }
    v.push_back({last, ct});
    return v;
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
        int n;
        cin >> n;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }
        vector<pair<int, int>> v;
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                v.push_back({a[j], a[i]});
            }
        }
        sort(v.begin(), v.end(), comp);

        sort(b.begin(), b.end());
        vector<pair<int, int>> c = rle(b);
        ll ans = 0, ifa = 1;
        for (auto [_, f] : c) {
            ifa = ifa * factinv[f] % M;
        }

        for (int i = 0; i < c.size(); i++) {
            for (int j = 0; j < c.size(); j++) {
                auto [a, xa] = c[i]; auto [b, xb] = c[j];
                if (i == j && xa == 1) {
                    continue;
                }
                int l = 0, r = v.size() - 1, spl = 0;
                while (l <= r) {
                    int mid = (l + r) / 2;
                    if (comp(v[mid], make_pair(a, b))) {
                        l = mid + 1;
                        spl = mid + 1;
                    } else {
                        r = mid - 1;
                    }
                }
                ll mul;
                if (i == j) {
                    mul = ifa * fact[xa] % M * factinv[xa - 2] % M;
                } else {
                    mul = ifa * fact[xa] % M * fact[xb] % M * factinv[xa - 1] % M * factinv[xb - 1] % M;
                }
                ans = (ans + spl * mul % M * fact[n - 2]) % M;
            }
        }
        ans = ans * factinv[n] % M * modPow(ifa, M - 2) % M;
        cout << ans << endl;

    }
    return 0;
}
