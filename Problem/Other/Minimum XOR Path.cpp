//https://atcoder.jp/contests/abc396/tasks/abc396_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 15;

long long d[N][N];


int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            d[i][j] = -1;
        }
    }
    for (int i = 0; i < m; i++) {
        int u, v; long long wt;
        cin >> u >> v >> wt;
        u--, v--;
        d[u][v] = wt;
        d[v][u] = wt;
    }
    long long ans = 1LL << 60;
    for (int j = 1; j < 1 << n; j++) {
        vector<int> v;
        bool can = true;
        for (int i = 0; i < n; i++) {
            int c = (1 << i) & j;
            if (i == 0 && !c) {
                can = false;
            }
            if (i == n - 1 && !c) {
                can = false;
            }
            if (c) {
                v.push_back(i);
            }
        }
        if (!can) {
            continue;
        }
        do {
            long long cur = 0;
            if (v[0] != 0 || v.back() != n - 1) {
                continue;
            }
            bool can = true;
            for (int i = 1; i < v.size(); i++) {
                if (d[v[i]][v[i - 1]] == -1) {
                    can = false;
                    break;
                }
                cur ^= d[v[i]][v[i - 1]];
            }
            if (can) {
                ans = min(ans, cur);
            }
        } while (next_permutation(v.begin(), v.end()));
    }
    cout << ans;
    return 0;
}
