//https://atcoder.jp/contests/dp/tasks/dp_p
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long M = 1e9 + 7;

long long dp[N][2];
vector<int> adj[N];

void dfs(int u, int p) {
    if ((adj[u].size() == 1 && adj[u][0] == p) || adj[u].size() == 0) {
        dp[u][0] = 1;
        dp[u][1] = 1;
        return;
    }
    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        if (v != p) {
            dfs(v, u);
            if (dp[u][0] < 0) {
                dp[u][0] = (dp[v][1] + dp[v][0]) % M;
                dp[u][1] = dp[v][0];
            } else {
                dp[u][0] = (dp[u][0] * (dp[v][0] + dp[v][1])) % M;
                dp[u][1] = (dp[u][1] * dp[v][0]) % M;
            }
        }
    }
    return;
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        dp[i][0] = -M;
        dp[i][1] = -M;
    }
    dfs(0, -1);
    cout << (dp[0][0] + dp[0][1]) % M << endl;


    return 0;
}
