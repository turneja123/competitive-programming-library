//https://www.facebook.com/codingcompetitions/hacker-cup/2025/round-2/problems/D
#pragma GCC target("avx2")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int M = 998244353;

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

int s(string &s) {
    int n = s.size();
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = ((ll)ans * 10 + (s[i] - '0')) % M;
    }
    return ans;
}

__int128 _toi(string &s) {
    int n = s.size();
    __int128 ans = 0;
    for (int i = 0; i < n; i++) {
        ans = (__int128)ans * 10 + (s[i] - '0');
    }
    return ans;
}

ll f(int tight, int mask, int rem = 0) {
    return ((ll)mask << 7) | ((ll)rem << 2) | (ll)tight;
}

tuple<int, int> uf(ll z) {
    int tight = z & 3;
    int mask = z >> 7;
    return make_tuple(tight, mask);
}

int cyc(int x, int s, int k) {
    int mask = (1 << k) - 1;
    x &= mask;
    return ((x >> s) | (x << (k - s))) & mask;
}

int calc(__int128 n, int k) {
    if (n == 0) {
        return 0;
    }
    vector<int> b;
    while (n > 0) {
        b.push_back(n % 10);
        n /= 10;
    }
    reverse(b.begin(), b.end());
    gp_hash_table<ll, int, custom_hash> dp;
    gp_hash_table<ll, int, custom_hash> dp_nx;

    int ans = 0;
    for (int d = 1; d < 10; d++) {
        int tight;
        if (d < b[0]) {
            tight = 0;
        }
        if (d == b[0]) {
            tight = 2;
        }
        if (d > b[0]) {
            tight = 1;
        }
        if (d % k == 0) {
            continue;
        }
        int j = d % k;
        int mask = 1 + (1 << j);
        dp[f(tight, cyc(mask, j, k))] = 1;
        if (tight != 1 || b.size() > 1) {
            ans++;
        }
    }
    for (int i = 1; i < b.size(); i++) {
        for (auto it = dp.begin(); it != dp.end(); ++it) {

            auto [t, mask] = uf(it->first);
            int add = it->second;

            for (int d = 1; d < 10; d++) {
                int j = d % k;
                if (j == 0) {
                    continue;
                }
                int mask_nx = mask | (1 << j);
                if (mask_nx == mask) {
                    continue;
                }

                int tight;
                if (t == 1) {
                    tight = 1;
                } else if (t == 0) {
                    tight = 0;
                } else if (t == 2) {
                    if (d < b[i]) {
                        tight = 0;
                    }
                    if (d == b[i]) {
                        tight = 2;
                    }
                    if (d > b[i]) {
                        tight = 1;
                    }
                }
                int j_nx = cyc(mask_nx, j, k);

                dp_nx[f(tight, j_nx)] = (dp_nx[f(tight, j_nx)] + add) % M;
                if (tight != 1 || i != b.size() - 1) {
                    ans = (ans + add) % M;
                }


            }
        }
        dp = dp_nx;
        dp_nx.clear();
    }
    return ans;

}

int main() {
    //IOS;
    freopen("248.in", "r", stdin);
    //freopen("248.out", "w", stdout);
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        string l, r;
        cin >> l >> r;
        int k;
        cin >> k;
        int ans = (s(r) - s(l) + 1 + M) % M;
        __int128 L, R;
        cout << "Case #" << tt << ": ";

        if (l.size() >= k) {
            cout << ans << endl;
            continue;
        }
        L = _toi(l) - 1;
        if (r.size() < k) {
            R = _toi(r);
        } else {
            R = 1;
            for (int i = 0; i < k - 1; i++) {
                R *= 10;
            }
        }
        int bad = (calc(R, k) - calc(L, k) + M) % M;
        cout << (ans - bad + M) % M << endl;




    }
    return 0;
}

