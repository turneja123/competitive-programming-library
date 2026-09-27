//https://codeforces.com/contest/1599/problem/I
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const int INF = 1e9;

int a_init[N];

struct Node {
    Node* l = nullptr;
    Node* r = nullptr;
    Node* p = nullptr;
    int i;
    int sz = 0;
    int val = 0;
    int mx = 0;
    int lazy_set = 0;
    int is_edge;
    int edge_ct;

    bool set_flag = false;
    bool rev = false;
    Node() {}
    void push() {
		if (rev) {
			rev = false;
			swap(l, r);
			if (l) {
                l->rev ^= true;
			}
			if (r) {
                r->rev ^= true;
			}
		}
		if (set_flag) {
            if (is_edge) {
                val = lazy_set;
            }
            if (edge_ct) {
                mx = lazy_set;
            }
            if (l) {
                l->set_flag = true;
                l->lazy_set = lazy_set;
            }
            if (r) {
                r->set_flag = true;
                r->lazy_set = lazy_set;
            }
		}
		lazy_set = 0;
		set_flag = false;
	}
	void pull() {
	    if (l) {
            l->push();
	    }
	    if (r) {
            r->push();
	    }
        sz = 1 + (l ? l->sz : 0) + (r ? r->sz : 0);
        edge_ct = is_edge + (l ? l->edge_ct : 0) + (r ? r->edge_ct : 0);
        mx = max({val, (l ? l->mx : -INF), (r ? r->mx : -INF)});
    }
    bool is_root() {
        return p == 0 || (p->l != this && p->r != this);
    }
};

struct LCT {
    vector<Node> a;
    int root;
    LCT(int n, int r) {
        root = r;
        a.resize(n);
        for (int i = 0; i < n; i++) {
            a[i].i = i;
            a[i].val = -1;
            a[i].mx = -1;
            a[i].sz = 1;
            a[i].is_edge = a_init[i];
            a[i].edge_ct = a_init[i];
        }
    }
    void rot(Node* c) {
        Node* p = c->p;
        Node* g = p->p;
        if (!p->is_root()) {
            (g->r == p ? g->r : g->l) = c;
        }

        p->push();
        c->push();

        if (p->l == c) {
            p->l = c->r;
            c->r = p;
            if (p->l) {
                p->l->p = p;
            }
        } else {
            p->r = c->l;
            c->l = p;
            if (p->r) {
                p->r->p = p;
            }
        }

        p->p = c;
        c->p = g;
        p->pull();
        c->pull();
    }

    void splay(Node* c) {
        while (!c->is_root()) {
            Node* p = c->p;
            Node* g = p->p;
            if (!p->is_root()) {
                rot((g->r == p) == (p->r == c) ? p : c);
            }
            rot(c);
        }
        c->push();
    }

    Node* access(int v) {
        Node* last = nullptr;
        Node* c = &a[v];
        for (Node* p = c; p; p = p->p) {
            splay(p);
            p->r = last;
            p->pull();
            last = p;
        }
        splay(c);
        return last;
    }

    void make_root(int v) {
        access(v);
        Node* c = &a[v];
        if (c->l) {
            c->l->rev ^= true;
            c->l = nullptr;
        }
    }

    void link(int u, int v) {
        make_root(u);
        Node* c = &a[u];
        c->p = &a[v];
        make_root(root);
    }

    void cut(int v) {
        access(v);
        if (a[v].l) {
            a[v].l->p = nullptr;
            a[v].l = nullptr;
        }
    }

    void cut(int u, int v) {
		make_root(u);
		access(v);
		if (a[v].l) {
			a[v].l->p = nullptr;
			a[v].l = nullptr;
		}
		make_root(root);
	}

    void upd(int u, int v, int x) {
        make_root(u);
        access(v);
        a[v].lazy_set = x;
        a[v].set_flag = true;
        make_root(root);
    }

    int query(int u, int v) {
        make_root(u);
        access(v);
        int ans = 0;
        ans = a[v].mx;
        make_root(root);
        return ans;
    }

    int get_parent(int u) {
        access(u);
        if (a[u].l) {
            return a[u].l->i;
        }
        return -1;
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
        if (!connected(u, v)) {
            return -1;
        }
        access(u);
        return access(v)->i;
    }
};

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        a_init[n + i] = 1;
    }
    LCT lct(N, 0);
    vector<pair<int, int>> edges;
    vector<int> cycle_edge(m, 0);
    ll ans = 0;
    for (int i = 0, l = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        edges.push_back({u, v});
        if (!lct.connected(u, v)) {
            lct.link(u, n + i);
            lct.link(v, n + i);
        } else {
            int col = lct.query(u, v);
            if (col == -1) {
                lct.upd(u, v, i);
                cycle_edge[i] = 1;
            } else {
                while (l < i) {
                    auto [U, V] = edges[l];
                    if (!cycle_edge[l]) {
                        int e = lct.query(n + l, n + l);
                        if (e == -1) {
                            lct.cut(U, n + l);
                            lct.cut(V, n + l);
                        } else {
                            auto [UU, VV] = edges[e];
                            lct.upd(UU, VV, -1);
                            lct.cut(U, n + l);
                            lct.cut(V, n + l);

                            lct.link(UU, n + e);
                            lct.link(VV, n + e);

                            cycle_edge[e] = 0;
                        }
                    } else {
                        cycle_edge[l] = 0;
                        lct.upd(U, V, -1);
                    }
                    l++;
                    if (!lct.connected(u, v)) {
                        lct.link(u, n + i);
                        lct.link(v, n + i);
                        break;
                    } else {
                        int col = lct.query(u, v);
                        if (col == -1) {
                            lct.upd(u, v, i);
                            cycle_edge[i] = 1;
                            break;
                        }
                    }
                }
            }
        }
        ans += i - l + 1;
    }
    cout << ans;


    return 0;
}
