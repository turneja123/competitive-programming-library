//https://cses.fi/problemset/task/1197/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 5005;
const long long INF = 1e18;

long long dist[N];
vector<tuple<int, int, int>> edges;
int parent[N];


int main() {
	IOS;
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        edges.push_back(make_tuple(u, v, wt));
	}
	for (int i = 0; i < n; i++) {
        dist[i] = 0;
	}
	for (int j = 1; j <= n; j++) {
        for (int i = 0; i < m; i++) {
            auto [u, v, wt] = edges[i];
            if (dist[u] == INF) {
                continue;
            }
            if (dist[v] > dist[u] + wt) {
                dist[v] = dist[u] + wt;
                parent[v] = u;
                if (j == n) {
                    cout << "YES" << endl;
                    for (int i = 0; i < n; i++) {
                        v = parent[v];
                    }
                    vector<int> ans{v};
                    int p = parent[v];
                    while (p != v) {
                        ans.push_back(p);
                        p = parent[p];
                    }
                    ans.push_back(p);
                    reverse(ans.begin(), ans.end());
                    for (int x : ans) {
                        cout << x + 1 << " ";
                    }
                    return 0;
                }
            }
        }
	}
	cout << "NO";
	return 0;
}
