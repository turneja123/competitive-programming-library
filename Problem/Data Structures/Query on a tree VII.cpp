//https://www.spoj.com/problems/QTREE7/
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
int wt[N];

struct Node {
    Node* l = nullptr;
    Node* r = nullptr;
    Node* p = nullptr;
    int i;
    int sum;
    int val;
    multiset<int> vir;
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
        sum = val;
        if (l) {
            sum = max(sum, l->sum);
        }
        if (r) {
            sum = max(sum, r->sum);
        }
        if (vir.size()) {
            sum = max(sum, *vir.rbegin());
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
            a[i].sum = wt[i];
            a[i].val = wt[i];
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
                p->vir.insert(p->r->sum);
            }
            if (last) {
                p->vir.erase(p->vir.find(last->sum));
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
            c->vir.insert(c->l->sum);
            c->l = nullptr;
        }
    }

    void link(int u, int v) {
        make_root(u);
        access(v);
        a[u].p = &a[v];
        a[v].vir.insert(a[u].sum);
        a[v].pull();
    }

    void upd(int v, int x) {
        access(v);
        a[v].val = x;
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

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        cin >> color[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> wt[i];
    }
    dfs(0, -1);
    LCT black(n);
    LCT white(n);
    for (int i = 1; i < n; i++) {
        if (color[i] == 0) {
            black.link(i, parent[i]);
        } else {
            white.link(i, parent[i]);
        }
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
        } else if (t == 1) {
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
        } else {
            int w;
            cin >> w;
            black.upd(u, w);
            white.upd(u, w);
        }
    }
    return 0;
}
