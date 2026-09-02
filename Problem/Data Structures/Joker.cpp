//https://codeforces.com/contest/1386/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int INF = 1e9;

struct Change {
    int a, sa, wa;
    int b, sb, wb;
    int ans;
    Change() {}
    Change(int _a, int _sa, int _wa, int _b, int _sb, int _wb, int _ans) {
        a = _a;
        sa = _sa;
        wa = _wa;
        b = _b;
        sb = _sb;
        wb = _wb;
        ans = _ans;
    }
};

struct RollbackDSU {
    vector<int> parent;
    vector<int> sz;
    vector<int> wt;
    vector<Change> restore;
    int ans;
    RollbackDSU() {}
    RollbackDSU(int n) {
        init(n);
    }
    void init(int n) {
        parent.resize(n);
        wt.assign(n, 0);
        sz.assign(n, 1);
        restore.clear();
        ans = 1;
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    pair<int, int> dsu_find(int a) {
        if (parent[a] == a) {
            return {a, 0};
        }

        auto [p, x] = dsu_find(parent[a]);
        return {p, x ^ wt[a]};
    }
    void apply(pair<int, int> e) {
        auto [a, wa] = dsu_find(e.first);
        auto [b, wb] = dsu_find(e.second);
        restore.push_back(Change(a, sz[a], wt[a], b, sz[b], wt[b], ans));
        if (a == b) {
            int c = wa ^ wb;
            if (c == 0) {
                ans = 0;
            }
            return;
        }
        if (sz[a] > sz[b]) {
            swap(a, b);
        }
        parent[a] = b;
        sz[b] += sz[a];
        wt[a] = wa ^ wb ^ 1;
    }
    void undo() {
        Change c = restore.back();
        restore.pop_back();
        parent[c.a] = c.a;
        parent[c.b] = c.b;
        sz[c.a] = c.sa;
        sz[c.b] = c.sb;
        wt[c.a] = c.wa;
        wt[c.b] = c.wb;

        ans = c.ans;
    }
    int answer() {
        return ans;
    }
};

template <typename DS, typename Update>
struct PriorityUndo {
    static const int D = 2;
    static const int B = 4;
    static const int MAX_OP = 400000 + 5;
    static const int SHIFT = 400000 + 5;
    static const int LIM = 3 * SHIFT;

    struct FastSet {
        vector<unsigned long long> a;
        int cnt;
        int mx;
        FastSet() {}
        void init() {
            a.assign((LIM + 63) >> 6, 0);
            cnt = 0;
            mx = -1;
        }
        void insert(int x) {
            a[x >> 6] |= 1ull << (x & 63);
            cnt++;
            if (x > mx) {
                mx = x;
            }
        }
        void erase(int x) {
            a[x >> 6] &= ~(1ull << (x & 63));
            cnt--;
            if (x == mx) {
                mx = prev(x - 1);
            }
        }
        bool empty() {
            return cnt == 0;
        }
        int prev(int x) {
            if (x < 0) {
                return -1;
            }
            int b = x >> 6;
            int c = x & 63;
            unsigned long long cur;
            if (c == 63) {
                cur = a[b];
            } else {
                cur = a[b] & ((1ull << (c + 1)) - 1);
            }
            while (!cur) {
                b--;
                if (b < 0) {
                    return -1;
                }
                cur = a[b];
            }
            return (b << 6) + 63 - __builtin_clzll(cur);
        }
        int top() {
            return mx;
        }
    };

    struct Node {
        Update upd;
        ll p[D];
        int rk[D];
        int pos;
        bool alive;
        Node() {}
        Node(Update _upd, initializer_list<ll> _p) {
            upd = _upd;
            auto it = _p.begin();
            p[0] = *it;
            it++;
            p[1] = *it;
            pos = -1;
            alive = false;
        }
        Node(Update _upd, const vector<ll> &_p) {
            upd = _upd;
            p[0] = _p[0];
            p[1] = _p[1];
            pos = -1;
            alive = false;
        }
    };

    DS d;
    vector<Node> a;
    vector<int> st;
    vector<int> mark;
    vector<int> used;
    FastSet q[D];
    vector<int> id_at[D];
    vector<int> high[D];
    vector<int> ord[D];
    vector<int> popped;
    vector<int> big;
    vector<int> take;
    int timer;
    int timer_used;

