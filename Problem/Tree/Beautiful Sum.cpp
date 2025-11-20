//https://www.codechef.com/problems/XPS
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int K = 20;

vector<pair<int, int>> adj[N];
int depth[N];
int val[N];
int pos[N];
int tour[N];
int sz[N];
int timer = 0;

struct Node {
    int sum[K][2];
    int lazy[2];
    int ct[2];

    Node() {
        lazy[0] = 0;
        lazy[1] = 0;
        ct[0] = 0;
        ct[1] = 0;
        for (int i = 0; i < K; i++) {
            sum[i][0] = 0;
            sum[i][1] = 0;
        }

    }
    Node(int u) {
        lazy[0] = 0;
        lazy[1] = 0;
        ct[0] = 0;
        ct[1] = 0;
        ct[depth[u] % 2] = 1;
        for (int i = 0; i < K; i++) {
            sum[i][0] = 0;
            sum[i][1] = 0;
        }
        for (int i = 0; i < K; i++) {
            int c = (1 << i) & val[u];
            if (c) {
                sum[i][depth[u] % 2] = 1;
            }
        }
    }
};

int a[N];
Node segtree[4 * N];

Node combine(Node left, Node right) {
    Node node = Node();
    node.ct[0] = left.ct[0] + right.ct[0];
    node.ct[1] = left.ct[1] + right.ct[1];
    for (int i = 0; i < K; i++) {
        node.sum[i][0] = left.sum[i][0] + right.sum[i][0];
        node.sum[i][1] = left.sum[i][1] + right.sum[i][1];
    }
    return node;
}

void compose(int parent, int child) {
    segtree[child].lazy[0] ^= segtree[parent].lazy[0];
    segtree[child].lazy[1] ^= segtree[parent].lazy[1];
}

void apply(int node, int l, int r) {
    if (segtree[node].lazy[0]) {
        for (int i = 0; i < K; i++) {
            int c = segtree[node].lazy[0] & (1 << i);
            if (c) {
                segtree[node].sum[i][0] = segtree[node].ct[0] - segtree[node].sum[i][0];
            }
        }
    }
    if (segtree[node].lazy[1]) {
        for (int i = 0; i < K; i++) {
            int c = segtree[node].lazy[1] & (1 << i);
            if (c) {
                segtree[node].sum[i][1] = segtree[node].ct[1] - segtree[node].sum[i][1];
            }
        }
    }
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    segtree[node].lazy[0] = 0;
    segtree[node].lazy[1] = 0;
}

void incUpdate(int node, int l, int r, int lq, int rq, int add, int d) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[node].lazy[(d + 1) % 2] ^= add;

        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    incUpdate(node * 2 + 1, l, mid, lq, rq, add, d);
    incUpdate(node * 2 + 2, mid + 1, r, lq, rq, add, d);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

Node getNode(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        Node sentinel = Node();
        return sentinel;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree[node];
    }
    int mid = (l + r) / 2;
    return combine(getNode(l, mid, lq, rq, 2 * node + 1), getNode(mid + 1, r, lq, rq, 2 * node + 2));
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        int u = tour[l];
        segtree[node] = Node(u);
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

void dfs(int u, int p) {
    tour[timer] = u;
    pos[u] = timer++;
    sz[u] = 1;
    for (auto [v, wt] : adj[u]) {
        if (v != p) {
            val[v] = val[u] ^ wt;
            depth[v] = depth[u] + 1;
            dfs(v, u);
            sz[u] += sz[v];
        }
    }

}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n;
        for (int i = 1; i < n; i++) {
            int u, v, wt;
            cin >> u >> v >> wt;
            u--, v--;
            adj[u].push_back({v, wt});
            adj[v].push_back({u, wt});
        }
        dfs(0, 0);
        build(0, n - 1, 0);
        cin >> q;
        for (int i = 0; i < q; i++) {
            int t;
            cin >> t;
            if (t == 1) {
                int u, x;
                cin >> u >> x;
                u--;
                incUpdate(0, 0, n - 1, pos[u], pos[u] + sz[u] - 1, x, depth[u]);
            } else {
                int u;
                cin >> u;
                u--;
                ll ans = 0;
                Node node = getNode(0, n - 1, pos[u], pos[u] + sz[u] - 1, 0);
                for (int j = 0; j < K; j++) {
                    ll add = 0;
                    for (int dx = 0; dx <= 1; dx++) {
                        for (int dy = 0; dy <= 1; dy++) {
                            add += (ll)node.sum[j][dx] * (node.ct[dy] - node.sum[j][dy]);
                        }
                    }
                    ans += add * (1 << j);
                }
                cout << ans << endl;
            }
        }
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
        timer = 0;
    }
    return 0;
}
