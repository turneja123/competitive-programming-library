//https://cses.fi/problemset/task/1680/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int nx[N];
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
    dp[n - 1] = 1;
    for (int i = n - 1; i >= 0; i--) {
        int u = sorted[i];
        for (int v : adj[u]) {
            if (dp[u] < dp[v] + 1 && dp[v] != 0) {
                dp[u] = dp[v] + 1;
                nx[u] = v;
            }
        }
    }
    if (dp[0] == 0) {
        cout << "IMPOSSIBLE";
        return 0;
    } else {
        cout << dp[0] << endl;
        int u = 0;
        while (u != n - 1) {
            cout << u + 1 << " ";
            u = nx[u];
        }
        cout << n;
    }
    return 0;
}
