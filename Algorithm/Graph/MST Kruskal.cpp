#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 200005;

int parent[N];
int sz[N];
bool vis[N];

vector<int> adj[N];
tuple<long long, int, int> edge[N];

int dsu_find(int a) {
    if (parent[a] == a) {
        return a;
    }
    return parent[a] = dsu_find(parent[a]);
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
    long long ans = 0;
    for (int i = 0; i < m; i++) {
        int a, b, wt;
        cin >> a >> b >> wt;
        a--, b--;
        edge[i] = make_tuple(wt, a, b);
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vis[0] = true;
    dfs(0);
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        sz[i] = 1;
        if (!vis[i]) {
            cout << "IMPOSSIBLE";
            return 0;
        }
    }
    sort(edge, edge + m);
    for (int i = 0; i < m; i++) {
        long long wt = get<0>(edge[i]);
        int a = get<1>(edge[i]);
        int b = get<2>(edge[i]);
        int p1 = dsu_find(a);
        int p2 = dsu_find(b);
        if (p1 != p2) {
            dsu_unite(p1, p2);
            ans += wt;
        }
    }
    cout << ans;
    return 0;
}
