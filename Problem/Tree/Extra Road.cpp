//https://codeforces.com/contest/2290/problem/H
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

vector<int> adj[N];
int sz[N];

void dfs_sz(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p) {
            dfs_sz(v, u);
            sz[u] += sz[v];
        }
    }
}

int dfs(int u, int p) {
    int ans = 0;
    vector<int> child;
    for (int v : adj[u]) {
        if (v != p) {
            child.push_back(v);
        }
    }
    sort(child.begin(), child.end(), [&](int u, int v) {return sz[u] > sz[v];});
    for (int i = 0; i < child.size(); i++) {
        int v = child[i];
        ans = max(ans, dfs(v, u));
        if (i != 0) {
            ans = max(ans, sz[v]);
        }
    }
    return ans;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs_sz(0, 0);
        sort(adj[0].begin(), adj[0].end(), [&](int u, int v) {return sz[u] > sz[v];});
        int ans;
        if (adj[0].size() == 1) {
            ans = dfs(adj[0][0], 0);
        } else {
            ans = max(dfs(adj[0][0], 0), dfs(adj[0][1], 0));
            for (int i = 2; i < adj[0].size(); i++) {
                ans = max(ans, sz[adj[0][i]]);
            }
        }
        cout << n - ans << endl;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }

    }

    return 0;
}
