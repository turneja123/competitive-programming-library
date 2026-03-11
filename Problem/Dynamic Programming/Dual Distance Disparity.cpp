//https://www.codechef.com/problems/DUDIST
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 105;
const int M = 998244353;

vector<vector<vector<vector<vector<int>>>>> dp[N];
vector<int> adj[N];

void add(int k, int dx, int dy, int far_x, int far_y, int val, vector<vector<vector<vector<vector<int>>>>> &DP) {

    if (DP.size() <= k) {
        DP.resize(k + 1);
    }
    if (DP[k].size() <= dx) {
        DP[k].resize(dx + 1);
    }
    if (DP[k][dx].size() <= dy) {
        DP[k][dx].resize(dy + 1);
    }
    if (DP[k][dx][dy].size() <= far_x) {
        DP[k][dx][dy].resize(far_x + 1);
    }
    if (DP[k][dx][dy][far_x].size() <= far_y) {
        DP[k][dx][dy][far_x].resize(far_y + 1);
    }
    DP[k][dx][dy][far_x][far_y] += val;
    if (DP[k][dx][dy][far_x][far_y] >= M) {
        DP[k][dx][dy][far_x][far_y] -= M;
    }
}


void dfs(int u, int d, int p) {

    add(1, 1, 0, 1, 0, 1, dp[u]);
    add(0, 0, 1, 0, 1, 1, dp[u]);

    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, d, u);

            vector<vector<vector<vector<vector<int>>>>> dp_nx;

            for (int ku = 0; ku < dp[u].size(); ku++) {
                for (int dxu = 0; dxu < dp[u][ku].size(); dxu++) {
                    for (int dyu = 0; dyu < dp[u][ku][dxu].size(); dyu++) {
                        for (int farxu = 0; farxu < dp[u][ku][dxu][dyu].size(); farxu++) {
                            for (int faryu = 0; faryu < dp[u][ku][dxu][dyu][farxu].size(); faryu++) {

                                 for (int kv = 0; kv < dp[v].size(); kv++) {
                                    for (int dxv = 0; dxv < dp[v][kv].size(); dxv++) {
                                        for (int dyv = 0; dyv < dp[v][kv][dxv].size(); dyv++) {
                                            for (int farxv = 0; farxv < dp[v][kv][dxv][dyv].size(); farxv++) {
                                                for (int faryv = 0; faryv < dp[v][kv][dxv][dyv][farxv].size(); faryv++) {
                                                    int val = (ll)dp[u][ku][dxu][dyu][farxu][faryu] * dp[v][kv][dxv][dyv][farxv][faryv] % M;
                                                    int nxdxv = (dxv && dxv <= d ? dxv + 1 : 0);
                                                    int nxdyv = (dyv && dyv <= d ? dyv + 1 : 0);
                                                    int nxfarxv = (farxv ? farxv + 1 : 0), nxfaryv = (faryv ? faryv + 1 : 0);
                                                    int nxdx = (dxu == 0 ? nxdxv : (nxdxv == 0 ? dxu : min(dxu, nxdxv)));
                                                    int nxdy = (dyu == 0 ? nxdyv : (nxdyv == 0 ? dyu : min(dyu, nxdyv)));

                                                    if (nxfarxv && dyu && nxfarxv + dyu <= d + 2) {
                                                        nxfarxv = 0;
                                                    }
                                                    if (nxfaryv && dxu && nxfaryv + dxu <= d + 2) {
                                                        nxfaryv = 0;
                                                    }
                                                    int nxfarxu = farxu;
                                                    if (nxfarxu && nxdyv && nxfarxu + nxdyv <= d + 2) {
                                                        nxfarxu = 0;
                                                    }
                                                    int nxfaryu = faryu;
                                                    if (nxfaryu && nxdxv && nxfaryu + nxdxv <= d + 2) {
                                                        nxfaryu = 0;
                                                    }
                                                    if (max({nxfarxu, nxfarxv, nxfaryu, nxfaryv}) > d) {
                                                        continue;
                                                    }
                                                    add(ku + kv, nxdx, nxdy, max(nxfarxu, nxfarxv), max(nxfaryu, nxfaryv), val, dp_nx);
                                                }
                                            }
                                        }
                                    }
                                }

                            }
                        }
                    }
                }
            }
            dp[u].swap(dp_nx);

        }
    }

}


int main() {
    IOS;

    int t;
    cin >> t;
    while (t--) {
        int n, k, d;
        cin >> n >> k >> d;
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(0, d, 0);
        int ans = 0;
        if (dp[0].size() > k) {
            for (int dx = 0; dx < dp[0][k].size(); dx++) {
                for (int dy = 0; dy < dp[0][k][dx].size(); dy++) {
                    if (dp[0][k][dx][dy].size() && dp[0][k][dx][dy][0].size()) {
                        ans = ans + dp[0][k][dx][dy][0][0];
                        if (ans >= M) {
                            ans -= M;
                        }
                    }
                }
            }
        }
        cout << ans << endl;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            dp[i].clear();
        }


    }

    return 0;
}
