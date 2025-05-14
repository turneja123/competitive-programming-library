//https://codeforces.com/problemset/problem/2019/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int parent[N];
int ct[2][N];
int start[N];
int sz[N];
bool vis[N];

int good = 0, reds = 0;

int dsu_find(int u) {
    if (parent[u] == u) {
        return u;
    }
    return parent[u] = dsu_find(parent[u]);
}

void dsu_merge(int a, int b) {
    if (sz[a] > sz[b]) {
        swap(a, b);
    }
    reds -= sz[a] / 2 + sz[a] % 2;
    int alla = ct[0][a] + ct[1][a];
    if (alla) {
        if (sz[a] % 2 == 0 || ct[start[a] % 2][a]) {
            good--;
        }
    }
    reds -= sz[b] / 2 + sz[b] % 2;
    int allb = ct[0][b] + ct[1][b];
    if (allb) {
        if (sz[b] % 2 == 0 || ct[start[b] % 2][b]) {
            good--;
        }
    }

    sz[b] += sz[a];
    start[b] = min(start[b], start[a]);
    ct[0][b] += ct[0][a];
    ct[1][b] += ct[1][a];
    parent[a] = b;
    int all = ct[0][b] + ct[1][b];
    if (all) {
        if (sz[b] % 2 == 0 || ct[start[b] % 2][b]) {
            good++;
        }
    }
    reds += sz[b] / 2 + sz[b] % 2;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int mx = 0;
        map<int, vector<int>> mp;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            mx = max(mx, a[i]);
            mp[a[i]].push_back(i);
        }
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            start[i] = i;
            sz[i] = 1;
            if (a[i] == mx) {
                ct[i % 2][i]++;
            }
        }
        int ans = 2 * mx + 1;
        reds = 0; good = 0;
        for (auto it = mp.rbegin(); it != mp.rend(); it++) {
            auto [mn, v] = *it;
            for (int j : v) {
                reds++;
                vis[j] = true;
                if (a[j] == mx) {
                    good++;
                }
                if (j != 0 && vis[j - 1]) {
                    dsu_merge(dsu_find(j), dsu_find(j - 1));
                }
                if (j != n - 1 && vis[j + 1]) {
                    dsu_merge(dsu_find(j), dsu_find(j + 1));
                }
            }
            ans = max(ans, mx + mn + reds - (good == 0));
        }
        cout << ans << endl;
        for (int i = 0; i < n; i++) {
            vis[i] = 0;
            ct[0][i] = 0;
            ct[1][i] = 0;
        }
    }
    return 0;
}
