//https://dmoj.ca/problem/dcc1p3
#pragma GCC optimize("Ofast,fast-math")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 805;

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

int a[N][N];
long long pref[N][N];

void preprocess(int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            pref[i][j] = a[i][j] + (i > 0 ? pref[i - 1][j] : 0) + (j > 0 ? pref[i][j - 1] : 0) - (i > 0 && j > 0 ? pref[i - 1][j - 1] : 0);
        }
    }
    return;
}

long long query(int x1, int y1, int x2, int y2) {
    long long ans = pref[x2][y2] - (x1 > 0 ? pref[x1 - 1][y2] : 0) - (y1 > 0 ? pref[x2][y1 - 1] : 0) + (x1 > 0 && y1 > 0 ? pref[x1 - 1][y1 - 1] : 0);
    return ans;
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> a[i][j];
        }
    }
    preprocess(n, m);
    int ans = 0;
    for (int k = 0; k < m; k++) {
        for (int j = 0; j < m; j++) {
            if (k - j < 0 || k + j + 1 >= m) {
                continue;
            }
            long long sum = 0;
            gp_hash_table<long long, int, custom_hash> mp;
            mp[0] = -1;
            int dim = 0;
            for (int i = 0; i < n; i++) {
                sum += query(i, k - j, i, k) - query(i, k + 1, i, k + 1 + j);
                auto [it, f] = mp.insert({sum, i});
                if (!f) {
                    dim = max(dim, i - it->second);
                }
            }
            ans = max(ans, dim * (2 * (j + 1)));
        }
    }
    cout << ans;
    return 0;
}
