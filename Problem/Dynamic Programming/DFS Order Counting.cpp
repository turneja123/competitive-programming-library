//https://repovive.com/contests/5/problems/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5005;
const ll M = 998244353;

ll pw[N];
ll dp[N][N];
vector<int> adj[N];

int main() {
    IOS;
    pw[0] = 1;
    for (int i = 1; i < N; i++) {
        pw[i] = pw[i - 1] * 2 % M;
    }
    int t;
    cin >> t;
    while  (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        for (int i = n - 1; i >= 0; i--) {
            vector<int> pref(n, 0);
            sort(adj[i].begin(), adj[i].end());
            for (int v : adj[i]) {
                pref[v] = 1;
            }
            for (int i = 1; i < n; i++) {
                pref[i] += pref[i - 1];
            }
            dp[i][i] = 1;
            for (int v : adj[i]) {
                if (v > i) {
                    for (int j = v; j < n; j++) {
                        dp[i][j] = (dp[i][j] + dp[i][v - 1] * dp[v][j] % M * pw[pref[j] - pref[v]]) % M;
                    }
                }
            }
        }
        cout << dp[0][n - 1] << endl;;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            for (int j = 0; j < n; j++) {
                dp[i][j] = 0;
            }
        }
    }
    return 0;
}
