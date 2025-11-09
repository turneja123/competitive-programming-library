//https://dmoj.ca/problem/dmopc20c1p5
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

struct BIT {
    int n;
    vector<int> t;
    BIT(int _n) {
        n = _n;
        t.assign(n + 1, 0);
    }
    void upd(int i, int val) {
        if (i <= 0) {
            return;
        }
        for (; i <= n; i += (i & -i)) {
            t[i] += val;
        }
    }
    int query(int i) {
        int ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans += t[i];
        }
        return ans;
    }
    int query(int l, int r) {
        return query(r) - query(l - 1);
    }
};


const int N = 5e5 + 5;
const int K = 21;


BIT bit(N);
vector<int> adj[N];
int timer = 0, e = 0;
int tour[N];
int sz[N];
int tin[2 * N];
int pos[N];
int a[N];
int table[K][2 * N];
int mn[K][2 * N];
int depth[N];

struct comp {
    bool operator()(int x, int y) const {
        return tour[x] < tour[y];
    }
};

set<int, comp> st[N];

void dfs(int u, int p) {
    pos[u] = timer;
    tin[timer++] = u;


    tour[u] = e++;
    sz[u] = 1;

    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
            sz[u] += sz[v];
            tin[timer++] = u;
        }
    }
}

void build(int n) {
    for (int i = 1; i <= n; i++) {
        int u = tin[i - 1];
        table[0][i] = depth[u];
        mn[0][i] = u;
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            if (table[k - 1][i] < table[k - 1][i + (1 << (k - 1))]) {
                table[k][i] = table[k - 1][i];
                mn[k][i] = mn[k - 1][i];
            } else {
                table[k][i] = table[k - 1][i + (1 << (k - 1))];
                mn[k][i] = mn[k - 1][i + (1 << (k - 1))];
            }
        }
    }
    return;
}

int query(int l, int r) {
    l++, r++;
    int k = 31 - __builtin_clz(r - l + 1);
    if (table[k][l] < table[k][r - (1 << k) + 1]) {
        return mn[k][l];
    }
    return mn[k][r - (1 << k) + 1];
}

int lca(int a, int b) {
    int l = pos[a];
    int r = pos[b];
    if (l > r) {
        swap(l, r);
    }
    return query(l, r);
}

void add(int u, int c) {
    bit.upd(tour[u] + 1, 1);

    auto it = st[c].insert(u).first;

    int l = -1, r = -1;
    if (it != st[c].begin()) {
        it--;
        l = *it;
        it++;
    }
    it++;
    if (it != st[c].end()) {
        r = *it;
    }
    if (l != -1) {
        int anc = lca(l, u);
        bit.upd(tour[anc] + 1, -1);
    }
    if (r != -1) {
        int anc = lca(r, u);
        bit.upd(tour[anc] + 1, -1);
    }
    if (l != -1 && r != -1) {
        int anc = lca(l, r);
        bit.upd(tour[anc] + 1, 1);
    }

}

void rem(int u, int c) {
    bit.upd(tour[u] + 1, -1);

    auto it = st[c].lower_bound(u);
    int l = -1, r = -1;
    if (it != st[c].begin()) {
        it--;
        l = *it;
        it++;
    }
    it++;
    if (it != st[c].end()) {
        r = *it;
    }
    if (l != -1) {
        int anc = lca(l, u);
        bit.upd(tour[anc] + 1, 1);
    }
    if (r != -1) {
        int anc = lca(r, u);
        bit.upd(tour[anc] + 1, 1);
    }
    if (l != -1 && r != -1) {
        int anc = lca(l, r);
        bit.upd(tour[anc] + 1, -1);
    }
    st[c].erase(u);


}

int main() {
    IOS;
    int n, q;
    cin >> n >> q >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
    }
    for (int i = 1; i < n; i++) {
        int v, u;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, 0);
    build(2 * n - 1);
    for (int i = 0; i < n; i++) {
        add(i, a[i]);
    }
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int c, u;
            cin >> u >> c;
            c--, u--;
            rem(u, a[u]);
            a[u] = c;
            add(u, a[u]);
        } else {
            int u;
            cin >> u;
            u--;
            cout << bit.query(tour[u] + 1, tour[u] + 1 + sz[u] - 1) << endl;
        }

    }
    return 0;
}
