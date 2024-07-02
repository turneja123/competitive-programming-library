//https://cses.fi/problemset/task/1131/
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

void dfs(int u, int p, int d) {
    for (int v : adj[u]) {
        if (v != p) {
            if (d + 1 > mx) {
                mx = d + 1;
                node = v;
            }
            dfs(v, u, d + 1);
        }
    }
    return;
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    mx = 0;
    dfs(0, -1, 0);
    mx = 0;
    dfs(node, -1, 0);
    cout << mx;

    return 0;
}
