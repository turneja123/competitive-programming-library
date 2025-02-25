//https://usaco.org/index.php?page=viewproblem&cpid=1485
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long INF = 1e18;

int c[N];
int go[N];

vector<int> rev[N];
vector<int> cycle;
vector<vector<int>> cycles;

bool on_cycle[N];
int color[N];
int parent[N];

long long dp[N][2];

void dfs_root(int u) {
    dp[u][0] = 0;
    dp[u][1] = c[u];
    for (int v : rev[u]) {
        if (on_cycle[v]) {
            continue;
        }
        dfs_root(v);
        dp[u][0] += dp[v][1];
        dp[u][1] += min(dp[v][0], dp[v][1]);
    }
    return;
}





void dfs(int u, int p) {
    color[u] = 1;
    parent[u] = p;
    int v = go[u];
    if (v == u) {
        color[u] = 2;
        return;
    }

    if (color[v] == 0) {
        dfs(v, u);
    } else if (color[v] == 1) {
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
    color[u] = 2;
    return;

}

int main() {
    IOS;
    int n;
    cin >> n;
    vector<int> root;
    for (int i = 0; i < n; i++) {
        cin >> go[i];
        go[i]--;
        if (go[i] == i) {
            root.push_back(i);
        } else {
            rev[go[i]].push_back(i);
        }
    }
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        if (!color[i]) {
            dfs(i, i);
        }
    }
    long long ans = 0;
    for (int r : root) {
        c[r] = 0;
        dfs_root(r);
        ans += dp[r][1];
    }
    for (vector<int> cycle : cycles) {
        for (int x : cycle) {
            dfs_root(x);
        }
        long long best = INF;
        long long cur[2];
        cur[0] = dp[cycle[0]][1] + dp[cycle[1]][0], cur[1] = dp[cycle[0]][1] + dp[cycle[1]][1];

        for (int i = 2; i < cycle.size(); i++) {
            long long nw[2];
            nw[0] = cur[1] + dp[cycle[i]][0];
            nw[1] = min(cur[0], cur[1]) + dp[cycle[i]][1];
            cur[0] = nw[0];
            cur[1] = nw[1];
        }
        best = min(cur[0], cur[1]);

        cur[0] = INF, cur[1] = dp[cycle[0]][0] + dp[cycle[1]][1];
        for (int i = 2; i < cycle.size(); i++) {
            long long nw[2];
            nw[0] = cur[1] + dp[cycle[i]][0];
            nw[1] = min(cur[0], cur[1]) + dp[cycle[i]][1];
            cur[0] = nw[0];
            cur[1] = nw[1];
        }
        best = min(best, cur[1]);
        ans += best;
    }

    cout << ans;
    return 0;
}
