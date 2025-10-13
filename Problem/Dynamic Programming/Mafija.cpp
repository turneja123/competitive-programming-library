//https://dmoj.ca/problem/coci14c1p4
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const int INF = 1e9;

vector<pair<int, int>> adj[N];
vector<int> cycle;
vector<vector<int>> cycles;

bool on_cycle[N];
int color[N];
int parent[N];

int dp[N][2];

void dfs_root(int u, int p) {
    dp[u][0] = 0, dp[u][1] = 1;
    for (auto [v, _] : adj[u]) {
        if (v != p && !on_cycle[v]) {
            dfs_root(v, u);
            dp[u][0] += max(dp[v][0], dp[v][1]);
            dp[u][1] += dp[v][0];
        }
    }

    return;
}



void dfs(int u, int p, int e) {
    color[u] = 1;
    parent[u] = p;

    for (auto [v, ed] : adj[u]) {
        if (color[v] == 0) {
            dfs(v, u, ed);
        } else if (color[v] == 1 && ed != e) {
            cycle.push_back(v);
            on_cycle[v] = true;
            int x = u;
            while (x != v) {
                cycle.push_back(x);
                on_cycle[x] = true;
                x = parent[x];
            }
            cycles.push_back(cycle);
            cycle.clear();
        }
    }
    color[u] = 2;
    return;

}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int p;
        cin >> p;
        p--;
        adj[i].push_back(make_pair(p, i));
        adj[p].push_back(make_pair(i, i));
    }
    for (int i = 0; i < n; i++) {
        if (!color[i]) {
            dfs(i, i, -1);
        }
    }

    int ans = 0;
    for (vector<int> cycle : cycles) {
        for (int x : cycle) {
            dfs_root(x, x);
        }
        int best = -INF;
        int cur[2];
        cur[0] = -INF, cur[1] = dp[cycle[0]][1];
        for (int i = 1; i < cycle.size(); i++) {
            int v = cycle[i];
            int nx[2];
            nx[0] = max(cur[0], cur[1]) + dp[v][0];
            nx[1] = cur[0] + dp[v][1];
            cur[0] = nx[0];
            cur[1] = nx[1];
        }
        best = cur[0];

        cur[0] = dp[cycle[0]][0], cur[1] = -INF;
        for (int i = 1; i < cycle.size(); i++) {
            int v = cycle[i];
            int nx[2];
            nx[0] = max(cur[0], cur[1]) + dp[v][0];
            nx[1] = cur[0] + dp[v][1];
            cur[0] = nx[0];
            cur[1] = nx[1];
        }
        best = max({best, cur[0], cur[1]});
        ans += best;
    }

    cout << ans;
    return 0;
}
