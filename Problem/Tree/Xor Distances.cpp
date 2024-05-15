//https://atcoder.jp/contests/abc201/tasks/abc201_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long M = 1e9 + 7;

vector<pair<int, long long>> adj[N];
long long ct[N][64][2];

long long ans = 0;

void dfs(int u, int p) {
    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i].first; long long wt = adj[u][i].second;
        if (v != p) {
            dfs(v, u);
            for (long long j = 0; j < 64; j++) {
                long long bit = 1ll << j;
                long long c = wt & bit;
                bit %= M;
                if (c == 0) {
                    ans = (ans + ct[v][j][1] * bit) % M;
                    ans = (ans + ((ct[v][j][1] * ct[u][j][0]) % M) * bit) % M;
                    ans = (ans + ((ct[v][j][0] * ct[u][j][1]) % M) * bit) % M;
                    ct[u][j][0] += ct[v][j][0];
                    ct[u][j][1] += ct[v][j][1];
                } else {
                    ans = (ans + ct[v][j][0] * bit) % M;
                    ans = (ans + ((ct[v][j][0] * ct[u][j][0]) % M) * bit) % M;
                    ans = (ans + ((ct[v][j][1] * ct[u][j][1]) % M) * bit) % M;
                    ct[u][j][0] += ct[v][j][1];
                    ct[u][j][1] += ct[v][j][0];
                }
            }
        }
    }
    for (int j = 0; j < 64; j++) {
        ct[u][j][0]++;
    }
}

int main() {
	IOS;
	int n;
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
        int u, v; long long wt;
        cin >> u >> v >> wt;
        u--, v--;
        adj[u].push_back(make_pair(v, wt));
        adj[v].push_back(make_pair(u, wt));
	}
    dfs(0, -1);
    cout << ans;

	return 0;
}
