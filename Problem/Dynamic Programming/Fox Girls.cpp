//https://dmoj.ca/problem/halloween14p4
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long INF = 2e14;

int c[N];

vector<pair<int, int>> adj[N];
vector<int> cycle;
vector<vector<int>> cycles;

bool on_cycle[N];
int color[N];
int parent[N];

long long dp[N][3];

void dfs_root(int u, int p) {
    dp[u][0] = 0;
    dp[u][1] = c[u];
    dp[u][2] = INF;
    long long mn = INF;
    int best = -1;

    for (auto [v, _] : adj[u]) {
        if (on_cycle[v] || v == p) {
            continue;
        }
        dfs_root(v, u);
        dp[u][0] += dp[v][2];
        dp[u][1] += min({dp[v][0], dp[v][1], dp[v][2]});
        if (dp[v][1] - dp[v][2] < mn) {
            mn = dp[v][1] - dp[v][2];
            best = v;
        }
    }
    if (best == -1) {
        return;
    }
    dp[u][2] = 0;
    for (auto [v, _] : adj[u]) {
        if (on_cycle[v] || v == p) {
            continue;
        }
        if (v == best) {
            dp[u][2] += dp[v][1];
        } else {
            dp[u][2] += min(dp[v][1], dp[v][2]);
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
        cin >> c[i];
    }
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

    long long ans = 0;
    for (vector<int> cycle : cycles) {
        for (int x : cycle) {
            dfs_root(x, x);
        }
        if (cycle.size() == 2) {
            int u = cycle[0], v = cycle[1];
            long long best = min({dp[u][2] + dp[v][2], dp[u][1] + min(dp[v][0], dp[v][2]), min(dp[u][0], dp[u][2]) + dp[v][1], dp[u][1] + dp[v][1]});
            ans += best;
            continue;
        }
        if (cycle.size() == 3) {
            int u = cycle[0], v = cycle[1], z = cycle[2];
            long long best = INF;
            for (int i = 0; i < 3; i++) {
                for (int j = 0; j < 3; j++) {
                    for (int k = 0; k < 3; k++) {
                        vector<int> f(3, 0);
                        if (i == 1) {
                            f[0] = 1, f[1] = 1, f[2] = 1;
                        } else if (i == 2) {
                            f[0] = 1;
                        }

                        if (j == 1) {
                            f[0] = 1, f[1] = 1, f[2] = 1;
                        } else if (j == 2) {
                            f[1] = 1;
                        }

                        if (k == 1) {
                            f[0] = 1, f[1] = 1, f[2] = 1;
                        } else if (k == 2) {
                            f[2] = 1;
                        }

                        if (f[0] && f[1] && f[2]) {
                            best = min(best, dp[u][i] + dp[v][j] + dp[z][k]);
                        }
                    }
                }
            }
            ans += best;
            continue;
        }

        long long best = INF;
        long long cur[3];
        cur[0] = INF, cur[1] = dp[cycle[0]][1], cur[2] = INF;
        for (int i = 1; i < cycle.size(); i++) {
            long long nw[3];
            nw[0] = cur[2] + dp[cycle[i]][0];
            nw[1] = min({cur[0], cur[1], cur[2]}) + dp[cycle[i]][1];
            nw[2] = min(min({cur[1], cur[2]}) + dp[cycle[i]][2], cur[1] + min(dp[cycle[i]][0], dp[cycle[i]][2]));
            cur[0] = nw[0];
            cur[1] = nw[1];
            cur[2] = nw[2];
        }
        best = min({cur[0], cur[1], cur[2]});

        for (int f = 0; f < 3; f++) {
            cur[0] = INF, cur[1] = INF, cur[2] = INF;
            cur[f] = dp[cycle[0]][2] + dp[cycle[1]][f];
            for (int i = 2; i < cycle.size(); i++) {
                long long nw[3];
                nw[0] = cur[2] + dp[cycle[i]][0];
                nw[1] = min({cur[0], cur[1], cur[2]}) + dp[cycle[i]][1];
                nw[2] = min(min({cur[1], cur[2]}) + dp[cycle[i]][2], cur[1] + min(dp[cycle[i]][0], dp[cycle[i]][2]));
                cur[0] = nw[0];
                cur[1] = nw[1];
                cur[2] = nw[2];
            }
            best = min({best, cur[1], cur[2]});
        }

        for (int f = 0; f < 3; f++) {
            cur[0] = INF, cur[1] = INF, cur[2] = INF;
            cur[f] = dp[cycle[0]][0] + dp[cycle[1]][f];
            for (int i = 2; i < cycle.size(); i++) {
                long long nw[3];
                nw[0] = cur[2] + dp[cycle[i]][0];
                nw[1] = min({cur[0], cur[1], cur[2]}) + dp[cycle[i]][1];
                nw[2] = min(min({cur[1], cur[2]}) + dp[cycle[i]][2], cur[1] + min(dp[cycle[i]][0], dp[cycle[i]][2]));
                cur[0] = nw[0];
                cur[1] = nw[1];
                cur[2] = nw[2];
            }
            if (f == 1) {
                best = min({best, cur[1], cur[2]});
            } else {
                best = min(best, cur[1]);
            }
        }

        ans += best;
    }

    cout << ans;
    return 0;
}
