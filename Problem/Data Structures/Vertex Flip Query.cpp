//https://atcoder.jp/contests/abc460/tasks/abc460_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 6e5 + 5;
const ll INF = 1e16;

ll a_init[N];

struct Node {
    Node* l = nullptr;
    Node* r = nullptr;
    Node* p = nullptr;
    int i;
    long long val;
    long long sum;
    long long vir;
    long long pref;
    long long suf;
    bool rev = false;
    Node() {}
    Node(int x) {
        i = x;
    }
    void revnode() {
        rev ^= true;
        swap(l, r);
        swap(pref, suf);
    }
    void push() {
		if (rev) {
			rev = false;
			if (l) {
                l->revnode();
			}
			if (r) {
                r->revnode();
			}
		}
	}
	void pull() {
        long long mid = val + vir;
        sum = mid;
        pref = mid;
        suf = mid;
        if (l) {
            sum += l->sum;
            pref = max(l->pref, l->sum + mid);
            suf = max(mid, mid + l->suf);
        }
        if (r) {
            pref = max(pref, sum + r->pref);
            suf = max(r->suf, r->sum + suf);
            sum += r->sum;
        }
        sum = max(sum, -INF);
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
            a[i].pref = a_init[i];
            a[i].suf = a_init[i];
            a[i].vir = 0;
        }
    }
    long long get(Node* c) {
        return c ? max(0LL, c->pref) : 0;
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
                p->vir += get(p->r);
            }
            if (last) {
                p->vir -= get(last);
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
            c->l->revnode();
            c->vir += get(c->l);
            c->l = nullptr;
        }
        c->pull();
    }

    void link(int u, int v) {
        make_root(u);
        access(v);
        a[u].p = &a[v];
        a[v].vir += get(&a[u]);
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

    void upd(int u, ll x) {
        access(u);
        a[u].val += x;
        a[u].pull();
    }

    long long query(int v) {
        make_root(v);
        return a[v].val + a[v].vir;
    }
};

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    vector<ll> w(n, 0), c(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
        a_init[i] = w[i];
        a_init[i + n] = -INF;
    }
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        if (c[i] == 1) {
            a_init[i] = -INF;
            a_init[i + n] = w[i];
        }
    }
    LCT lct(2 * n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        lct.link(u, v);
        lct.link(u + n, v + n);
    }


    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int u;
            cin >> u;
            u--;
            if (c[u] == 0) {
                lct.upd(u, -INF - w[u]);
                lct.upd(u + n, INF + w[u]);
            } else {
                lct.upd(u + n, -INF - w[u]);
                lct.upd(u, INF + w[u]);
            }
            c[u] ^= 1;
        } else if (t == 2) {
            int u; ll add;
            cin >> u >> add;
            u--;
            if (c[u] == 0) {
                lct.upd(u, add);
            } else {
                lct.upd(u + n, add);
            }
            w[u] += add;
        } else {
            int u;
            cin >> u;
            u--;
            if (c[u] == 0) {
                cout << lct.query(u) << endl;
            } else {
                cout << lct.query(u + n) << endl;
            }
        }
    }

    return 0;
}
