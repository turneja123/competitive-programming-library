//https://repovive.com/contests/4/problems/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int sz[N];
vector<int> adj[N];

void dfs_subtree(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p) {
            dfs_subtree(v, u);
            sz[u] += sz[v];
        }
    }
    return;
}

int dfs_centroid(int u, int p, int n) {
    for (int v : adj[u]) {
        if (v != p && sz[v] > n / 2) {
            return dfs_centroid(v, u, n);
        }
    }
    return u;
}

void build(int u, int p, int n) {
    dfs_subtree(u, u);
    int c = dfs_centroid(u, u, sz[u]);
    dfs_subtree(c, c);
    vector<int> child;
    for (int v : adj[c]) {
        child.push_back(sz[v]);
    }
    sort(child.begin(), child.end());
    reverse(child.begin(), child.end());
    int s = 0, m = child.size();
    for (int i = 0; i < m; i++) {
        s += child[i];
        cout << min(s, n / 2) << " ";
    }
    for (int i = m; i < n - 1; i++) {
        cout << n / 2 << " ";
    }
    cout << endl;

    return;
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
        build(0, -1, n);
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
    }


    return 0;
}
