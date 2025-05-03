//https://www.spoj.com/problems/DYNALCA/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

struct Node {
    Node* l = nullptr;
    Node* r = nullptr;
    Node* p = nullptr;
    int i;
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
    }

    void cut(int v) {
        access(v);
        if (a[v].l) {
            a[v].l->p = 0;
            a[v].l = 0;
        }
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
    LCT lct(n);
    for (int i = 0; i < m; i++) {
        string s; int u, v;
        cin >> s >> u;
        u--, v--;
        if (s == "link") {
            cin >> v;
            v--;
            lct.link(u, v);
        } else if (s == "cut") {
            lct.cut(u);
        } else {
            cin >> v;
            v--;
            cout << lct.lca(u, v) + 1 << endl;
        }
    }
    return 0;
}
