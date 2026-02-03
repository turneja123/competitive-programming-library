//https://codeforces.com/contest/2187/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int MAX = 6e6;

struct Node {
    ll sum;
    int val;
    int left;
    int right;
    Node() : sum(0), val(0), left(-1), right(-1) {}
};

Node nodes[MAX];
int idx = 0;
int parent[N];
vector<int> items[N];
vector<int> adj[N];
int up[N];
int depth[N];

ll query(int node, int l, int r, int lq, int rq, int f) {
    if (r < lq || l > rq || lq > rq) {
        return 0;
    }
    if (lq <= l && rq >= r) {
        return (f == 0 ? nodes[node].val : nodes[node].sum);
    }
    int mid = (l + r) / 2; ll ans = 0;
    if (nodes[node].left != -1) {
        ans += query(nodes[node].left, l, mid, lq, rq, f);
    }
    if (nodes[node].right != -1) {
        ans += query(nodes[node].right, mid + 1, r, lq, rq, f);
    }
    return ans;

}

void update(int node, int l, int r, int ind) {
    if (l == r) {
        nodes[node].val += 1;
        nodes[node].sum += l;
        return;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        if (nodes[node].left == -1) {
            nodes[node].left = idx;
            nodes[idx++] = Node();
        }
        update(nodes[node].left, l, mid, ind);
    } else {
        if (nodes[node].right == -1) {
            nodes[node].right = idx;
            nodes[idx++] = Node();
        }
        update(nodes[node].right, mid + 1, r, ind);
    }
    nodes[node].val = 0;
    nodes[node].sum = 0;
    if (nodes[node].left != -1) {
        nodes[node].val += nodes[nodes[node].left].val;
        nodes[node].sum += nodes[nodes[node].left].sum;
    }
    if (nodes[node].right != -1) {
        nodes[node].val += nodes[nodes[node].right].val;
        nodes[node].sum += nodes[nodes[node].right].sum;
    }
}

int dsu_find(int p) {
    if (parent[p] == p) {
        return p;
    }
    parent[p] = dsu_find(parent[p]);
    return parent[p];
}

ll ans = 0;

void dsu_unite(int a, int b, int u, int n) {
    if (items[a].size() > items[b].size()) {
        swap(a, b);
    }
    for (int d : items[a]) {
        ans += query(b, 0, n - 1, d, n - 1, 0) * (d - u);
        ans += query(b, 0, n - 1, 0, d, 1) - query(b, 0, n - 1, 0, d, 0) * u;
    }
    for (int d : items[a]) {
        items[b].push_back(d);
        update(b, 0, n - 1, d);
    }
    items[a].clear();
    parent[a] = b;
}



void dfs(int u, int p, int n) {
    update(u, 0, n - 1, depth[u]);
    items[u].push_back(depth[u]);
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u, n);
            int a = dsu_find(u), b = dsu_find(v);
            dsu_unite(a, b, depth[u], n);
        }
    }

}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        idx = 0;
        ans = 0;
        for (int i = 0; i < n; i++) {
            nodes[idx++] = Node();
            parent[i] = i;
        }
        for (int i = 0; i < n - 1; i++) {
            up[i] = i + 1;
        }
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            up[u] = max(up[u], v);
        }
        for (int i = 0; i < n - 1; i++) {
            adj[i].push_back(up[i]);
            adj[up[i]].push_back(i);
        }
        depth[n - 1] = 0;
        dfs(n - 1, n - 1, n);
        cout << ans << endl;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            items[i].clear();
        }
    }


    return 0;
}
