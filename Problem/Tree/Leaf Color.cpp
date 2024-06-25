//https://atcoder.jp/contests/abc340/tasks/abc340_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long M = 998244353;

int a[N];
int parent[N];
vector<int> adj[N];
map<int, long long> mp[N];
map<int, long long> dp[N];
long long ans = 0;

int dsu_find(int p) {
    if (parent[p] == p) {
        return p;
    }
    parent[p] = dsu_find(parent[p]);
    return parent[p];
}

void dsu_merge(int a, int b, int u) {
    if (mp[a].size() > mp[b].size()) {
        swap(a, b);
    }
    int k = 0;
    if (dsu_find(u) == a) {
        k = 1;
    }
    parent[a] = b;
    for (auto it = mp[a].begin(); it != mp[a].end(); ++it) {
        auto f = mp[b].find(it->first);
        if (f != mp[b].end()) {
            if (dp[u][it->first] == 0) {
                dp[u][it->first] = (long long)(it->second + 1) * (f->second + 1) % M;
            } else {
                if (k == 0) {
                    ans = (ans - (dp[u][it->first] - (f->second + 1)) + M) % M;
                    dp[u][it->first] = dp[u][it->first] * (it->second + 1) % M;
                } else {
                    ans = (ans - (dp[u][it->first] - (it->second + 1)) + M) % M;
                    dp[u][it->first] = dp[u][it->first] * (f->second + 1) % M;
                }

            }
            ans = (ans + dp[u][it->first] - (it->second + f->second + 1) + M) % M;
        }

    }
    for (auto it = mp[a].begin(); it != mp[a].end(); ++it) {
        mp[b][it->first] = (mp[b][it->first] + it->second) % M;
    }
    return;
}

void dfs(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
    for (int v : adj[u]) {
        if (v != p) {
            int a = dsu_find(u), b = dsu_find(v);
            dsu_merge(a, b, u);
        }
    }
    int d = dsu_find(u);

    ans = (ans + mp[d][a[u]] + 1) % M;
    for (auto it = dp[u].begin(); it != dp[u].end(); ++it) {
        mp[d][it->first] = (it->second - 1 + M) % M;
    }

    mp[d][a[u]]++;
    return;
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }
    dfs(0, -1);
    cout << ans;

    return 0;
}
