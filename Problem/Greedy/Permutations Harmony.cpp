//https://codeforces.com/contest/2034/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll M = 1e9 + 7;
const ll P = 26, INV_P = 576923081;
const ll Q = 53, INV_Q = 56603774;

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

ll calc(vector<int> &s) {
    int n = s.size();
    ll p = 0, q = 0;
    ll p_pow = 1, q_pow = 1;
    for (int i = 0; i < n; i++) {
        p = (p + p_pow * s[i]) % M;
        q = (q + q_pow * s[i]) % M;
        p_pow = (p_pow * P) % M;
        q_pow = (q_pow * Q) % M;
    }
    return (p + (q << 32));
}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        if (n == 1) {
            if (k == 1) {
                cout << "YES" << endl << 1 << endl;
            } else {
                cout << "NO" << endl;
            }
            continue;
        }
        if (k == 1) {
            cout << "NO" << endl;
            continue;
        }
        if (n % 2 == 0 && k % 2 == 1) {
            cout << "NO" << endl;
            continue;
        }
        vector<vector<int>> ans(k, vector<int>(n, 0));
        gp_hash_table<ll, int, custom_hash> mp;
        int i = 0;
        if (k % 2 == 1) {
            int need = (n + 1) / 2 * 3;
            iota(ans[0].begin(), ans[0].end(), 1);
            for (int i = 0, j = (n + 1) / 2; i < n; i++, j++) {
                if (j > n) {
                    j = 1;
                }
                ans[1][i] = j;
                ans[2][i] = need - ans[1][i] - ans[0][i];
            }
            mp[calc(ans[0])] = 1;
            mp[calc(ans[1])] = 1;
            mp[calc(ans[2])] = 1;
            i = 3;
        }

        int ok = 1;
        vector<int> perm(n, 0);
        iota(perm.begin(), perm.end(), 1);
        for (; i < k && ok; i += 2) {
            while (1) {
                vector<int> inv = perm;
                for (int j = 0; j < n; j++) {
                    inv[j] = n + 1 - perm[j];
                }
                ll ha = calc(perm), hb = calc(inv);
                if (mp.find(ha) == mp.end() && mp.find(hb) == mp.end()) {
                    ans[i] = perm;
                    ans[i + 1] = inv;
                    mp[ha] = 1;
                    mp[hb] = 1;
                    break;
                } else {

                    bool b = next_permutation(perm.begin(), perm.end());
                    if (!b) {
                        ok = 0;
                        break;
                    }
                }
            }
        }
        if (!ok) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
            for (int i = 0; i < k; i++) {
                for (int j = 0; j < n; j++) {
                    cout << ans[i][j] << " ";
                }
                cout << endl;
            }
        }

    }

    return 0;
}
