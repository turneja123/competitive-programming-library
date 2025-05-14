//https://codeforces.com/contest/2097/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const int INF = 2e9 + 5;

int x[N];
int id[N];
int val[N];
vector<int> pos[N];

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

Node* go[N];

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

void add(int i, int x, int l, LCT &lct, set<pair<int, int>, comp> &st) {
    lct.link(2 * i, 2 * i + 1);
    auto la = st.insert(make_pair(x, 2 * i)).first;
    la--;
    auto ra = la;
    ra++, ra++;
    if (is_white(la->second)) {
        lct.cut(la->second, ra->second);
        lct.link(la->second, 2 * i);
    }
    la = st.insert(make_pair(x + l, 2 * i + 1)).first;
    la--;
    ra = la;
    ra++, ra++;
    if (is_white(la->second)) {
        lct.cut(la->second, ra->second);
        lct.link(la->second, 2 * i + 1);
    }
    lct.link(2 * i + 1, ra->second);
    return;
}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, l;
        cin >> n >> l;
        l--;
        LCT lct(2 * n + 5);
        set<pair<int, int>, comp> st;
        st.insert(make_pair(-INF, 0));
        st.insert(make_pair(INF, 1));
        lct.link(0, 1);
        vector<pair<int, int>> compr;
        for (int i = 0; i < n; i++) {
            id[i] = i + 1;
            cin >> x[i];
            compr.push_back(make_pair(x[i], i));
        }
        sort(compr.begin(), compr.end());
        int last = -1, m = -1;
        for (int i = 0; i < n; i++) {
            if (last != compr[i].first) {
                last = compr[i].first;
                m++;
                val[m] = compr[i].first;
            }
            x[compr[i].second] = m;
        }
        m++;
        for (int i = 0; i < n; i++) {
            pos[x[i]].push_back(i);
        }
        long long ans = 0;
        for (int i = m - 1; i >= 0; i--) {
            for (int j : pos[i]) {
                add(id[j], j, l, lct, st);
            }
            int diff = val[i] - (i == 0 ? 0 : val[i - 1]);
            ans += (long long)diff * lct.query(0, 1);
        }
        cout << ans << endl;
        for (int i = 0; i < n; i++) {
            pos[x[i]].clear();
        }

    }
    return 0;
}
