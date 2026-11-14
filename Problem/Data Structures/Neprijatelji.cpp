//https://evaluator.hsin.hr/events/coci27_2/tasks/HONI262727neprijatelji/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const ll INF = 1e16;

ll a_init[N];
vector<int> adj[N];
int parent[N];

struct Mat {
    ll a[3][3];
};

Mat combine(const Mat &A, const Mat &B) {
    Mat C;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            C.a[i][j] = max({A.a[i][0] + B.a[0][j], A.a[i][1] + B.a[1][j], A.a[i][2] + B.a[2][j], -INF});
        }
    }
    return C;
}

struct Node {
    Node* l = nullptr;
    Node* r = nullptr;
    Node* p = nullptr;
    int i;
    ll val;
    ll vd = 0;
    ll vb = 0;
    ll mx = 0;
    multiset<ll> vir;
    Mat m;
    Node() {}
    Node(int x) {
        i = x;
    }
    void pull() {
        ll x = val + vd, y = vb, z = vb + mx;
        if (l) {
            for (int k = 0; k < 3; k++) {
                m.a[k][0] = l->m.a[k][1] + y;
                m.a[k][1] = max(l->m.a[k][1] + z, l->m.a[k][2] + y);
                m.a[k][2] = max(l->m.a[k][0] + x, -INF);
            }
            if (r) {
                m = combine(m, r->m);
            }
        } else if (r) {
            for (int k = 0; k < 3; k++) {
                m.a[0][k] = max(x + r->m.a[2][k], -INF);
                m.a[1][k] = max(y + r->m.a[0][k], z + r->m.a[1][k]);
                m.a[2][k] = y + r->m.a[1][k];
            }
        } else {
            m.a[0][0] = -INF, m.a[0][1] = -INF, m.a[0][2] = x;
            m.a[1][0] = y, m.a[1][1] = z, m.a[1][2] = -INF;
            m.a[2][0] = -INF, m.a[2][1] = y, m.a[2][2] = -INF;
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
            a[i].val = a_init[i];
            a[i].pull();
        }
    }
    void add(Node* p, Node* c, int s) {
        ll x = max(c->m.a[0][1], c->m.a[0][2]);
        ll y = max(c->m.a[1][1], c->m.a[1][2]);
        ll z = max(c->m.a[2][1], c->m.a[2][2]);
        p->vd += s * z;
        p->vb += s * y;
        if (x > y) {
            if (s == 1) {
                p->vir.insert(x - y);
            } else {
                p->vir.erase(p->vir.find(x - y));
            }
            p->mx = (p->vir.size() ? *p->vir.rbegin() : 0);
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
                add(p, p->r, 1);
            }
            if (last) {
                add(p, last, -1);
            }
            p->r = last;

            p->pull();
            last = p;
        }
        splay(c);
        c->pull();
        return last;
    }

    void link(int u, int v) {
        access(u);
        access(v);
        a[u].p = &a[v];
        add(&a[v], &a[u], 1);
        a[v].pull();
    }

    void upd(int u, ll x) {
        access(u);
        a[u].val = x;
        a[u].pull();
    }

    ll query(int v) {
        Node* c = &a[v];
        splay(c);
        c->pull();
        ll x = -INF, y = 0, z = 0;
        if (c->r) {
            x = max(c->r->m.a[0][1], c->r->m.a[0][2]);
            y = max(c->r->m.a[1][1], c->r->m.a[1][2]);
            z = max(c->r->m.a[2][1], c->r->m.a[2][2]);
        }
        return max({c->val + c->vd + z, c->vb + x, c->vb + c->mx + y});
    }
};

void dfs(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            parent[v] = u;
            dfs(v, u);
        }
    }
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a_init[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, 0);
    LCT lct(n);
    for (int i = 1; i < n; i++) {
        lct.link(i, parent[i]);
    }

    for (int i = 0; i < q; i++) {
        int t, u;
        cin >> t >> u;
        u--;
        if (t == 1) {
            ll x;
            cin >> x;
            lct.upd(u, x);
        } else {
            cout << lct.query(u) << endl;
        }
    }
    return 0;
}
