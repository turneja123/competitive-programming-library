//https://dmoj.ca/problem/ccoprep4p3
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e4 + 5;
const int INF = 1e9;

vector<pair<int, int>> dynacon[4 * N];
int val[N];
int stamp[N];
pair<int, int> edges[N];


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

Node* go[4 * N];

struct LCT {
    vector<Node> a;
    LCT(int n) {
        a.resize(4 * N);
        for (int i = 0; i < 4 * N; i++) {
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

    void link(int u, int v, int y, int wt) {
        a[y].val = wt;
        a[y].mx = wt;
        link(u, y);
        link(v, y);
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

void upd(int l, int r, int lq, int rq, pair<int, int> edge, int node) {
    if (r < lq || l > rq) {
        return;
    }
    if (l >= lq && r <= rq) {
        dynacon[node].push_back(edge);
        return;
    }
    int mid = (l + r) / 2;
    upd(l, mid, lq, rq, edge, 2 * node + 1);
    upd(mid + 1, r, lq, rq, edge, 2 * node + 2);
    return;
}

ll ans = 0;
ll mst[N];
LCT lct(N);

vector<tuple<int, int, int, int, int, int>> restore;

void dfs(int l, int r, int node, int n) {
    int ct = 0;
    for (auto [k, wt] : dynacon[node]) {
        auto [u, v] = edges[k];
        if (!lct.connected(u, v)) {
            lct.link(u, v, k + n, wt);
            ans += wt;
            restore.push_back(make_tuple(u, v, k + n, wt, -1, -1));
            ct++;
        } else {
            int j = lct.query(u, v);
            int diff = wt - lct.a[j].val;
            if (diff < 0) {
                ans += wt - lct.a[j].val;
                lct.cut(u, j);
                lct.cut(v, j);
                lct.link(u, v, k + n, wt);
                restore.push_back(make_tuple(u, v, k + n, wt, j, lct.a[j].val));
                ct++;
            }
        }

    }

    if (l == r) {
        mst[l] = ans;
    } else {
        int mid = (l + r) / 2;
        dfs(l, mid, 2 * node + 1, n);
        dfs(mid + 1, r, 2 * node + 2, n);
    }
    for (int i = 0; i < ct; i++) {
        auto [u, v, k, wt, j, jwt] = restore.back();
        ans -= wt;
        lct.cut(u, k);
        lct.cut(v, k);
        if (j != -1) {
            ans += jwt;
            lct.link(edges[j - n].first, edges[j - n].second, j, jwt);
        }

        restore.pop_back();
    }

    return;
}


int main() {
    IOS;
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < m; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        edges[i] = {u, v};
        val[i] = wt;
    }
    for (int i = 1; i <= q; i++) {
        int k, wt;
        cin >> k >> wt;
        k--;
        upd(0, q, stamp[k], i - 1, {k, val[k]}, 0);
        stamp[k] = i;
        val[k] = wt;
    }
    for (int k = 0; k < m; k++) {
        upd(0, q, stamp[k], q, {k, val[k]}, 0);
    }
    dfs(0, q, 0, n);
    for (int i = 1; i <= q; i++) {
        cout << mst[i] << endl;
    }
    return 0;
}
