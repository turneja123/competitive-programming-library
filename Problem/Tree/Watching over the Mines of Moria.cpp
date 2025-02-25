//https://www.spoj.com/problems/MORIA3/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 2e6 + 5;
const int INF = 1e9;

vector<int> adj[N];
int dp[N][3];


void dfs(int u, int p) {
    bool leaf = true;
    dp[u][0] = 0;
    dp[u][1] = 0;
    dp[u][2] = 1;
    bool has = false;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            leaf = false;
            if (dp[v][1] == INF) {
                has = true;
            }
        }
    }
    if (has) {
        dp[u][0] = INF;
    }
    int diff = N, take = -1;
    for (int v : adj[u]) {
        if (v != p) {
            if (!has) {
                dp[u][0] += dp[v][1];
            }
            if (dp[v][2] - dp[v][1] < diff) {
                diff = dp[v][2] - dp[v][1];
                take = v;
            }
            dp[u][2] += min({dp[v][0], dp[v][1], dp[v][2]});
        }
    }
    if (leaf) {
        dp[u][0] = 0;
        dp[u][1] = INF;
        dp[u][2] = 1;
    } else {
        for (int v : adj[u]) {
            if (v != p) {
                if (take == v) {
                    dp[u][1] += dp[v][2];
                } else {
                    dp[u][1] += min(dp[v][1], dp[v][2]);
                }
            }
        }
    }
    return;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        n++;
        for (int i = 1; i < n; i++) {
            int p;
            cin >> p;
            adj[i].push_back(p);
            adj[p].push_back(i);
        }
        dfs(0, 0);
        cout << min(dp[0][0], dp[0][1]) << endl;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
    }
    return 0;
}
