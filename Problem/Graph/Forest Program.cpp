//https://codeforces.com/gym/102361/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 1e6 + 5;
const long long M = 998244353;

vector<int> adj[N];

int depth[N];
bool vis[N];
int parent[N];

vector<vector<int>> cycles;

long long pw[N];
long long dp[N];

void dfs(int u, int p) {
    vis[u] = true;
    parent[u] = p;
    for (int v : adj[u]) {
        if (!vis[v]) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
        } else if (depth[u] - depth[v] > 1) {
            vector<int> cyc;
            int x = u;
            while (x != v) {
                cyc.push_back(x);
                x = parent[x];
            }
            cyc.push_back(v);
            cycles.push_back(cyc);
        }
    }
    return;
}

int main() {
	IOS;
	pw[0] = 1;
	for (int i = 1; i < N; i++) {
        pw[i] = pw[i - 1] * 2 % M;
	}
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    long long ans = pw[m];
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(i, i);
        }
    }
    if (cycles.size() == 0) {
        cout << ans;
        return 0;
    }
    dp[0] = pw[cycles[0].size()] - 1;
    m -= cycles[0].size();
    for (int i = 1; i < cycles.size(); i++) {
        dp[i] = dp[i - 1] * (pw[cycles[i].size()] - 1) % M;
        m -= cycles[i].size();
    }
    cout << dp[cycles.size() - 1] * pw[m] % M;

	return 0;
}
