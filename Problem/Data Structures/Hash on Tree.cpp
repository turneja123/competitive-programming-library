//https://atcoder.jp/contests/abc351/tasks/abc351_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const ll M = 998244353;

ll modPow(ll a, ll y) {
    ll res = 1;
    while (y > 0) {
        if (y % 2 != 0) {
            res = res * a % M;
        }
        y /= 2;
        a = a * a % M;
    }
    return res;
}

struct Node {
    Node* l = nullptr;
    Node* r = nullptr;
    Node* p = nullptr;
    int i;
    int deg;
    int zero;
    ll val;
    ll vir;
    ll add;
    ll mul;
    Node() {}
    Node(int x) {
        i = x;
    }
    ll coef() {
        if (deg == 0 || zero) {
            return 0;
        }
        return vir;
    }
    void pull() {
        add = val;
        mul = coef();
        if (r) {
            add = (add + mul * r->add) % M;
            mul = mul * r->mul % M;
        }
        if (l) {
            add = (l->add + l->mul * add) % M;
            mul = l->mul * mul % M;
        }
    }
    bool is_root() {
        return p == 0 || (p->l != this && p->r != this);
    }
};

struct LCT {
    vector<Node> a;
    LCT(int n, vector<int> &par, vector<int> &deg, vector<int> &zero, vector<ll> &val, vector<ll> &prod) {
        a.resize(n);
        for (int i = 0; i < n; i++) {
            a[i].i = i;
            a[i].deg = deg[i];
            a[i].zero = zero[i];
            a[i].val = val[i];
            a[i].vir = prod[i];
            a[i].pull();
        }
        for (int i = 1; i < n; i++) {
            a[i].p = &a[par[i]];
        }
    }

    ll get(Node* c) {
        return (c->add + c->mul) % M;
    }

    void add_vir(Node* c, ll x) {
        if (x == 0) {
            c->zero++;
        } else {
            c->vir = c->vir * x % M;
        }
    }

    void rem_vir(Node* c, ll x) {
        if (x == 0) {
            c->zero--;
        } else {
            c->vir = c->vir * modPow(x, M - 2) % M;
        }
    }

    void rot(Node* c) {
        Node* p = c->p;
        Node* g = p->p;

        if (!p->is_root()) {
            (g->r == p ? g->r : g->l) = c;
        }

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
    }

    Node* access(int v) {
        Node* last = nullptr;
        Node* c = &a[v];
        for (Node* p = c; p; p = p->p) {
            splay(p);
            if (p->r) {
                add_vir(p, get(p->r));
            }
            if (last) {
                rem_vir(p, get(last));
            }
            p->r = last;
            if (last) {
                last->p = p;
            }
            p->pull();
            last = p;
        }
        splay(c);
        return last;
    }

    ll upd(int u, ll x) {
        access(u);
        a[u].val = x;
        a[u].pull();
        return get(&a[u]);
    }
};

int main() {
    IOS;
    int n, q;
    cin >> n >> q;

    vector<int> par(n, -1), deg(n, 0), zero(n, 0);
    vector<ll> val(n), prod(n, 1), f(n);

    for (int i = 1; i < n; i++) {
        cin >> par[i];
        par[i]--;
        deg[par[i]]++;
    }

    for (int i = 0; i < n; i++) {
        cin >> val[i];
    }

    for (int i = n - 1; i >= 0; i--) {
        f[i] = val[i];
        if (deg[i]) {
            f[i] = (f[i] + (zero[i] ? 0 : prod[i])) % M;
        }
        if (i) {
            if (f[i] == 0) {
                zero[par[i]]++;
            } else {
                prod[par[i]] = prod[par[i]] * f[i] % M;
            }
        }
    }

    LCT lct(n, par, deg, zero, val, prod);

    while (q--) {
        int v;
        ll x;
        cin >> v >> x;
        v--;
        cout << lct.upd(v, x) << endl;
    }

    return 0;
}
