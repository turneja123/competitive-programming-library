//https://dmoj.ca/problem/ds5
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int INF = 1e9 + 1;

struct Lazy {
    int a;
    int b;
    Lazy() {
        a = 1;
        b = 0;
    }
    bool is() {
        return a != 1 || b;
    }
};

struct Data {
    int sz;
    int mn;
    int mx;
    int sum;
    Data() {
        sz = 0;
        mn = INF;
        mx = -INF;
        sum = 0;
    }
    Data(int val) {
        sz = 1;
        mn = val;
        mx = val;
        sum = val;
    }
    Data(int _sz, int _mn, int _mx, int _sum) {
        sz = _sz;
        mn = _mn;
        mx = _mx;
        sum = _sum;
    }
};

struct Node {
    int p, val;
    int ch[4];
    Data path, subtree, all;
    Lazy lazy_path, lazy_subtree;
    bool rev, aux;
    Node() : p(0), ch(), path(), subtree(), all(), lazy_path(), lazy_subtree(), rev(false), aux(true) {}
    Node(int x) : Node() {
        val = x;
        path = Data(val);
        all = Data(val);
        rev = false;
        aux = false;
    }
};

Data operator + (const Data &a, const Data &b) {
    return Data(a.sz + b.sz, min(a.mn, b.mn), max(a.mx, b.mx), a.sum + b.sum);
}

