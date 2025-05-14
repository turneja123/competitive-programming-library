//https://cses.fi/problemset/task/3408/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 7e5 + 5;
const int INF = 2e9;

int ptr = 0;

tuple<int, int, int> edges_added[N];

int parent[N];
int sz[N];

int dsu_find(int a) {
    if (parent[a] == a) {
        return a;
    }
    return parent[a] = dsu_find(parent[a]);
}

void dsu_unite(int a, int b) {
    if (sz[b] > sz[a]) {
        swap(a, b);
    }
    sz[a] += sz[b];
    parent[b] = a;
}

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
    int n, m, q;
    cin >> n >> m >> q;
    LCT lct(n);
    vector<tuple<int, int, int, int>> edges, edges_unsorted;
    vector<bool> mst(m, false);
    for (int i = 0; i < m; i++) {
        int u, v, y;
        cin >> u >> v >> y;
        u--, v--;
        edges.push_back(make_tuple(y, u, v, i));
    }
    edges_unsorted = edges;
    sort(edges.begin(), edges.end());
    ptr = n;
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
    for (auto [y, u, v, i] : edges) {
        int a = dsu_find(u), b = dsu_find(v);
        if (a != b) {
            dsu_unite(a, b);
            lct.link(u, v, y);
            mst[i] = true;
        }
    }
    while (q--) {
        int k;
        cin >> k;
        vector<tuple<int, int, int, int>> edges_set(k);
        for (int j = 0; j < k; j++) {
            int i;
            cin >> i;
            i--;
            edges_set[j] = edges_unsorted[i];
        }
        sort(edges_set.begin(), edges_set.end());
        string ans = "YES";
        vector<tuple<int, int, int>> restore;
        for (auto [y, u, v, i] : edges_set) {
            if (mst[i]) {
                int j = lct.query(u, v);
                lct.cut(u, j);
                lct.cut(v, j);
                lct.link(u, v, 0);
                restore.push_back(edges_added[j]);
                restore.push_back(make_tuple(u, v, -1));
                continue;
            }
        }
        for (auto [y, u, v, i] : edges_set) {
            if (mst[i]) {
                continue;
            }
            int j = lct.query(u, v);
            if (get<2>(edges_added[j]) < y) {
                ans = "NO";
                break;
            }
            lct.cut(get<0>(edges_added[j]), j);
            lct.cut(get<1>(edges_added[j]), j);
            lct.link(u, v, y);
            restore.push_back(edges_added[j]);
            restore.push_back(make_tuple(u, v, -1));
        }
        if (restore.size()) {
            reverse(restore.begin(), restore.end());
        }
        for (int i = 0; i < restore.size(); i++) {
            auto [u, v, y] = restore[i];
            if (i % 2 == 0) {
                int j = lct.query(u, v);
                lct.cut(u, j);
                lct.cut(v, j);
            } else {
                assert(!lct.connected(u, v));
                lct.link(u, v, y);
            }
        }
        cout << ans << endl;
    }
    return 0;
}
