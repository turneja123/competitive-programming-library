//https://dmoj.ca/problem/mockccc15s5
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int INF = 1e9;
const int SQ = 100;

int a_init[N];

struct Node {
    Node* l = nullptr;
    Node* r = nullptr;
    Node* p = nullptr;
    int i;
    int val;
    int mn;
    int ct;
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
		if (lazy_inc) {
            val += lazy_inc;
            mn += lazy_inc;

            if (l) {
                l->lazy_inc += lazy_inc;
            }
            if (r) {
                r->lazy_inc += lazy_inc;
            }
		}
		lazy_inc = 0;
	}
	void pull() {
	    if (l) {
            l->push();
	    }
	    if (r) {
            r->push();
	    }
        mn = min({val, (l ? l->mn : INF), (r ? r->mn : INF)});
        ct = (val == mn ? 1 : 0) + (l ? (l->mn == mn ? l->ct : 0) : 0) + (r ? (r->mn == mn ? r->ct : 0) : 0) ;
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
            a[i].mn = a_init[i];
            a[i].val = a_init[i];
            a[i].ct = 1;
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

    void upd(int u, int v, int x) {
        make_root(u);
        access(v);
        a[v].lazy_inc += x;

        make_root(root);
    }

    int query(int u, int v) {
        make_root(u);
        access(v);
        int ans = (a[v].mn == 0 ? a[v].ct : 0);
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

vector<pair<int, int>> edges[N];
vector<pair<int, int>> queries[N];

int outs[N];
int seen[N];
bool vis[N];
int tin[N];
int low[N];

vector<pair<int, int>> adj[N];
int timer = 0;
int bridges = 0;

void dfs(int v, int p) {
    vis[v] = true;
    tin[v] = low[v] = timer++;
    for (auto [u, e] : adj[v]) {
        if (e == p) {
            continue;
        }
        if (vis[u]) {
            low[v] = min(low[v], tin[u]);
        } else {
            dfs(u, e);
            low[v] = min(low[v], low[u]);
            if (low[u] > tin[v]) {
                bridges++;
            }
        }
    }
}


int solve(int x, int y) {
    vector<int> nodes;
    int e = 0;
    for (auto [u, v] : edges[x]) {
        adj[u].push_back({v, e});
        adj[v].push_back({u, e});
        if (!seen[u]) {
            seen[u] = 1;
            nodes.push_back(u);
        }
        if (!seen[v]) {
            seen[v] = 1;
            nodes.push_back(v);
        }
        e++;
    }
    for (auto [u, v] : edges[y]) {
        adj[u].push_back({v, e});
        adj[v].push_back({u, e});
        if (!seen[u]) {
            seen[u] = 1;
            nodes.push_back(u);
        }
        if (!seen[v]) {
            seen[v] = 1;
            nodes.push_back(v);
        }
        e++;
    }
    for (int v : nodes) {
        if (!vis[v]) {
            dfs(v, -1);
        }
    }
    for (int v : nodes) {
        adj[v].clear();
        vis[v] = 0;
        seen[v] = 0;
    }
    int ans = bridges;
    timer = 0;
    bridges = 0;
    return ans;
}

int main() {
    IOS;
    int n, m, t;
    cin >> n >> m >> t;
    for (int i = 0; i < n; i++) {
        a_init[i] = INF;
    }
    for (int i = n; i < 2 * n; i++) {
        a_init[i] = 0;
    }
    vector<int> u(t + 1);
    for (int i = 0; i <= t; i++) {
        cin >> u[i];
        u[i]--;
    }
    for (int i = 0; i < m; i++) {
        int k;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            edges[i].push_back({u, v});
        }
    }
    map<pair<int, int>, int> mp;
    for (int i = 0; i < t; i++) {
        int x = u[i], y = u[i + 1];
        if (edges[y].size() > edges[x].size()) {
            swap(x, y);
        }
        if (edges[y].size() > SQ || edges[x].size() < 500) {
            int l = min(x, y), r = max(x, y);
            auto it = mp.find({l, r});
            if (it != mp.end()) {
                outs[i] = it->second;
                continue;
            }

            outs[i] = solve(x, y);
            mp[{l, r}] = outs[i];
            continue;
        }
        queries[x].push_back({y, i});
    }
    int ans = n, e = 0;
    LCT lct(2 * n, 0);

    vector<tuple<int, int, int, int>> restore;
    for (int i = 0; i < m; i++) {
        if (queries[i].empty()) {
            continue;
        }
        for (auto [u, v] : edges[i]) {
            if (!lct.connected(u, v)) {
                restore.push_back({u, v, e, ans});
                lct.link(u, n + e);
                lct.link(v, n + e);
                e++;
            } else {
                restore.push_back({u, v, -1, ans});
                ans -= lct.query(u, v);
                lct.upd(u, v, 1);
            }
        }
        int ptr = restore.size();
        for (auto [j, ind] : queries[i]) {
            int l = min(i, j), r = max(i, j);
            auto it = mp.find({l, r});
            if (it != mp.end()) {
                outs[ind] = it->second;
                continue;
            }

            for (auto [u, v] : edges[j]) {
                if (!lct.connected(u, v)) {
                    restore.push_back({u, v, e, ans});
                    lct.link(u, n + e);
                    lct.link(v, n + e);
                    e++;
                } else {
                    restore.push_back({u, v, -1, ans});
                    ans -= lct.query(u, v);
                    lct.upd(u, v, 1);
                }
            }
            outs[ind] = ans - (n - e);
            mp[{l, r}] = outs[ind];
            while (restore.size() > ptr) {
                auto [u, v, E, ANS] = restore.back();
                if (E == -1) {
                    lct.upd(u, v, -1);
                    ans = ANS;
                } else {
                    lct.cut(u, n + E);
                    lct.cut(v, n + E);
                    e = E;
                    ans = ANS;
                }
                restore.pop_back();
            }
        }
        while (restore.size()) {
            auto [u, v, E, ANS] = restore.back();
            if (E == -1) {
                lct.upd(u, v, -1);
                ans = ANS;
            } else {
                lct.cut(u, n + E);
                lct.cut(v, n + E);
                e = E;
                ans = ANS;
            }
            restore.pop_back();
        }
    }
    for (int i = 0; i < t; i++) {
        cout << outs[i] << endl;
    }

    return 0;
}
