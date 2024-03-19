//https://atcoder.jp/contests/abc259/tasks/abc259_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

vector<pair<int, long long>> adj[N];
int d[N];
long long dp[N][2];

void dfs(int u, int p) {
    if (adj[u].size() == 1 && adj[u][0].first == p) {
        return;
    }
    priority_queue<pair<long long, int>> pq;
    map<int, bool> mark;
    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i].first;
        if (v != p) {
            dfs(v, u);
            long long wt = adj[u][i].second;
            if (d[v] != 0) {
                pq.push(make_pair(dp[v][0] - dp[v][1] + wt, v));
            }
            mark[v] = false;
        }
    }
    int j = 0, worst = 0;
    while (pq.size() > 0 && j < d[u]) {
        long long wt = pq.top().first;
        if (wt < 0) {
            break;
        }
        int v = pq.top().second;
        pq.pop();
        if (j == d[u] - 1) {
            worst = v;
        }
        mark[v] = true;
        j++;
    }
    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i].first;
        if (v == p) {
            continue;
        }
        if (mark[v]) {
            long long wt = adj[u][i].second;
            dp[u][1] += dp[v][0] + wt;
            if (v != worst) {
                dp[u][0] += dp[v][0] + wt;
            } else {
                dp[u][0] += dp[v][1];
            }
        } else {
            dp[u][1] += dp[v][1];
            dp[u][0] += dp[v][1];
        }
    }
    if (j < d[u]) {
        dp[u][0] = dp[u][1];
    }
    return;
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> d[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v; long long wt;
        cin >> u >> v >> wt;
        u--,v--;
        adj[u].push_back(make_pair(v, wt));
        adj[v].push_back(make_pair(u, wt));
    }
    dfs(0, 0);
    cout << dp[0][1];
    return 0;
}
