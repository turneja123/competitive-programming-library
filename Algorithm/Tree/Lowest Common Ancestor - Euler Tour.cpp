//https://judge.yosupo.jp/problem/lca
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

vector<int> adj[N];
pair<int, int> tour[2 * N];
vector<int> trav(3, 0);

bool visited[N] = { };
int segtree[8 * N];
int depth[N];
int pos[N];
int timer = 0, mn, ind;

void dfs(int u, int p) {
    pos[u] = timer;
    tour[timer++] = make_pair(u, depth[u]);
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
            tour[timer++] = make_pair(u, depth[u]);
        }
    }
}

void traverse(int l, int r, int node) {
    if (l == r) {
        ind = l;
        return;
    }
    int mid = (l + r) / 2;
    if (segtree[2 * node + 1] <= segtree[2 * node + 2]) {
        traverse(l, mid, 2 * node + 1);
    } else {
        traverse(mid + 1, r, 2 * node + 2);
    }
    return;
}

void rmq(int l, int r, int lq, int rq, int node) {
    if (lq <= l && rq >= r) {
        if (segtree[node] < mn) {
            mn = segtree[node];
            trav[0] = l, trav[1] = r, trav[2] = node;
        }
        return;
    }

    if (l > rq || r < lq) {
        return;
    }

    int mid = (l + r) / 2;
    rmq(l, mid, lq, rq, 2 * node + 1);
    rmq(mid + 1, r, lq, rq, 2 * node + 2);
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = tour[l].second;
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = min(segtree[2 * node + 1], segtree[2 * node + 2]);
}


int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 1; i < n; i++) {
        int v;
        cin >> v;
        adj[i].push_back(v);
        adj[v].push_back(i);
    }
    depth[0] = 1;
    dfs(0, -1);
    int m = 2 * n - 1;
    build(0, m - 1, 0);
    for (int i = 0; i < q; i++) {
        ind = -1, mn = 4 * N;
        int a, b;
        cin >> a >> b;
        int l = pos[a];
        int r = pos[b];
        if (l > r) {
            swap(l, r);
        }
        rmq(0, m - 1, l, r, 0);
        traverse(trav[0], trav[1], trav[2]);
        cout << tour[ind].first << endl;
    }
    return 0;

}
