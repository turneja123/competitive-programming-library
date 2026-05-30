//https://codeforces.com/contest/2062/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

vector<int> adj[N];
int l[N], r[N];
int val[N];
ll down[N];

void dfs(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            if (val[u] <= val[v]) {
                if (r[u] >= val[v]) {
                    val[u] = max(val[u], val[v]);
                } else {
                    val[u] = r[u];
                    down[0] += val[v] - val[u];
                    down[v] -= val[v] - val[u];
                }
            } else {
                if (r[v] >= val[u]) {
                    val[v] = max(val[v], val[u]);
                } else {
                    val[v] = r[v];
                    down[v] += val[u] - val[v];
                }
            }

        }
    }

}

void dfs_add(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            down[v] += down[u];
            dfs_add(v, u);
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
            cin >> l[i] >> r[i];
            val[i] = l[i];
        }
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(0, 0);
        dfs_add(0, 0);
        ll ans = 0;
        for (int i = 0; i < n; i++) {
            ans = max(ans, val[i] + down[i]);
            adj[i].clear();
            down[i] = 0;
        }
        cout << ans << endl;
    }

    return 0;
}
