//https://codeforces.com/contest/1957/problem/F2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int MAX = 1e7;
const int K = 18;

const long long P = 26, Q = 53;
const long long M = 1e9 + 7;

pair<long long, long long> mul(pair<long long, long long> a, pair<long long, long long> b) {
    return make_pair(a.first * b.first % M, a.second * b.second % M);
}

struct Node {
    int left, right;
    pair<long long, long long> val;
    pair<long long, long long> invval;
    Node() {
        left = -1, right = -1, val = make_pair(1, 1), invval = make_pair(1, 1);
    }
};

Node nodes[MAX];
int root[N];
int idx = 0;


vector<int> adj[N];
int a[N];
int tin[N];
int tout[N];
int up[K][N];
int timer = 0;

int ans = 0;
int found = 0;

long long modPow(long long a, long long y) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
}

void build(int node, int l, int r) {
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    nodes[node].left = idx;
    nodes[idx++] = Node();
    nodes[node].right = idx;
    nodes[idx++] = Node();
    build(nodes[node].left, l, mid);
    build(nodes[node].right, mid + 1, r);
}

void upd(int prev_node, int node, int l, int r, int x) {
    nodes[node].left = nodes[prev_node].left;
    nodes[node].right = nodes[prev_node].right;
    nodes[node].val = nodes[prev_node].val;
    nodes[node].invval = nodes[prev_node].invval;
    if (l == r) {
        nodes[node].val = mul(nodes[node].val, make_pair(x + P, x + Q));
        nodes[node].invval = mul(nodes[node].invval, make_pair(modPow(x + P, M - 2), modPow(x + Q, M - 2)));
        return;
    }
    int mid = (l + r) / 2;
    if (x <= mid) {
        nodes[node].left = idx;
        nodes[idx++] = Node();
        upd(nodes[prev_node].left, nodes[node].left, l, mid, x);
    } else {
        nodes[node].right = idx;
        nodes[idx++] = Node();
        upd(nodes[prev_node].right, nodes[node].right, mid + 1, r, x);
    }
    nodes[node].val = mul(nodes[nodes[node].left].val, nodes[nodes[node].right].val);
    nodes[node].invval = mul(nodes[nodes[node].left].invval, nodes[nodes[node].right].invval);
}


void query(int u1, int v1, int l1, int p1, int u2, int v2, int l2, int p2, int f1, int f2, int l, int r) {
    if (l == r) {
        pair<long long, long long> x = mul(nodes[u1].val, nodes[v1].val);
        x = mul(x, nodes[l1].invval);
        if (f1) {
            x = mul(x, nodes[p1].invval);
        }

        pair<long long, long long> y = mul(nodes[u2].val, nodes[v2].val);
        y = mul(y, nodes[l2].invval);
        if (f2) {
            y = mul(y, nodes[p2].invval);
        }
        if (x == y) {
            ans = l;
        }
        return;
    }
    pair<long long, long long> x = mul(nodes[nodes[u1].left].val, nodes[nodes[v1].left].val);
    x = mul(x, nodes[nodes[l1].left].invval);
    if (f1) {
        x = mul(x, nodes[nodes[p1].left].invval);
    }

    pair<long long, long long> y = mul(nodes[nodes[u2].left].val, nodes[nodes[v2].left].val);
    y = mul(y, nodes[nodes[l2].left].invval);
    if (f2) {
        y = mul(y, nodes[nodes[p2].left].invval);
    }
    int mid = (l + r) / 2;
    if (x != y) {
        query(nodes[u1].left, nodes[v1].left, nodes[l1].left, nodes[p1].left, nodes[u2].left, nodes[v2].left, nodes[l2].left, nodes[p2].left, f1, f2, l, mid);
    } else {
        ans = mid;
        query(nodes[u1].right, nodes[v1].right, nodes[l1].right, nodes[p1].right, nodes[u2].right, nodes[v2].right, nodes[l2].right, nodes[p2].right, f1, f2, mid + 1, r);
    }

}

void go(int u1, int v1, int l1, int p1, int u2, int v2, int l2, int p2, int f1, int f2, int l, int r, int lq, int rq) {
    if (l > rq || r < lq) {
        return;
    }
    if (found) {
        return;
    }
    if (l >= lq && r <= rq) {
        pair<long long, long long> x = mul(nodes[u1].val, nodes[v1].val);
        x = mul(x, nodes[l1].invval);
        if (f1) {
            x = mul(x, nodes[p1].invval);
        }

        pair<long long, long long> y = mul(nodes[u2].val, nodes[v2].val);
        y = mul(y, nodes[l2].invval);
        if (f2) {
            y = mul(y, nodes[p2].invval);
        }
        if (x != y) {
            found = 1;
            ans = l - 1;
            query(u1, v1, l1, p1, u2, v2, l2, p2, f1, f2, l, r);
        }
        return;
    }
    int mid = (l + r) / 2;
    go(nodes[u1].left, nodes[v1].left, nodes[l1].left, nodes[p1].left, nodes[u2].left, nodes[v2].left, nodes[l2].left, nodes[p2].left, f1, f2, l, mid, lq, rq);
    go(nodes[u1].right, nodes[v1].right, nodes[l1].right, nodes[p1].right, nodes[u2].right, nodes[v2].right, nodes[l2].right, nodes[p2].right, f1, f2, mid + 1, r, lq, rq);
}



void dfs(int u, int p, int prev_root) {
    tin[u] = timer++;
    up[0][u] = p;
    for (int k = 1; k < K; k++) {
        up[k][u] = up[k - 1][up[k - 1][u]];
    }
    root[u] = idx;
    nodes[idx++] = Node();
    upd(prev_root, root[u], 0, N - 1, a[u]);
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, root[u]);
        }
    }
    tout[u] = timer++;
    return;
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v) {
    if (is_ancestor(u, v)) {
        return u;
    }
    if (is_ancestor(v, u)) {
        return v;
    }
    for (int k = K - 1; k >= 0; k--) {
        if (!is_ancestor(up[k][u], v)) {
            u = up[k][u];
        }
    }
    return up[0][u];
}

int main() {
    IOS;
    nodes[idx++] = Node();
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
    build(0, 0, N - 1);
    dfs(0, 0, 0);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int u1, v1, u2, v2, k;
        cin >> u1 >> v1 >> u2 >> v2 >> k;
        u1--, v1--, u2--, v2--;
        int l1 = lca(u1, v1), l2 = lca(u2, v2);
        ans = -1;
        vector<int> add;
        int lf = 0;
        for (int j = 0; j < k; j++) {
            if (lf >= N) {
                break;
            }
            ans = -1;
            found = 0;
            go(root[u1], root[v1], root[l1], root[up[0][l1]], root[u2], root[v2], root[l2], root[up[0][l2]], l1, l2, 0, N - 1, lf, N - 1);
            if (found == 0) {
                break;
            }
            lf = ans + 2;
            add.push_back(ans + 1);
        }
        cout << add.size() << " ";
        for (int x : add) {
            cout << x << " ";
        }
        cout << endl;
    }
    return 0;
}
