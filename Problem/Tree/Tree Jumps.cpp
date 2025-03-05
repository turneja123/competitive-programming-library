//https://codeforces.com/contest/2070/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const long long M = 998244353;

int depth[N];
long long dp[N];
long long dp_level[N];
int parent[N];

vector<int> adj[N];

void dfs(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            parent[v] = u;
            dfs(v, u);
        }
    }
}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 1; i < n; i++) {
            int p;
            cin >> p;
            p--;
            adj[i].push_back(p);
            adj[p].push_back(i);
        }
        dfs(0, 0);
        dp[0] = 1;
        dp_level[0] = 1;
        queue<int> q;
        for (int v : adj[0]) {
            q.push(v);
        }
        while (q.size()) {
            int u = q.front();
            q.pop();
            dp[u] = (dp[u] + dp_level[depth[u] - 1]) % M;
            dp_level[depth[u]] = (dp_level[depth[u]] + dp[u]) % M;
            for (int v : adj[u]) {
                if (v != parent[u]) {
                    dp[v] = (M - dp[u]) % M;
                    q.push(v);
                }
            }
        }
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            ans = (ans + dp[i]) % M;
        }
        cout << ans << endl;
        for (int i = 0; i < n; i++) {
            depth[i] = 0;
            dp[i] = 0;
            dp_level[i] = 0;
            adj[i].clear();
        }
    }
    return 0;
}
