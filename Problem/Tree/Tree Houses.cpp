//solution for https://www.codechef.com/MAY21C/problems/THOUSES
#include <bits/stdc++.h>

using namespace std;

const int N = 3e5 + 5;
const long long M = 1e9 + 7;
long long ans = 0;

vector<vector<int>> adj;
long long sz[N];
long long val[N];

long long dfs(int v, long long ct, int p) {
    vector<long long> l;
    for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
        if (*it != p) {
            l.push_back(dfs(*it, 1, v));
        }
    }
    sort(l.begin(), l.end());
    reverse(l.begin(), l.end());
    for (long long i = 0; i < l.size(); i++) {
        ct += (i + 1) * l[i];
    }
    return sz[v] = ct;
}

void solve(int v, int p) {
    vector<pair<long long, int>> child;
    for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
        if (*it != p) {
            child.push_back({sz[*it], *it});
        }
    }
    sort(child.begin(), child.end());
    reverse(child.begin(), child.end());
    val[v] %= M;
    long long x = val[v];
    for (auto it = child.begin(); it != child.end(); ++it) {
        ans += x;
        ans %= M;
        val[it->second] = x;
        solve(it->second, v);
        x += val[v];
        x %= M;
    }
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        int n; long long x;
        cin >> n >> x;
        adj.resize(n);
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
        for (int i = 1; i < n; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(0, 0ll, 0);
        ans = x;
        val[0] = x;
        solve(0, 0);
        cout << ans << endl;
        adj.clear();
    }
    return 0;
}
