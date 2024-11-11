//https://cses.fi/problemset/task/1681
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long M = 1e9 + 7;

int deg[N];
int dp[N];
vector<int> adj[N];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        deg[v]++;
    }
    priority_queue<int, vector<int>, greater<int>> q;
    for (int i = 0; i < n; i++) {
        if (deg[i] == 0) {
            q.push(i);
        }
    }
    vector<int> sorted;
    while (q.size()) {
        int u = q.top();
        q.pop();
        sorted.push_back(u);
        for (int v : adj[u]) {
            deg[v]--;
            if (deg[v] == 0) {
                q.push(v);
            }
        }
    }
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        int u = sorted[i];
        for (int v : adj[u]) {
            dp[v] = (dp[v] + dp[u]) % M;
        }
    }
    cout << dp[n - 1];
    return 0;
}
