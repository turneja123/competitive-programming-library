//https://codeforces.com/contest/1916/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

int timer = 0;
int sz[N];
int pos[N];
int last[N];
int c[N];
int depth[N];
vector<int> adj[N];
vector<int> updates[N];


struct Node {
    int sum;
    int lazy;
    Node() {
        lazy = 0;
    }
    Node(int x) : sum(x), lazy(0) {}
};

int a[N];
Node segtree[4 * N];

Node combine(Node left, Node right) {
    Node node = Node();
    node.sum = max(left.sum, right.sum);
    return node;
}

void compose(int parent, int child) {
    segtree[child].lazy += segtree[parent].lazy;
}

void apply(int node, int l, int r) {
    segtree[node].sum += segtree[node].lazy;
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    segtree[node].lazy = 0;
}

void incUpdate(int node, int l, int r, int lq, int rq, int add) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[node].lazy += add;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    incUpdate(node * 2 + 1, l, mid, lq, rq, add);
    incUpdate(node * 2 + 2, mid + 1, r, lq, rq, add);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int getSum(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return 0;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree[node].sum;
    }
    int mid = (l + r) / 2;
    return max(getSum(l, mid, lq, rq, 2 * node + 1), getSum(mid + 1, r, lq, rq, 2 * node + 2));
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = Node(0);
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

vector<int> path;

void dfs_sz(int u, int p) {
    path.push_back(u);
    int rb = last[c[u]];
    if (rb == -1) {
        updates[0].push_back(u);
    } else {
        updates[path[depth[rb] + 1]].push_back(u);
    }
    last[c[u]] = u;
    pos[u] = timer++;
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs_sz(v, u);
            sz[u] += sz[v];
        }
    }
    path.pop_back();
    last[c[u]] = rb;
}

ll ans = 1;

void dfs(int u, int p, int n) {
    for (int v : updates[u]) {
        incUpdate(0, 0, n - 1, pos[v], pos[v] + sz[v] - 1, 1);
    }
    incUpdate(0, 0, n - 1, pos[u], pos[u] + sz[u] - 1, -1);
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, n);
        }
    }
    incUpdate(0, 0, n - 1, pos[u], pos[u] + sz[u] - 1, 1);
    vector<int> sizes;
    for (int v : adj[u]) {
        if (v != p) {
            sizes.push_back(getSum(0, n - 1, pos[v], pos[v] + sz[v] - 1, 0));
        }
    }
    if (sizes.size()) {
        sort(sizes.begin(), sizes.end(), greater<int>());
        ans = max(ans, (ll)sizes[0]);
        if (sizes.size() > 1) {
            ans = max(ans, (ll)sizes[0] * sizes[1]);
        }
    }

    for (int v : updates[u]) {
        incUpdate(0, 0, n - 1, pos[v], pos[v] + sz[v] - 1, -1);
    }
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 1; i < n; i++) {
            int p;
            cin >> p;
            p--;
            adj[p].push_back(i);
            adj[i].push_back(p);
        }
        for (int i = 0; i < n; i++) {
            cin >> c[i];
            c[i]--;
            last[i] = -1;
        }
        build(0, n - 1, 0);
        dfs_sz(0, 0);
        dfs(0, 0, n);
        for (int i = 0; i < n; i++) {
            updates[i].clear();
            adj[i].clear();

        }
        cout << ans << endl;
        ans = 1;
        timer = 0;
    }
    return 0;
}
