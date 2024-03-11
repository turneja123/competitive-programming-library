//solution for https://cses.fi/problemset/task/2076/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

list<int> adj[N];
vector<pair<int, int>> bridges;
bool visited[N];
int tin[N];
int low[N];

int timer = 0;

void dfs(int v, int p = -1) {
    visited[v] = true;
    tin[v] = low[v] = timer++;
    for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
        if (*it == p) {
            continue;
        }
        if (visited[*it]) {
            low[v] = min(low[v], tin[*it]);
        } else {
            dfs(*it, v);
            low[v] = min(low[v], low[*it]);
            if (low[*it] > tin[v]) {
                bridges.push_back({v, *it});
            }
        }
    }
}


int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }
    cout << bridges.size() << endl;
    for (int i = 0; i < bridges.size(); i++) {
        cout << bridges[i].first + 1 << " " << bridges[i].second + 1 << endl;
    }
    return 0;
}
