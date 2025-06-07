//https://judge.yosupo.jp/problem/incremental_minimum_spanning_forest
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e6 + 5;
const int INF = 2e9;

int ptr = 0;

int id[N];
tuple<int, int, int> edges_added[N];

struct Node {
    Node* l = nullptr;
    Node* r = nullptr;
    Node* p = nullptr;
    int i;
    int val;
    int mx;
    int pos;
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
	}
	void pull() {
	    if (val >= (l ? l->mx : -INF) && val >= (r ? r->mx : -INF)) {
            mx = val;
            pos = i;
	    } else if ((l ? l->mx : -INF) >= (r ? r->mx : -INF)) {
            mx = l->mx;
            pos = l->pos;
	    } else {
            mx = r->mx;
            pos = r->pos;
	    }
    }
    bool is_root() {
        return p == 0 || (p->l != this && p->r != this);
    }
};

Node* go[N];

struct LCT {
    vector<Node> a;
    LCT(int n) {
        a.resize(N);
        for (int i = 0; i < N; i++) {
            a[i].i = i;
            a[i].val = -INF;
            a[i].mx = -INF;
            a[i].pos = i;
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
        Node* y = c;
        int j = 0;
        go[j++] = y;
        while (!y->is_root()) {
            y = y->p;
            go[j++] = y;
        }
        while (j) {
            go[--j]->push();
        }

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
    }

    void link(int u, int v, int y) {
        edges_added[ptr] = make_tuple(u, v, y);
        a[ptr].val = y;
        a[ptr].mx = y;
        link(u, ptr);
        link(v, ptr);
        ptr++;
    }

    void cut(int u, int v) {
		make_root(u);
		access(v);
		if (a[v].l) {
			a[v].l->p = nullptr;
			a[v].l = nullptr;
		}
	}

	bool connected(int u, int v) {
		access(u);
		access(v);
		return a[u].p;
	}

    int query(int u, int v) {
        make_root(u);
        access(v);
        return a[v].pos;
    }
};

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    LCT lct(n);
    ptr = n;
    for (int i = 0; i < m; i++) {
        int u, v, y;
        cin >> u >> v >> y;
        if (u == v) {
            cout << i << " ";
            continue;
        }
        if (!lct.connected(u, v)) {
            cout << -1 << " ";
            id[ptr] = i;
            lct.link(u, v, y);
        } else {
            int j = lct.query(u, v);
            int diff = y - get<2>(edges_added[j]);
            if (diff < 0) {
                cout << id[j] << " ";
                lct.cut(u, j);
                lct.cut(v, j);
                id[ptr] = i;
                lct.link(u, v, y);
            } else {
                cout << i << " ";
            }
        }
    }

    return 0;
}
