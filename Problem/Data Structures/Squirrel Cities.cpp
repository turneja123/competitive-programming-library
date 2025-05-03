//https://dmoj.ca/problem/wac4p7
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 8e5 + 5;
const int INF = 2e9;

int ptr = 0;

tuple<int, int, int> edges_added[N];
vector<tuple<int, int, int>> edges[N];
vector<pair<int, int>> queries[N];

string ans[N];

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
        a.resize(N / 2);
        for (int i = 0; i < N / 2; i++) {
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
    int comps = n;
    LCT lct(n);
    ptr = n;
    vector<pair<int, int>> compr_x, compr_y;
    vector<tuple<int, int, int, int>> edges_temp;
    vector<tuple<int, int, int>> queries_temp;
    for (int i = 0; i < m; i++) {
        int u, v, x, y;
        cin >> u >> v >> x >> y;
        u--, v--;
        if (u == v) {
            continue;
        }
        compr_x.push_back(make_pair(x, edges_temp.size()));
        compr_y.push_back(make_pair(y, edges_temp.size()));
        edges_temp.push_back(make_tuple(u, v, x, y));
    }
    m = edges_temp.size();
    for (int i = 0; i < q; i++) {
        int x, y;
        cin >> x >> y;
        compr_x.push_back(make_pair(x, m + i));
        compr_y.push_back(make_pair(y, m + i));
        queries_temp.push_back(make_tuple(x, y, i));
    }
    sort(compr_x.begin(), compr_x.end());
    sort(compr_y.begin(), compr_y.end());
    int m_x = -1, last = -INF;
    for (auto [x, i] : compr_x) {
        if (x != last) {
            last = x;
            m_x++;
        }
        if (i < m) {
            get<2>(edges_temp[i]) = m_x;
        } else {
            get<0>(queries_temp[i - m]) = m_x;
        }
    }
    m_x++;

    int m_y = -1; last = -INF;
    for (auto [y, i] : compr_y) {
        if (y != last) {
            last = y;
            m_y++;
        }
        if (i < m) {
            get<3>(edges_temp[i]) = m_y;
        } else {
            get<1>(queries_temp[i - m]) = m_y;
        }
    }
    m_y++;
    for (auto [u, v, x, y] : edges_temp) {
        edges[x].push_back(make_tuple(u, v, y));
    }
    for (auto [x, y, ind] : queries_temp) {
        queries[x].push_back(make_pair(y, ind));
    }
    multiset<int> mst;
    for (int i = m_x - 1; i >= 0; i--) {
        for (auto [u, v, y] : edges[i]) {
            if (!lct.connected(u, v)) {
                lct.link(u, v, y);
                comps--;
                mst.insert(y);
            } else {
                int j = lct.query(u, v);
                if (get<2>(edges_added[j]) > y) {
                    mst.erase(mst.find(get<2>(edges_added[j])));
                    lct.cut(get<0>(edges_added[j]), j);
                    lct.cut(get<1>(edges_added[j]), j);
                    lct.link(u, v, y);
                    mst.insert(y);
                }
            }
        }
        for (auto [y, j] : queries[i]) {
            if (mst.size() && *mst.rbegin() <= y && comps == 1) {
                ans[j] = "YES";
            } else {
                ans[j] = "NO";
            }
        }
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
