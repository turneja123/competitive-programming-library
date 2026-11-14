//https://tlx.toki.id/contests/troc-44/problems/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;


int id[N];
vector<int> adj[4 * N];
vector<int> rev[4 * N];
int L[4 * N];
int R[4 * N];

int idx = 0;

void upd(int l, int r, int lq, int rq, int node, int v) {
    if (l > rq || r < lq) {
        return;
    }
    if (lq <= l && rq >= r) {
        adj[v].push_back(node);
        rev[node].push_back(v);
        return;
    }

    int mid = (l + r) / 2;
    upd(l, mid, lq, rq, L[node], v);
    upd(mid + 1, r, lq, rq, R[node], v);
}

void build(int l, int r, int node) {
    if (l == r) {
        adj[node].push_back(l);
        rev[l].push_back(node);
        return;
    }

    int mid = (l + r) / 2;
    L[node] = idx;
    build(l, mid, idx++);
    R[node] = idx;
    build(mid + 1, r, idx++);
    adj[node].push_back(L[node]);
    adj[node].push_back(R[node]);
    rev[L[node]].push_back(node);
    rev[R[node]].push_back(node);

}

int ans[N];
int vis[4 * N];
int parent[4 * N];
int sz[4 * N];
stack<int> s;

void fillStack(int u) {
    vis[u] = true;
    for (int v : adj[u]) {
        if (!vis[v]) {
            fillStack(v);
        }
    }
    s.push(u);
}

void dfs(int u, int j) {
    vis[u] = true;
    parent[u] = j;
    for (int v : rev[u]) {
        if (!vis[v]) {
            dfs(v, j);
        }
    }
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;

    vector<tuple<int, int, int, int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v, l, r;
        cin >> u >> v >> l >> r;
        u--, v--, l--, r--;
        edges.push_back({u, i, l, r, v});
    }


    sort(edges.begin(), edges.end());
    idx = m + 1;
    build(0, m - 1, m);
    for (int i = 0; i < m; i++) {
        auto [u, ind, l, r, v] = edges[i];
        int L = lower_bound(edges.begin(), edges.end(), make_tuple(v, l, -1, -1, -1)) - edges.begin();
        int R = lower_bound(edges.begin(), edges.end(), make_tuple(v, r + 1, -1, -1, -1)) - edges.begin() - 1;
        if (L <= R) {
            upd(0, m - 1, L, R, m, i);
        }
    }

    for (int i = 0; i < 4 * m; i++) {
        if (!vis[i]) {
            fillStack(i);
        }
    }
    for (int i = 0; i < 4 * m; i++) {
        vis[i] = 0;
    }
    int j = 0;
    while (!s.empty()) {
        int v = s.top();
        s.pop();
        if (vis[v] == false) {
            dfs(v, j++);
        }
    }

    for (int i = 0; i < m; i++) {
        sz[parent[i]]++;
    }
    for (int i = 0; i < m; i++) {
        ans[get<1>(edges[i])] = sz[parent[i]] > 1;
    }
    for (int i = 0; i < m; i++) {
        cout << ans[i] << " ";
    }

    return 0;
}
