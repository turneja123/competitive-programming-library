//https://codeforces.com/contest/2152/problem/G
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const int INF = 1e9;

int timer = 0;
int tin[N];
int tout[N];
int a[N];
int val[N];

vector<int> adj[N];


struct Node {
    int ab;
    int ba;
    int cd;
    int dc;
    int aa;
    int bb;
    int cc;
    int dd;
    int lazy;
    Node() {
        lazy = 0;
    }
    Node(int x) {
        ab = -INF, ba = -INF, cd = -INF, dc = -INF;
        aa = -INF, bb = -INF, cc = -INF, dd = -INF;
        if (x == 0) {
            aa = 1;
        } else if (x == 1) {
            bb = 1;
        } else if (x == 2) {
            cc = 1;
        } else {
            dd = 1;
        }
        lazy = 0;
    }
};

Node segtree[4 * N];

Node combine(Node left, Node right) {
    Node node = Node();
    node.ab = max({left.ab, right.ab, left.ab + right.ab, left.aa + right.bb});
    node.ba = max({left.ba, right.ba, left.ba + right.ba, left.bb + right.aa});
    node.cd = max({left.cd, right.cd, left.cd + right.cd, left.cc + right.dd});
    node.dc = max({left.dc, right.dc, left.dc + right.dc, left.dd + right.cc});

    node.aa = max({left.aa, right.aa, left.ab + right.aa, left.aa + right.ba});
    node.bb = max({left.bb, right.bb, left.ba + right.bb, left.bb + right.ab});
    node.cc = max({left.cc, right.cc, left.cd + right.cc, left.cc + right.dc});
    node.dd = max({left.dd, right.dd, left.dc + right.dd, left.dd + right.cd});
    return node;
}

void compose(int parent, int child) {
    segtree[child].lazy ^= segtree[parent].lazy;
}

void apply(int node, int l, int r) {
    if (segtree[node].lazy == 1) {
        swap(segtree[node].ab, segtree[node].cd);
        swap(segtree[node].ba, segtree[node].dc);
        swap(segtree[node].aa, segtree[node].cc);
        swap(segtree[node].bb, segtree[node].dd);
    }

    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    segtree[node].lazy = 0;
}

void incUpdate(int node, int l, int r, int lq, int rq) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[node].lazy ^= 1;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    incUpdate(node * 2 + 1, l, mid, lq, rq);
    incUpdate(node * 2 + 2, mid + 1, r, lq, rq);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = Node(val[l]);
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

void dfs(int u, int p) {
    tin[u] = timer;
    val[timer] = (a[u] ? 2 : 0);
    timer++;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
    tout[u] = timer;
    val[timer] = (a[u] ? 3 : 1);
    timer++;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        int q;
        cin >> q;
        dfs(0, 0);
        build(0, 2 * n - 1, 0);
        cout << max(0, segtree[0].cd / 2)  << endl;
        for (int i = 0; i < q; i++) {
            int u;
            cin >> u;
            u--;
            incUpdate(0, 0, 2 * n - 1, tin[u], tout[u]);
            apply(0, 0, 2 * n - 1);
            cout << max(0, segtree[0].cd / 2)  << endl;
        }


        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
        timer = 0;

    }
    return 0;
}
