//https://usaco.org/index.php?page=viewproblem2&cpid=696
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int INF = 1e9;

int a[N];
int ans[N];
int parent[N];
int sz[N];
vector<int> adj[N];
tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update> st[N];

int dsu_find(int p) {
    if (parent[p] == p) {
        return p;
    }
    parent[p] = dsu_find(parent[p]);
    return parent[p];
}

void dsu_merge(int a, int b) {
    if (st[a].size() > st[b].size()) {
        swap(a, b);
    }
    parent[a] = b;
    for (auto it = st[a].begin(); it != st[a].end(); ++it) {
        st[b].insert(*it);
    }
    return;
}

void dfs(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
    for (int v : adj[u]) {
        if (v != p) {
            int a = dsu_find(u), b = dsu_find(v);
            if (a != b) {
                dsu_merge(a, b);
            }
        }
    }
    ans[u] = st[dsu_find(u)].size() - st[dsu_find(u)].order_of_key(make_pair(a[u], INF));
    return;
}

int main() {
    //IOS;
    freopen("promote.in", "r", stdin);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i < n; i++) {
        int u;
        cin >> u;
        u--;
        adj[u].push_back(i);
        adj[i].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        sz[i] = 1;
        st[i].insert(make_pair(a[i], i));
    }
    dfs(0, 0);
    freopen("promote.out", "w", stdout);
    for (int i = 0; i < n; i++) {
        cout << ans[i] << endl;
    }


    return 0;
}
