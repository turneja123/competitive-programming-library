//https://cses.fi/problemset/task/1694/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;
const long long INF = 1e15;

long long capacity[N][N];
list<int> adj[N];

long long bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, long long>> q;
    q.push({s, INF});
    while (!q.empty()) {
        int cur = q.front().first;
        long long flow = q.front().second;
        q.pop();
        for (auto it = adj[cur].begin(); it != adj[cur].end(); ++it) {
            if (parent[*it] == -1 && capacity[cur][*it]) {
                parent[*it] = cur;
                long long new_flow = min(flow, capacity[cur][*it]);
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
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; long long wt;
        cin >> u >> v >> wt;
        capacity[u][v] += wt;
        if (find(adj[u].begin(), adj[u].end(), v) == adj[u].end()) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }
    capacity[0][1] = INF;
    adj[0].push_back(1);
    adj[1].push_back(0);
    capacity[n][n + 1] = INF;
    adj[n].push_back(n + 1);
    adj[n + 1].push_back(n);

    vector<int> parent(n + 2);
    long long flow = 0, new_flow;
    while (new_flow = bfs(0, n + 1, parent)) {
        flow += new_flow;
        int cur = n + 1;
        while (cur != 0) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }
    cout << flow << endl;
    return 0;
}
