//https://www.spoj.com/problems/TWOPATHS/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int INF = 1e9;

vector<int> adj[N];

int depth[N];
int subtree[N];
int subtree_path[N];

int aux[N];
int aux_path[N];
int dp[N];
int dp_path[N];

long long ans = 0;

void dfs_subtree(int u, int p) {
    pair<int, int> l = {-INF, -1}, r = {-INF, -1};
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs_subtree(v, u);
            subtree[u] = max(subtree[u], subtree[v] + 1);
            if (subtree[v] + 1 > r.first) {
                l = r;
                r = make_pair(subtree[v] + 1, v);
            } else if (subtree[v] + 1 > l.first) {
                l = make_pair(subtree[v] + 1, v);
            }
        }
    }
    subtree_path[u] = subtree[u];
    if (r.second != -1 && l.second != -1) {
        subtree_path[u] = max(subtree_path[u], r.first + l.first);
    }
    int ll = -INF, rl = -INF;
    int lr = -INF, rr = -INF;
    for (int v : adj[u]) {
        if (v != p && v != l.second && v != r.second) {
            aux[v] = r.first;
            aux_path[v] = r.first + l.first;
        }
        if (v != p && v != l.second) {
            if (subtree[v] + 1 > rl) {
                ll = rl;
                rl = subtree[v] + 1;
            } else if (subtree[v] + 1 > ll) {
                ll = subtree[v] + 1;
            }
        }
        if (v != p && v != r.second) {
            if (subtree[v] + 1 > rr) {
                lr = rr;
                rr = subtree[v] + 1;
            } else if (subtree[v] + 1 > lr) {
                lr = subtree[v] + 1;
            }
        }
    }
    if (l.second != -1) {
        aux[l.second] = rl;
        aux_path[l.second] = rl + ll;
    }
    if (r.second != -1) {
        aux[r.second] = rr;
        aux_path[r.second] = rr + lr;
    }
    return;
}

void dfs(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            dp[v] = dp[u] + 1;
            dp_path[v] = dp_path[u];
            dp[v] = max(dp[v], aux[v] + 1);
            dp_path[v] = max(dp_path[v], dp[u] + aux[v]);
            dp_path[v] = max(dp_path[v], aux_path[v]);
            ans = max(ans, (long long)subtree_path[v] * dp_path[v]);
            ans = max(ans, (long long)(subtree[v] - 1) * dp[v]);
            ans = max(ans, (long long)subtree_path[v] * (dp[v] - 1));
            dfs(v, u);
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
    dfs_subtree(0, 0);
    dfs(0, 0);
    cout << ans;
    return 0;
}
