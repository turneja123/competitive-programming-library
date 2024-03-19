//https://www.codechef.com/problems/NTA?tab=statement
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const long long INF = 1e18;

long long a[N];
long long ans[N];
long long best[N];
int sz[N];
int parent[N];
vector<int> adj[N];
tree<pair<long long, int>, null_type, less<pair<long long, int>>, rb_tree_tag, tree_order_statistics_node_update> st[N];

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
        long long val = it->first;
        int pos = st[b].order_of_key(*it);
        for (int dx = -1; dx <= 1; dx++) {
            if (pos + dx >= 0 && pos + dx < st[b].size()) {
                long long k = (st[b].find_by_order(pos + dx))->first;
                best[b] = min(best[b], val ^ k);
            }
        }
        st[b].insert(*it);
    }
    return;
}

void dfs(int u, int p) {
    vector<int> child;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            child.push_back(v);
        }
    }
    for (int v : child) {
        int a = dsu_find(u), b = dsu_find(v);
        if (a != b) {
            dsu_merge(a, b);
        }
    }
    ans[u] = best[dsu_find(u)];
    return;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            sz[i] = 1;
            st[i].insert(make_pair(a[i], i));
            best[i] = INF;
            ans[i] = INF;
        }
        dfs(0, -1);
        for (int i = 0; i < n; i++) {
            if (ans[i] != INF) {
                cout << ans[i] << " ";
            } else {
                cout << -1 << " ";
            }
        }
        cout << endl;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            st[i].clear();
        }
    }

    return 0;
}
