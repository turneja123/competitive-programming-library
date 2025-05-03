//https://dmoj.ca/problem/ioi11p5io
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 6e5 + 5;
const int INF = 2e9 + 5;

int x[N];
int id[N];

bool is_white(int i) {
    return i < 2 || i % 2 == 1;
}

struct Node {
    Node* l = nullptr;
    Node* r = nullptr;
    Node* p = nullptr;
    int i;
    int val;
    int sum;
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
        sum = val + (l ? l->sum : 0) + (r ? r->sum : 0);
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
            if (is_white(i)) {
                a[i].val = 0;
            } else {
                a[i].val = 1;
            }
            a[i].sum = a[i].val;
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

    void cut(int u, int v) {
		make_root(u);
		access(v);
		if (a[v].l) {
			a[v].l->p = nullptr;
			a[v].l = nullptr;
		}
	}

    void upd(int u, int x) {
        access(u);
        a[u].val = x;
        a[u].pull();
    }

    long long query(int u, int v) {
        make_root(u);
        access(v);
        return a[v].sum;
    }
};

struct comp {
    bool operator() (pair<int, int> a, pair<int, int> b) const {
        if (a.first != b.first) {
            return a.first < b.first;
        }
        if (is_white(a.second)) {
            return false;
        }
        if (is_white(b.second)) {
            return true;
        }
        return a.second < b.second;
    }
};

LCT lct(N);
set<pair<int, int>, comp> st;

void add(int i, int x, int l) {
    lct.link(2 * i, 2 * i + 1);
    st.insert(make_pair(x, 2 * i));
    auto la = st.lower_bound(make_pair(x, 2 * i));
    la--;
    auto ra = st.upper_bound(make_pair(x, 2 * i));
    if (is_white(la->second)) {
        lct.cut(la->second, ra->second);
        lct.link(la->second, 2 * i);
    }
    st.insert(make_pair(x + l, 2 * i + 1));
    la = st.lower_bound(make_pair(x + l, 2 * i + 1));
    la--;
    ra = st.upper_bound(make_pair(x + l, 2 * i + 1));
    if (is_white(la->second)) {
        lct.cut(la->second, ra->second);
        lct.link(la->second, 2 * i + 1);
    }
    lct.link(2 * i + 1, ra->second);
    return;
}

void rem(int i, int x, int l) {
    lct.cut(2 * i, 2 * i + 1);
    st.erase(make_pair(x, 2 * i));
    auto la = st.lower_bound(make_pair(x, 2 * i));
    la--;
    auto ra = st.lower_bound(make_pair(x, 2 * i));
    if (is_white(la->second)) {
        lct.cut(la->second, 2 * i);
        lct.link(la->second, ra->second);
    }
    st.erase(make_pair(x + l, 2 * i + 1));
    la = st.lower_bound(make_pair(x + l, 2 * i + 1));
    la--;
    ra = st.lower_bound(make_pair(x + l, 2 * i + 1));
    lct.cut(2 * i + 1, ra->second);
    if (is_white(la->second)) {
        lct.cut(la->second, 2 * i + 1);
        lct.link(la->second, ra->second);
    }
    return;

}

int main() {
    IOS;
    int n, m, l;
    cin >> n >> l >> m;
    assert(l != 0);
    map<int, set<int>> mp;
    map<int, int> active;
    st.insert(make_pair(-INF, 0));
    st.insert(make_pair(INF, 1));
    lct.link(0, 1);
    for (int i = 0; i < n; i++) {
        id[i] = i + 1;
        cin >> x[i];
        mp[x[i]].insert(id[i]);
        if (mp[x[i]].size() == 1) {
            active[x[i]] = id[i];
            add(id[i], x[i], l);
        }
    }
    int j = n + 1;
    for (int q = 0; q < m; q++, j++) {
        int i, y;
        cin >> i >> y;
        mp[x[i]].erase(id[i]);
        if (active[x[i]] == id[i]) {
            rem(id[i], x[i], l);
            if (mp[x[i]].size() > 0) {
                int j = *mp[x[i]].begin();
                active[x[i]] = j;
                add(j, x[i], l);
            }
        }
        x[i] = y;
        mp[x[i]].insert(id[i]);
        if (mp[x[i]].size() == 1) {
            active[x[i]] = id[i];
            add(id[i], x[i], l);
        }
        cout << lct.query(0, 1) << endl;
    }
    return 0;
}