struct LCT {
    vector<Node> a;
    vector<int> q;
    int root;
    LCT(int n, int r, vector<int> &a_init) {
        root = r;
        a.resize(N);
        for (int i = 1; i <= n; i++) {
            a[i] = Node(a_init[i - 1]);
        }
        for (int i = n + 1; i < N; i++) {
            q.push_back(i);
        }
    }
    void push_rev(int u) {
        if (u) {
            swap(a[u].ch[0], a[u].ch[1]);
            a[u].rev ^= true;
        }
    }
    void push_path(int u, Lazy &lazy) {
        if (u && !a[u].aux) {
            a[u].val = a[u].val * lazy.a + lazy.b;
            if (a[u].path.sz) {
                a[u].path.sum = a[u].path.sum * lazy.a + a[u].path.sz * lazy.b;
                a[u].path.mn = a[u].path.mn * lazy.a + lazy.b;
                a[u].path.mx = a[u].path.mx * lazy.a + lazy.b;
            }

            a[u].all = a[u].path + a[u].subtree;

            a[u].lazy_path.a = a[u].lazy_path.a * lazy.a;
            a[u].lazy_path.b = a[u].lazy_path.b * lazy.a + lazy.b;
        }
    }
    void push_subtree(int u, bool vir, Lazy &lazy) {
        if (u) {
            if (a[u].subtree.sz) {
                a[u].subtree.sum = a[u].subtree.sum * lazy.a + a[u].subtree.sz * lazy.b;
                a[u].subtree.mn = a[u].subtree.mn * lazy.a + lazy.b;
                a[u].subtree.mx = a[u].subtree.mx * lazy.a + lazy.b;
            }

            a[u].lazy_subtree.a = a[u].lazy_subtree.a * lazy.a;
            a[u].lazy_subtree.b = a[u].lazy_subtree.b * lazy.a + lazy.b;

            if (vir && !a[u].aux) {
                push_path(u, lazy);
            } else {
                a[u].all = a[u].path + a[u].subtree;
            }
        }
    }
    void push(int u) {
        if (u) {
            if (a[u].rev) {
                push_rev(a[u].ch[0]);
                push_rev(a[u].ch[1]);
                a[u].rev = false;
            }
            if (a[u].lazy_path.is()) {
                push_path(a[u].ch[0], a[u].lazy_path);
                push_path(a[u].ch[1], a[u].lazy_path);
                a[u].lazy_path.a = 1;
                a[u].lazy_path.b = 0;
            }
            if (a[u].lazy_subtree.is()) {
                push_subtree(a[u].ch[0], 0, a[u].lazy_subtree);
                push_subtree(a[u].ch[1], 0, a[u].lazy_subtree);
                push_subtree(a[u].ch[2], 1, a[u].lazy_subtree);
                push_subtree(a[u].ch[3], 1, a[u].lazy_subtree);
                a[u].lazy_subtree.a = 1;
                a[u].lazy_subtree.b = 0;
            }
        }
    }
    void pull(int u) {
        int l = a[u].ch[0], r = a[u].ch[1], v1 = a[u].ch[2], v2 = a[u].ch[3];
        if (!a[u].aux) {
            a[u].path = a[l].path + a[r].path + a[u].val;
        }
        a[u].subtree = a[l].subtree + a[r].subtree + a[v1].all + a[v2].all;
        a[u].all = a[u].path + a[u].subtree;
    }
    int pos(int u, int c) {
        int p = a[u].p;
        if (a[p].ch[c] == u) {
            return c;
        }
        if (a[p].ch[c + 1] == u) {
            return c + 1;
        }
        return -1;
    }
    void attach(int u, int c, int v) {
        a[u].ch[c] = v;
        a[v].p = u;
        pull(u);
    }
    void rot(int u, int c) {
        int p = a[u].p, pp = a[p].p, dx = pos(u, c), dy = pos(p, c);
        if (dy == -1 && !c) {
            dy = pos(p, 2);
        }
        attach(p, dx, a[u].ch[dx ^ 1]);
        attach(u, dx ^ 1, p);
        if (dy != -1) {
            attach(pp, dy, u);
        } else {
            a[u].p = pp;
        }
    }
    void splay(int u, int c) {
        push(u);
        while (pos(u, c) != -1 && (c == 0 || a[a[u].p].aux)) {
            int p = a[u].p, pp = a[p].p;
            push(pp);
            push(p);
            push(u);
            int dx = pos(u, c), dy = pos(p, c);
            if (dy != -1 && (c == 0 || a[pp].aux)) {
                rot(dx == dy ? p : u, c);
            }
            rot(u, c);
        }
    }
    int par(int u) {
        int v = a[u].p;
        if (!a[v].aux) {
            return v;
        }
        splay(v, 2);
        return a[v].p;
    }
    void go(int u) {
        if (a[u].aux) {
            go(a[u].p);
        }
        push(u);
    }
    void add(int u, int v) {
        if (!v) {
            return;
        }
        for (int i = 2; i < 4; i++) {
            if (!a[u].ch[i]) {
                attach(u, i, v);
                return;
            }
        }
        int w = q.back();
        q.pop_back();
        attach(w, 2, a[u].ch[2]);
        attach(w, 3, v);
        attach(u, 2, w);
    }
    void rem(int u) {
        int p = a[u].p;
        go(p);
        if (a[p].aux) {
            int pp = a[p].p;
            attach(pp, pos(p, 2), a[p].ch[pos(u, 2) ^ 1]);
            if (a[pp].aux) {
                splay(pp, 2);
            }
            q.push_back(p);
        } else {
            attach(p, pos(u, 2), 0);
        }
        a[u].p = 0;
    }
    int access(int u) {
        splay(u, 0);
        add(u, a[u].ch[1]);
        attach(u, 1, 0);
        int v = u;
        while (a[u].p) {
            v = par(u);
            splay(v, 0);
            rem(u);
            add(v, a[v].ch[1]);
            attach(v, 1, u);
            splay(u, 0);
        }
        return v;
    }
    void make_root(int u) {
        access(u);
        push_rev(u);
    }
    void link(int u, int v) {
        make_root(u);
        access(v);
        add(v, u);
    }
    void cut(int u, int v) {
        make_root(u);
        access(v);
        a[v].ch[0] = 0;
        a[u].p = 0;
        pull(v);
    }
    void cut(int v) {
        access(v);
        a[a[v].ch[0]].p = 0;
        a[v].ch[0] = 0;
        pull(v);
    }
    bool connected(int u, int v) {
		access(u);
		access(v);
		return a[u].p;
	}
    int lca(int u, int v) {
        if (u == v) {
            return u;
        }
        make_root(root);
        /*if (!connected(u, v)) {
            return -1;
        }*/
        access(u);
        return access(v);
    }
    void update_subtree(int u, int k, int x) {
        make_root(root);
        access(u);
        Lazy lazy;
        if (k == 0) {
            lazy.a = 0;
            a[u].val = x;
        } else {
            lazy.a = 1;
            a[u].val += x;
        }
        lazy.b = x;
        for (int i = 2; i < 4; i++) {
            push_subtree(a[u].ch[i], 1, lazy);
        }
    }
    void update_path(int u, int v, int k, int x) {
        make_root(u);
        access(v);
        Lazy lazy;
        if (k == 2) {
            lazy.a = 0;
        } else {
            lazy.a = 1;
        }
        lazy.b = x;
        push_path(v, lazy);
    }
    int query_subtree(int u, int k) {
        make_root(root);
        access(u);
        Data ans(a[u].val);
        for (int i = 2; i < 4; i++) {
            ans = ans + a[a[u].ch[i]].all;
        }
        if (k == 3) {
            return ans.mn;
        }
        if (k == 4) {
            return ans.mx;
        }
        return ans.sum;
    }
    int query_path(int u, int v, int k) {
        make_root(u);
        access(v);
        Data ans = a[v].path;
        if (k == 7) {
            return ans.mn;
        }
        if (k == 8) {
            return ans.mx;
        }
        return ans.sum;
    }
};

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> edges;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        edges.push_back(make_pair(u, v));
    }
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int r;
    cin >> r;
    LCT lct(n, r, a);
    for (auto [u, v] : edges) {
        lct.link(u, v);
    }
    for (int i = 0; i < q; i++) {
        int k;
        cin >> k;
        if (k == 1) {
            cin >> r;
            lct.root = r;
        }
        if (k == 0 || k == 5) {
            int u, x;
            cin >> u >> x;
            lct.update_subtree(u, k, x);
        }
        if (k == 2 || k == 6) {
            int u, v, x;
            cin >> u >> v >> x;
            lct.update_path(u, v, k, x);
        }
        if (k == 3 || k == 4 || k == 11) {
            int u;
            cin >> u;
            cout << lct.query_subtree(u, k) << endl;
        }
        if (k == 7 || k == 8 || k == 10) {
            int u, v;
            cin >> u >> v;
            cout << lct.query_path(u, v, k) << endl;
        }
        if (k == 9) {
            int u, v;
            cin >> u >> v;
            int l = lct.lca(u, v);
            if (l == u) {
                continue;
            }
            lct.cut(u);
            lct.link(u, v);
        }
    }
    return 0;
}
