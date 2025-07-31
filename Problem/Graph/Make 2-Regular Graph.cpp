//https://atcoder.jp/contests/abc412/tasks/abc412_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

bitset<8> g[8];

int cyc(vector<int> a) {
    int n = a.size();
    int ans = 0;
    for (int i = 0; i < n; i++) {
        int u = a[i], v = a[(i + 1) % n];
        ans += (g[u][v] ? -1 : 1);
    }
    return ans;
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].set(v);
        g[v].set(u);
    }
    vector<int> a(n);
    iota(a.begin(), a.end(), 0);
    int ans = 64;
    do {
        ans = min(ans, cyc(a) + m);
        if (a.size() >= 6) {
            ans = min(ans, cyc({a.begin(), a.begin() + 3}) + cyc({a.begin() + 3, a.end()}) + m);
        }
        if (a.size() >= 7) {
            ans = min(ans, cyc({a.begin(), a.begin() + 4}) + cyc({a.begin() + 4, a.end()}) + m);
        }
        if (a.size() >= 8) {
            ans = min(ans, cyc({a.begin(), a.begin() + 5}) + cyc({a.begin() + 5, a.end()}) + m);
        }
    } while (next_permutation(a.begin(), a.end()));
    cout << ans;
    return 0;
}
