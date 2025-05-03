//https://dmoj.ca/problem/ds5easy
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long INF = 1e18;

int a_init[N];

struct Node {
    Node* l = nullptr;
    Node* r = nullptr;
    Node* p = nullptr;
    int i;
    int sz = 0;
    long long val = 0;
    long long sum = 0;
    long long mn = 0;
    long long mx = 0;
    long long lazy_inc = 0;
    long long lazy_set = 0;
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
            val = lazy_set;
            mn = lazy_set;
            mx = lazy_set;
            sum = lazy_set * sz;
            if (l) {
                l->set_flag = true;
                l->lazy_set = lazy_set;
                l->lazy_inc = 0;
            }
            if (r) {
                r->set_flag = true;
                r->lazy_set = lazy_set;
                r->lazy_inc = 0;
            }
		}
		if (lazy_inc) {
            val += lazy_inc;
            mn += lazy_inc;
            mx += lazy_inc;
            sum += lazy_inc * sz;
            if (l) {
                l->lazy_inc += lazy_inc;
            }
            if (r) {
                r->lazy_inc += lazy_inc;
            }
		}
		lazy_set = 0;
		lazy_inc = 0;
		set_flag = false;
	}
	void pull() {
	    if (l) {
            l->push();
	    }
	    if (r) {
            r->push();
	    }
        sum = val + (l ? l->sum : 0) + (r ? r->sum : 0);
        sz = 1 + (l ? l->sz : 0) + (r ? r->sz : 0);
        mn = min({val, (l ? l->mn : INF), (r ? r->mn : INF)});
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
            a[i].val = a_init[i];
            a[i].sum = a_init[i];
            a[i].mn = a_init[i];
            a[i].mx = a_init[i];
            a[i].sz = 1;
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

    void upd(int u, int v, int x, int f) {
        make_root(u);
        access(v);
        if (f == 1) {
            a[v].lazy_inc = 0;
            a[v].lazy_set = x;
            a[v].set_flag = true;
        } else {
            a[v].lazy_inc += x;
        }
        make_root(root);
    }

    long long query(int u, int v, int f) {
        make_root(u);
        access(v);
        long long ans = 0;
        if (f == 3) {
            ans = a[v].mn;
        } else if (f == 4) {
            ans = a[v].mx;
        } else {
            ans = a[v].sum;
        }
        make_root(root);
        return ans;
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
    for (int i = 0; i < n; i++) {
        cin >> a_init[i];
    }
    LCT lct(n, 0);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        lct.link(u, v);
    }
    int r;
    cin >> r;
    r--;
    lct.make_root(r);
    lct.root = r;
    for (int i = 0; i < m; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            int r;
            cin >> r;
            r--;
            if (r == lct.root) {
                continue;
            }
            lct.make_root(r);
            lct.root = r;
        } else if (t == 1 || t == 2) {
            int u, v, x;
            cin >> u >> v >> x;
            u--, v--;
            lct.upd(u, v, x, t);
        } else if (t == 3 || t == 4 || t == 5) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            cout << lct.query(u, v, t) << endl;
        } else if (t == 6) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            int l = lct.lca(u, v);
            if (l == u) {
                continue;
            }
            lct.cut(u);
            lct.link(u, v);
        } else {
            int u, v;
            cin >> u >> v;
            u--, v--;
            cout << lct.lca(u, v) + 1 << endl;
        }
    }
    return 0;
}
