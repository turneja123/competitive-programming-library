//https://www.codechef.com/problems/MAGNET
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

vector<int> adj[N];

int mx, node;
int parent[N];

void dfs(int u, int p, int d) {
    for (int v : adj[u]) {
        if (v != p) {
            if (d + 1 > mx) {
                mx = d + 1;
                node = v;
            }
            parent[v] = u;
            dfs(v, u, d + 1);
        }
    }
    return;
}

void dfs_print(int u, int p) {
    if (u != node && u != parent[node]) {
        cout << u + 1 << " ";
    }
    for (int v : adj[u]) {
        if (v != p) {
            dfs_print(v, u);
        }
    }
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        mx = 0;
        dfs(0, -1, 1);
        mx = 0;
        dfs(node, -1, 1);
        if (mx < 4) {
            cout << -1 << endl;
            continue;
        }
        cout << parent[node] + 1 << " " << node + 1 << " ";
        dfs_print(parent[node], node);
        cout << endl;
    }

    return 0;
}
