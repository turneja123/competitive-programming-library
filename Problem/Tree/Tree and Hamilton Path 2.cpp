//https://atcoder.jp/contests/abc361/tasks/abc361_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 2e5 + 5;

vector<pair<int, int>> adj[N];

long long dist[N];

void dfs(int u, int p) {
    for (auto [v, wt] : adj[u]) {
        if (v != p) {
            dist[v] = dist[u] + wt;
            dfs(v, u);
        }
    }
    return;
}

int main() {
	IOS;
	int n;
	cin >> n;
	long long sum = 0;
	for (int i = 0; i < n - 1; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        adj[u].push_back(make_pair(v, wt));
        adj[v].push_back(make_pair(u, wt));
        sum += wt;
	}
	dfs(0, 0);
	long long mx = 0; int u = -1;
	for (int i = 0; i < n; i++) {
        if (dist[i] > mx) {
            mx = dist[i];
            u = i;
        }
        dist[i] = 0;
	}
	dfs(u, u);
	mx = 0;
	for (int i = 0; i < n; i++) {
        mx = max(mx, dist[i]);
	}
	cout << 2 * sum - mx;
	return 0;
}
