//https://codeforces.com/contest/2183/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5005;
const ll M = 998244353;

vector<int> adj[N];
vector<int> c[N];
vector<int> nodes;

ll dp[N][N];
string s;

void dfs(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            c[u].push_back(v);
            dfs(v, u);
        }
    }
    for (int v : nodes) {
        dp[u][v] = s[u] == s[v];
        if (s[u] != s[v]) {
            for (int x : c[u]) {
                for (int y : c[v]) {
                    dp[u][v] = (dp[u][v] - dp[x][y] + M) % M;
                }
            }
        }
        for (int x : c[u]) {
            dp[u][v] = (dp[u][v] + dp[x][v]) % M;
        }
        for (int x : c[v]) {
            dp[u][v] = (dp[u][v] + dp[u][x]) % M;
        }
        dp[v][u] = dp[u][v];
    }

    dp[u][u] = 1;
    for (int x : c[u]) {
        dp[u][u] = (dp[u][u] + dp[u][x] + dp[x][u]) % M;
    }


    nodes.push_back(u);
}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cin >> s;
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(0, 0);
        nodes.clear();
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            c[i].clear();
            cout << dp[i][i] << " ";
            for (int j = 0; j < n; j++) {
                dp[i][j] = 0;
            }
        }
        cout << endl;
    }
    return 0;
}