    PriorityUndo() {}
    PriorityUndo(int n) : d(n) {
        init_sets();
    }
    void init_sets() {
        a.reserve(MAX_OP);
        st.reserve(MAX_OP);
        mark.reserve(MAX_OP);
        used.reserve(MAX_OP);
        popped.reserve(MAX_OP);
        big.reserve(MAX_OP);
        take.reserve(MAX_OP);
        id_at[0].assign(LIM, -1);
        id_at[1].assign(LIM, -1);
        q[0].init();
        q[1].init();
        timer = 0;
        timer_used = 0;
    }
    int get_rank(int dim, ll p) {
        if (dim == 0) {
            if (p < -INF / 2) {
                return (int)(p + INF);
            }
            return SHIFT + (int)p;
        }
        if (p < -INF / 2) {
            return SHIFT + (int)(p + INF);
        }
        return 2 * SHIFT + (int)p;
    }
    int need_count(int k) {
        return (k + B - 1) / B;
    }
    int depth(int id) {
        return (int)st.size() - 1 - a[id].pos;
    }
    void push_id(int id) {
        d.apply(a[id].upd);
        a[id].pos = st.size();
        a[id].alive = true;
        st.push_back(id);
        q[0].insert(a[id].rk[0]);
        q[1].insert(a[id].rk[1]);
    }
    void erase_id(int id) {
        q[0].erase(a[id].rk[0]);
        q[1].erase(a[id].rk[1]);
        a[id].alive = false;
    }
    void add_node(int id) {
        a[id].rk[0] = get_rank(0, a[id].p[0]);
        a[id].rk[1] = get_rank(1, a[id].p[1]);
        id_at[0][a[id].rk[0]] = id;
        id_at[1][a[id].rk[1]] = id;
        mark.push_back(0);
        used.push_back(0);
        push_id(id);
    }
    void apply(Update upd, initializer_list<ll> p) {
        int id = a.size();
        a.push_back(Node(upd, p));
        add_node(id);
    }
    void apply(Update upd, const vector<ll> &p) {
        int id = a.size();
        a.push_back(Node(upd, p));
        add_node(id);
    }
    int get_next(int dim, int &pos, int target) {
        while (true) {
            int rk = q[dim].prev(pos);
            if (rk == -1) {
                pos = -1;
                return -1;
            }
            pos = rk - 1;
            int id = id_at[dim][rk];
            if (id != target) {
                return id;
            }
        }
    }
    int find_len(int target) {
        high[0].clear();
        high[1].clear();
        int k = 0, need = 0;
        int mx[D] = {-1, -1};
        int dep = depth(target);
        int pos[D] = {q[0].top(), q[1].top()};
        while (true) {
            k++;
            int cur = need_count(k);
            while (need < cur) {
                int id = get_next(0, pos[0], target);
                if (id != -1) {
                    mx[0] = max(mx[0], depth(id));
                    high[0].push_back(id);
                }
                id = get_next(1, pos[1], target);
                if (id != -1) {
                    mx[1] = max(mx[1], depth(id));
                    high[1].push_back(id);
                }
                need++;
            }
            if (dep < k && mx[0] < k && mx[1] < k) {
                return k;
            }
        }
    }
    void mark_big() {
        timer++;
        big.clear();
        for (int dim = 0; dim < D; dim++) {
            for (int id : high[dim]) {
                if (mark[id] != timer) {
                    mark[id] = timer;
                    big.push_back(id);
                }
            }
        }
    }
    void undo(int x) {
        if (x < 0 || x >= D || q[x].empty()) {
            return;
        }
        int target = id_at[x][q[x].top()];
        int k = find_len(target);
        mark_big();

        popped.clear();
        for (int i = 0; i < k; i++) {
            int id = st.back();
            st.pop_back();
            d.undo();
            erase_id(id);
            popped.push_back(id);
        }

        for (int i = (int)popped.size() - 1; i >= 0; i--) {
            int id = popped[i];
            if (id == target || mark[id] == timer) {
                continue;
            }
            push_id(id);
        }

        ord[0].clear();
        ord[1].clear();
        for (int id : big) {
            ord[0].push_back(id);
            ord[1].push_back(id);
        }
        sort(ord[0].begin(), ord[0].end(), [&](int x, int y) {
            return a[x].rk[0] > a[y].rk[0];
        });
        sort(ord[1].begin(), ord[1].end(), [&](int x, int y) {
            return a[x].rk[1] > a[y].rk[1];
        });

        timer_used++;
        take.clear();
        int ptr[D] = {0, 0};
        int dim = x;
        while ((int)take.size() < (int)big.size()) {
            while (used[ord[dim][ptr[dim]]] == timer_used) {
                ptr[dim]++;
            }
            int id = ord[dim][ptr[dim]];
            used[id] = timer_used;
            take.push_back(id);
            dim ^= 1;
        }
        for (int i = (int)take.size() - 1; i >= 0; i--) {
            push_id(take[i]);
        }
    }
    auto answer() {
        return d.answer();
    }
};

struct PriorityRollbackDSU {
    PriorityUndo<RollbackDSU, pair<int, int>> pq;
    PriorityRollbackDSU(int n) : pq(n) {}
    void apply(int a, int b, initializer_list<ll> p) {
        pq.apply(make_pair(a, b), p);
    }
    void apply(int a, int b, const vector<ll> &p) {
        pq.apply(make_pair(a, b), p);
    }
    void undo(int x) {
        pq.undo(x);
    }
    int answer() {
        return pq.answer();
    }
};

int main() {
    IOS;
    int n, m, q;
    cin >> n >> m >> q;
    vector<pair<int, int>> edges(m);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        edges[i] = {u, v};
    }
    PriorityRollbackDSU pq(n);

    vector<int> ans(m + 1);
    int r = m - 1;
    while (r >= 0 && pq.answer() == 1) {
        auto [u, v] = edges[r];
        pq.apply(u, v, {-INF + r, -r});
        r--;
    }
    if (r == -1 && pq.answer() == 1) {
        for (int i = 0; i <= m; i++) {
            ans[i] = -1;
        }
    } else {
        ans[0] = r + 1;
        for (int i = 0; i < m; i++) {
            auto [u, v] = edges[i];
            pq.apply(u, v, {i, -INF - i});
            if (r == i - 1) {
                r++;
                pq.undo(1);
            }

            while (pq.answer() == 0 && r <= m - 1) {
                r++;
                pq.undo(1);
            }
            ans[i + 1] = r;
        }
    }
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        if (r < ans[l]) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }

    return 0;
}
