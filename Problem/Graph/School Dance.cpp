//https://cses.fi/problemset/task/1696
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;
const int INF = 1e9;

int capacity[N][N];
bool mat[N][N];
list<int> adj[N];

int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});
    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();
        for (auto it = adj[cur].begin(); it != adj[cur].end(); ++it) {
            if (parent[*it] == -1 && capacity[cur][*it]) {
                parent[*it] = cur;
                int new_flow = min(flow, capacity[cur][*it]);
                if (*it == t) {
                    return new_flow;
                }
                q.push({*it, new_flow});
            }
        }
    }
    return 0;
}

int main() {
    IOS;
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 0; i < k; i++) {
        int u, v;
        cin >> u >> v;
        capacity[u][v + n] = 1;
        mat[u][v + n] = true;
        adj[u].push_back(v + n);
        adj[v + n].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        capacity[0][i] = 1;
        adj[0].push_back(i);
        adj[i].push_back(0);
    }
    for (int i = n + 1; i <= n + m; i++) {
        capacity[i][n + m + 1] = 1;
        adj[i].push_back(n + m + 1);
        adj[n + m + 1].push_back(i);
    }
    vector<int> parent(n + m + 2);
    int flow = 0, new_flow;
    while (new_flow = bfs(0, n + m + 1, parent)) {
        flow += new_flow;
        int cur = n + m + 1;
        while (cur != 0) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }
    cout << flow << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = n + 1; j <= n + m; j++) {
            if (!capacity[i][j] && mat[i][j]) {
                cout << i << " " << j - n << endl;
            }
        }
    }
    return 0;
}
