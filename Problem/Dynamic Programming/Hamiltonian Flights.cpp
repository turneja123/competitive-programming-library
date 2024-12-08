//https://cses.fi/problemset/task/1690/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 21;
const int M = 1e9 + 7;

vector<int> adj[N];

int dp[N][1 << N];

int main() {
	IOS;
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
	}
	dp[0][1] = 1;
	for (int i = 1; i < 1 << n; i += 2) {
        int j = i;
        while (j > 0) {
            int u = __builtin_ctz(j);
            j ^= (1 << u);
            for (int v : adj[u]) {
                int nx = i | (1 << v);
                if (nx != i) {
                    dp[v][nx] = (dp[v][nx] + dp[u][i]) % M;
                }
            }
        }
	}
	cout << dp[n - 1][(1 << n) - 1];
	return 0;
}
