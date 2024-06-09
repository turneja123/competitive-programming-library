//https://www.spoj.com/problems/DTRAP/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 25;

int a[N];
int parent[N];
bool vis[N];
vector<int> adj[N];

void dfs(int u, int p) {
    vis[u] = true;
    parent[u] = p;
    for (int v : adj[u]) {
        if (!vis[v]) {
            dfs(v, p);
        }
    }
    return;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, w, m;
        cin >> n >> w >> m;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            cin >> a[i];
        }
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            vis[i] = false;
        }
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                dfs(i, i);
            }
        }
        int bits = 1 << n, ans = 0;
        for (int j = 1; j < bits; j++) {
            int cur = 0, root = -1;
            bool can = true;
            for (int i = 0; i < n && can; i++) {
                if (j & (1 << i)) {
                    cur += a[i];
                    if (root == -1) {
                        root = parent[i];
                    } else if (root != parent[i]) {
                        can = false;
                    }
                }
            }
            if (can && cur == w) {
                ans++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
