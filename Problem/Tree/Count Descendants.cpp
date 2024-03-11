//solution for https://atcoder.jp/contests/abc202/tasks/abc202_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

list<int> adj[N];
vector<int> layer[N];
int depth[N];
int parent[N];
int tin[N];
int tout[N];

int timer = 0;

void dfs(int v, int p) {
    tin[v] = ++timer;
    layer[depth[v]].push_back(tin[v]);
    for (int u : adj[v]) {
        if (u != parent[v]) {
            depth[u] = depth[v] + 1;
            parent[u] = v;
            dfs(u, v);
        }
    }
    tout[v] = ++timer;
}

int main() {
    IOS;
    int n, q;
    cin >> n;
    for (int i = 1; i < n; i++) {
        int p; cin >> p; p--;
        adj[i].push_back(p);
        adj[p].push_back(i);
    }
    dfs(0, 0);
    cin >> q;
    while (q--) {
        int v, d;
        cin >> v >> d;
        v--;
        int ans = upper_bound(layer[d].begin(), layer[d].end(), tout[v]) - lower_bound(layer[d].begin(), layer[d].end(), tin[v]);
        cout << ans << endl;
    }


    return 0;
}
