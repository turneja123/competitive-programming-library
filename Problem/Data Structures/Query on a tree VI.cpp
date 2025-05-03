//https://www.spoj.com/problems/QTREE6/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int color[N];
vector<int> adj[N];
int parent[N];

struct Node {
    Node* l = nullptr;
    Node* r = nullptr;
    Node* p = nullptr;
    int i;
    int sum;
    int vir;
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
        sum = 1 + (l ? l->sum : 0) + (r ? r->sum : 0) + vir;
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
            a[i].sum = 1;
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

    void cut(int v) {
		access(v);
		if (a[v].l) {
			a[v].l->p = nullptr;
			a[v].l = nullptr;
		}
		a[v].pull();
	}

    int query(int u) {
        access(u);
        Node* r = &a[u];
        while (r->l) {
            r = r->l;
        }
        splay(r);
        if (color[r->i] != color[u]) {
            r = r->r;
        }
        return r->sum;
    }
};

void dfs(int u, int p) {
    parent[u] = p;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
    return;
}

int main() {
    IOS;
    int n, m;
    cin >> n;
    LCT black(n);
    LCT white(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, -1);
    for (int i = 1; i < n; i++) {
        black.link(i, parent[i]);
    }
    cin >> m;
    for (int i = 0; i < m; i++) {
        int t, u;
        cin >> t >> u;
        u--;
        if (t == 0) {
            if (color[u] == 0) {
                cout << black.query(u) << endl;
            } else {
                cout << white.query(u) << endl;
            }
        } else {
            if (color[u] == 0) {
                if (u != 0) {
                    black.cut(u);
                    white.link(u, parent[u]);
                }
                color[u] = 1;
            } else {
                if (u != 0) {
                    white.cut(u);
                    black.link(u, parent[u]);
                }
                color[u] = 0;
            }
        }
    }


    return 0;
}
