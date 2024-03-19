//https://cses.fi/problemset/task/1694/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5005;
const long long INF = 1e18;

long long capacity[N][N];
long long flow[N][N];
vector<long long> excess;
vector<long long> height;
vector<long long> next_son;
queue<int> excess_vertexes;
vector<int> adj[N];

int s, t, n, m;

void relabel(int u) {
	long long d = INF;
	for (int v : adj[u]) {
		if (capacity[u][v] > flow[u][v]) {
            d = min(d, height[v]);
        }
	}
	if (d < INF) {
        height[u] = d + 1;
    }
}

void push(int u, int v) {
	long long d = min(excess[u], capacity[u][v] - flow[u][v]);
	flow[u][v] += d;
	flow[v][u] -= d;
	excess[u] -= d;
	excess[v] += d;
	if (d && excess[v] == d) {
        excess_vertexes.push(v);
    }
}

void discharge(int u) {
	while (excess[u] > 0) {
		if (next_son[u] <= n) {
			int v = next_son[u];
			if (capacity[u][v] > flow[u][v] && height[u] > height[v]) {
				push(u, v);
			} else {
				next_son[u]++;
			}
		} else {
			relabel(u);
			next_son[u] = 1;
		}
	}
}
int main() {
    IOS;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; long long wt;
        cin >> u >> v >> wt;
        capacity[u][v] += wt;
    }
    for (int u = 1; u <= n; u++) {
        for (int v = u + 1; v <= n; v++) {
            if (u != v && (capacity[u][v] != 0 || capacity[v][u] != 0)) {
                adj[u].push_back(v);
                adj[v].push_back(u);
            }
        }
    }
    s = 1;
    t = n;
    excess.resize(n + 1);
	height.resize(n + 1);
	next_son.resize(n + 1);
	height[s] = n;
	excess[s] = INF;
    for (int i = 1; i <= n; i++) {
		if (i != s) {
            push(s, i);
		}
	}
	while (!excess_vertexes.empty()) {
		int node = excess_vertexes.front();
		excess_vertexes.pop();
		if (node != s && node != t) {
            discharge(node);
        }
	}
	long long max_flow = 0;
	for (int node = 1; node <= n; node++) {
        max_flow += flow[node][t];
    }
	cout << max_flow << endl;

    return 0;
}
