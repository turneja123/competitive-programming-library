//https://toph.co/p/jontrona-of-liakot
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int K = 30;
const int MAX = 1e7 + 5;

struct Node {
    int ct;
    int left;
    int right;
    Node() : ct(0), left(-1), right(-1) {}
};

Node nodes[MAX];

int a[N];
int tin[N];
int tout[N];
int tour[N];
int sz[N];
int root[N];

int timer = 0, idx = 0;

vector<int> adj[N];

int get_left(int node) {
    if (node == -1) {
        return -1;
    }
    return nodes[node].left;
}

int get_right(int node) {
    if (node == -1) {
        return -1;
    }
    return nodes[node].right;
}

int get_ct(int node) {
    if (node == -1) {
        return 0;
    }
    return nodes[node].ct;
}

int query(int node_lu, int node_ru, int node_lv, int node_rv, int d, int val, int k, int ans) {
    if (d == -1) {
        return ans;
    }
    int c = val & (1 << d);
    if (c == 0) {
        int lu = get_left(node_lu), ru = get_left(node_ru), lv = get_left(node_lv), rv = get_left(node_rv);

        int ct = get_ct(ru) - get_ct(lu) - (get_ct(rv) - get_ct(lv));
        if (ct < k) {
            return query(get_right(node_lu), get_right(node_ru), get_right(node_lv), get_right(node_rv), d - 1, val, k - ct, ans ^ (1 << d));
        } else {
            return query(lu, ru, lv, rv, d - 1, val, k, ans);
        }
    } else {
        int lu = get_right(node_lu), ru = get_right(node_ru), lv = get_right(node_lv), rv = get_right(node_rv);

        int ct = get_ct(ru) - get_ct(lu) - (get_ct(rv) - get_ct(lv));
        if (ct < k) {
            return query(get_left(node_lu), get_left(node_ru), get_left(node_lv), get_left(node_rv), d - 1, val, k - ct, ans ^ (1 << d));
        } else {
            return query(lu, ru, lv, rv, d - 1, val, k, ans);
        }
    }
}

void add(int node_prev, int node, int d, int val) {
    if (d < 0) {
        return;
    }
    int c = val & (1 << d);
    if (c == 0) {
        nodes[node].left = idx;
        nodes[idx++] = Node();
        nodes[nodes[node].left].ct = 1;
        if (node_prev != -1) {
            nodes[nodes[node].left].ct += nodes[nodes[node_prev].left].ct;
            nodes[node].right = nodes[node_prev].right;
        }
        add((node_prev == -1 ? -1 : nodes[node_prev].left), nodes[node].left, d - 1, val);
        return;
    } else {
        nodes[node].right = idx;
        nodes[idx++] = Node();
        nodes[nodes[node].right].ct = 1;
        if (node_prev != -1) {
            nodes[nodes[node].right].ct += nodes[nodes[node_prev].right].ct;
            nodes[node].left = nodes[node_prev].left;
        }
        add((node_prev == -1 ? -1 : nodes[node_prev].right), nodes[node].right, d - 1, val);
        return;
    }
}

void dfs(int u, int p) {
    tour[timer] = u;
    tin[u] = timer++;
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            sz[u] += sz[v];
        }
    }
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, -1);
    nodes[idx++] = Node();
    int last = 0;
    for (int i = 0; i < n; i++) {
        root[i] = idx;
        nodes[idx++] = Node();
        add(last, root[i], K - 1, a[tour[i]]);
        last = root[i];
    }
    for (int i = 0; i < q; i++) {
        int u, v, z, k;
        cin >> u >> v >> z >> k;
        u--, v--;
        if (u == v) {
            cout << -1 << endl;
            continue;
        }
        int lu = tin[u], ru = tin[u] + sz[u] - 1;
        int lv = tin[v], rv = tin[v] + sz[v] - 1;
        if (ru - lu - (rv - lv) < k) {
            cout << -1 << endl;
            continue;
        }
        cout << query((lu - 1 < 0 ? - 1 : root[lu - 1]), root[ru], (lv - 1 < 0 ? - 1 : root[lv - 1]), root[rv], K - 1, z, k, 0) << endl;
    }
    return 0;
}
