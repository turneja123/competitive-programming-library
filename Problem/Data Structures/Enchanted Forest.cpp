//https://dmoj.ca/problem/noi14p2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a_init[N];
tuple<int, int, int> ed[N];

struct Node {
    Node* l = nullptr;
    Node* r = nullptr;
    Node* p = nullptr;
    int i;
    int val;
    int mx;
    int mx_who;
    int lazy_inc = 0;

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
	    if (l) {
            l->push();
	    }
	    if (r) {
            r->push();
	    }
        mx = max({val, (l ? l->mx : -1), (r ? r->mx : -1)});
        mx_who = i;
        if (l && l->mx == mx) {
            mx_who = l->mx_who;
        }
        if (r && r->mx == mx) {
            mx_who = r->mx_who;
        }
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
            a[i].mx = a_init[i];
            a[i].val = a_init[i];
            a[i].mx_who = i;
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

    int query(int u, int v) {
        make_root(u);
        access(v);
        int ans = a[v].mx_who;
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
    vector<tuple<int, int, int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v, a, b;
        cin >> u >> v >> a >> b;
        u--, v--;
        edges.push_back({a, b, u, v});
    }
    sort(edges.begin(), edges.end());
    for (int i = 0; i < m; i++) {
        auto [a, b, u, v] = edges[i];
        ed[i + n] = {u, v, b};
        a_init[i + n] = b;
    }
    LCT lct(n + m, 0);

    int ans = N, j = n;
    for (auto [a, b, u, v] : edges) {
        if (u == v) {
            j++;
            continue;
        }
        if (!lct.connected(u, v)) {
            lct.link(u, j);
            lct.link(v, j);
        } else {
            int e = lct.query(u, v);
            auto [U, V, W] = ed[e];
            if (W > b) {
                lct.cut(U, e);
                lct.cut(V, e);
                lct.link(u, j);
                lct.link(v, j);
            }
        }
        if (lct.connected(0, n - 1)) {
            int e = lct.query(0, n - 1);
            ans = min(ans, a + get<2>(ed[e]));
        }
        j++;
    }
    if (ans == N) {
        ans = -1;
    }
    cout << ans << endl;
    return 0;
}
