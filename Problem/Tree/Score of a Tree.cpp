//https://codeforces.com/contest/1777/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long M = 1e9 + 7;

vector<int> adj[N];
long long pw[N];
int dist[N];
int ct[N];

void dfs(int u, int p) {
    bool leaf = true;
    for (int v : adj[u]) {
        if (v != p) {
            leaf = false;
            dfs(v, u);
            dist[u] = max(dist[u], dist[v] + 1);
        }
    }
    if (leaf) {
        dist[u] = 0;
    }
    ct[dist[u]]++;
    return;
}

int main() {
    IOS;
    pw[0] = 1;
    for (int i = 1; i < N; i++) {
        pw[i] = pw[i - 1] * 2 % M;
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(0, 0);
        long long ans = pw[n - 1] * n % M;
        for (int i = 0, m = n; i < n && m; i++) {
            m -= ct[i];
            ans = (ans + pw[n - 1] * m) % M;
        }
        cout << ans << endl;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            dist[i] = 0, ct[i] = 0;
        }
    }

    return 0;
}
