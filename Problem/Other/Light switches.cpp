//https://codeforces.com/contest/1423/problem/L
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int INF = 1e9;

struct BITSET {
    unsigned ll b[16];

    BITSET() {
        for (int i = 0; i < 16; i++) {
            b[i] = 0;
        }
    }

    void flip(int j) {
        b[j >> 6] ^= 1ULL << (j & 63);
    }

    void xor_other(BITSET &x) {
        for (int i = 0; i < 16; i++) {
            b[i] ^= x.b[i];
        }
    }

    bool operator < (const BITSET &x) const {
        for (int i = 0; i < 16; i++) {
            if (b[i] != x.b[i]) {
                return b[i] < x.b[i];
            }
        }
        return false;
    }

    bool operator == (const BITSET &x) const {
        for (int i = 0; i < 16; i++) {
            if (b[i] != x.b[i]) {
                return false;
            }
        }
        return true;
    }
};

BITSET b[30];

int main() {
    IOS;
    int m, n, q;
    cin >> m >> n >> q;
    for (int i = 0; i < n; i++) {
        int c;
        cin >> c;
        for (int j = 0; j < c; j++) {
            int k;
            cin >> k;
            k--;
            b[i].flip(k);
        }
    }
    vector<pair<BITSET, int>> v_tmp;
    int n_r = min(11, n / 2), n_l = n - n_r;
    for (int i = 0; i < 1 << n_l; i++) {
        BITSET cur;
        for (int j = 0; j < n_l; j++) {
            int c = i & (1 << j);
            if (c) {
                cur.xor_other(b[j]);
            }
        }
        v_tmp.push_back({cur, __builtin_popcount(i)});
    }
    sort(v_tmp.begin(), v_tmp.end());
    vector<pair<BITSET, int>> v;
    for (int i = 0; i < v_tmp.size(); i++) {
        if (i != 0 && v_tmp[i].first == v_tmp[i - 1].first) {
            continue;
        }
        v.push_back(v_tmp[i]);
    }
    while (q--) {
        BITSET qr;
        int c;
        cin >> c;
        for (int j = 0; j < c; j++) {
            int k;
            cin >> k;
            k--;
            qr.flip(k);
        }

        int ans = INF;
        for (int i = 0; i < 1 << n_r; i++) {
            BITSET cur = qr;
            for (int j = 0; j < n_r; j++) {
                int c = i & (1 << j);
                if (c) {
                    cur.xor_other(b[n_l + j]);
                }
            }
            auto it = lower_bound(v.begin(), v.end(), make_pair(cur, 0));
            if (it != v.end() && it->first == cur) {
                ans = min(ans, it->second + __builtin_popcount(i));
            }
        }
        if (ans == INF) {
            ans = -1;
        }
        cout << ans << endl;
    }
    return 0;
}
