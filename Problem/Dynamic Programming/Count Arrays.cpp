//https://atcoder.jp/contests/abc387/tasks/abc387_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2100;
const long long M = 998244353;

vector<int> adj[N];
vector<int> rev[N];
bool vis[N];
int parent[N];
long long dp[N][N];
long long suf[N][N];
long long pref[N][N];

stack<int> s;
set<int> scc[N];

vector<pair<int, int>> tr[N];

void fillStack(int v) {
    vis[v] = true;
    for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
        if (!vis[*it]) {
            fillStack(*it);
        }
    }
    s.push(v);
}

void dfs(int v, int j) {
    vis[v] = true;
    parent[v] = j;
    for (auto it = rev[v].begin(); it != rev[v].end(); ++it) {
        if (!vis[*it]) {
            dfs(*it, j);
        }
    }
}

void dfs_tree(int u, int k, int p) {
    int child = 0;
    vis[u] = true;
    for (auto [v, t] : tr[u]) {
        if (v != p) {
            dfs_tree(v, k, u);
            child++;
        }
    }
    if (child == 0) {
        for (int i = 1; i <= k; i++) {
            dp[u][i] = 1;
        }
        for (int i = 1; i <= k; i++) {
            pref[u][i] = (pref[u][i - 1] + dp[u][i]) % M;
        }
        for (int i = k; i >= 1; i--) {
            suf[u][i] = (suf[u][i + 1] + dp[u][i]) % M;
        }
    } else {
        for (int i = 1; i <= k; i++) {
            dp[u][i] = 1;
            for (auto [v, t] : tr[u]) {
                if (v != p) {
                    if (t == 1) {
                        dp[u][i] = dp[u][i] * suf[v][i] % M;
                    } else {
                        dp[u][i] = dp[u][i] * pref[v][i] % M;
                    }
                }
            }
        }
        for (int i = 1; i <= k; i++) {
            pref[u][i] = (pref[u][i - 1] + dp[u][i]) % M;
        }
        for (int i = k; i >= 1; i--) {
            suf[u][i] = (suf[u][i + 1] + dp[u][i]) % M;
        }
    }
    return;
}

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        a--;
        if (a != i) {
            adj[i].push_back(a);
            rev[a].push_back(i);
        }
    }
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            fillStack(i);
        }
    }
    for (int i = 0; i < n; i++) {
        vis[i] = 0;
    }
    int m = 0;
    while (!s.empty()) {
        int v = s.top();
        s.pop();
        if (vis[v] == false) {
            dfs(v, m++);
        }
    }
    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) {
            if (parent[u] != parent[v]) {
                auto it = scc[parent[u]].find(parent[v]);
                if (it == scc[parent[u]].end()) {
                    scc[parent[u]].insert(parent[v]);
                    tr[parent[u]].push_back(make_pair(parent[v], 1));
                    tr[parent[v]].push_back(make_pair(parent[u], 0));
                }
            }
        }
    }
    for (int i = 0; i < m; i++) {
        vis[i] = false;
    }
    long long ans = 1;
    for (int i = 0; i < m; i++) {
        if (!vis[i]) {
            dfs_tree(i, k, -1);
            long long cur = 0;
            for (int j = 1; j <= k; j++) {
                cur = (cur + dp[i][j]) % M;
            }
            ans = ans * cur % M;
        }
    }
    cout << ans;
    return 0;
}
