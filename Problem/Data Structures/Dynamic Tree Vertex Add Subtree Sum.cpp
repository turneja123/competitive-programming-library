//https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_subtree_sum
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

long long a_init[N];

struct Node {
    Node* l = nullptr;
    Node* r = nullptr;
    Node* p = nullptr;
    int i;
    long long val;
    long long sum;
    long long vir;
    bool rev = false;
    Node() {}
    Node(int x) {
        i = x;
    }
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
	}
	void pull() {
        sum = val + (l ? l->sum : 0) + (r ? r->sum : 0) + vir;
    }
    bool is_root() {
        return p == 0 || (p->l != this && p->r != this);
    }
};

struct LCT {
    vector<Node> a;
    LCT(int n) {
        a.resize(n);
        for (int i = 0; i < n; i++) {
            a[i].i = i;
            a[i].val = a_init[i];
            a[i].sum = a_init[i];
            a[i].vir = 0;
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
            if (p->r) {
                p->vir += p->r->sum;
            }
            if (last) {
                p->vir -= last->sum;
            }
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
            c->vir += c->l->sum;
            c->l = nullptr;
        }
    }

    void link(int u, int v) {
        make_root(u);
        access(v);
        a[u].p = &a[v];
        a[v].vir += a[u].sum;
        a[v].pull();
    }

    void cut(int u, int v) {
		make_root(u);
		access(v);
		if (a[v].l) {
			a[v].l->p = nullptr;
			a[v].l = nullptr;
		}
		a[v].pull();
	}

    void upd(int u, int x) {
        access(u);
        a[u].val += x;
        a[u].pull();
    }

    long long query(int u, int v) {
        cut(v, u);
        long long ans = a[u].sum;
        link(v, u);
        return ans;
        /*make_root(v);
        access(u);
        return a[u].vir + a[u].val;*/
    }
};

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a_init[i];
    }
    LCT lct(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        lct.link(u, v);
    }

    for (int i = 0; i < m; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            int u, v, w, x;
            cin >> u >> v >> w >> x;
            lct.cut(u, v);
            lct.link(w, x);
        } else if (t == 1) {
            int u, x;
            cin >> u >> x;
            lct.upd(u, x);
        } else {
            int u, v;
            cin >> u >> v;
            cout << lct.query(u, v) << endl;
        }
    }
    return 0;
}
