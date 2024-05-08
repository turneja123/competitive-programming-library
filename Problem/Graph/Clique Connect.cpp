//https://atcoder.jp/contests/abc352/tasks/abc352_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6;

int parent[N];
int sz[N];
bool vis[N];

list <int> adj[N];

int dsu_find(int a) {
    while (parent[a] != a) {
        a = parent[a];
    }
    return a;
}

void dsu_unite(int a, int b) {
    a = dsu_find(a);
    b = dsu_find(b);
    if (sz[b] > sz[a]) {
        swap(a, b);
    }
    sz[a] += sz[b];
    parent[b] = a;
}

void dfs(int v) {
    for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
        if (!vis[*it]) {
            vis[*it] = true;
            dfs(*it);
        }
    }
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    ll len = 0;
    vector<tuple<ll, int, int>> edge;
    for (int i = 0; i < m; i++) {
        int k, wt;
        cin >> k >> wt;
        vector<int> v(k, 0);
        for (int j = 0; j < k; j++) {
            cin >> v[j];
            v[j]--;
        }
        int a = v[0], b = v[k - 1];
        edge.push_back(make_tuple(wt, a, b));
        adj[a].push_back(b);
        adj[b].push_back(a);
        for (int j = 1; j < k; j++) {
            int a = v[j], b = v[j - 1];
            edge.push_back(make_tuple(wt, a, b));
            adj[a].push_back(b);
            adj[b].push_back(a);
        }
    }
    vis[0] = true;
    dfs(0);
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        sz[i] = 1;
        if (!vis[i]) {
            cout << -1;
            return 0;
        }
    }
    sort(edge.begin(), edge.end());
    for (int i = 0; i < edge.size(); i++) {
        ll wt = get<0>(edge[i]);
        int a = get<1>(edge[i]);
        int b = get<2>(edge[i]);
        int p1 = dsu_find(a);
        int p2 = dsu_find(b);
        if (p1 != p2) {
            dsu_unite(p1, p2);
            len += wt;
        }
    }
    cout << len;
    return 0;
}
