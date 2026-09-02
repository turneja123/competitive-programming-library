//https://codeforces.com/contest/603/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

struct Change {
    int a, sa;
    int b, sb;
    int ans;
    Change() {}
    Change(int _a, int _sa, int _b, int _sb, int _ans) {
        a = _a;
        sa = _sa;
        b = _b;
        sb = _sb;
        ans = _ans;
    }
};

struct RollbackDSU {
    vector<int> parent;
    vector<int> sz;
    vector<Change> restore;
    int ans;
    RollbackDSU() {}
    RollbackDSU(int n) {
        init(n);
    }
    void init(int n) {
        parent.resize(n);
        sz.assign(n, 1);
        restore.clear();
        ans = n;
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    int dsu_find(int a) {
        if (parent[a] == a) {
            return a;
        }

        auto p = dsu_find(parent[a]);
        return p;
    }
    void apply(pair<int, int> e) {
        auto a = dsu_find(e.first);
        auto b = dsu_find(e.second);
        restore.push_back(Change(a, sz[a], b, sz[b], ans));
        if (a == b) {
            return;
        }
        if (sz[a] > sz[b]) {
            swap(a, b);
        }
        parent[a] = b;
        if (sz[a] % 2 == 1 && sz[b] % 2 == 1) {
            ans -= 2;
        }
        sz[b] += sz[a];
    }
    void undo() {
        Change c = restore.back();
        restore.pop_back();
        parent[c.a] = c.a;
        parent[c.b] = c.b;
        sz[c.a] = c.sa;
        sz[c.b] = c.sb;

        ans = c.ans;
    }
    int answer() {
        return ans;
    }
};

template <typename DS, typename Update>
struct PriorityUndo {
    static const int B = 4;
    static const int MAX_OP = 2 * N + 5;

    struct Node {
        Update upd;
        ll p;
        int pos;
        bool alive;
        Node() {}
        Node(Update _upd, ll _p) {
            upd = _upd;
            p = _p;
            pos = -1;
            alive = false;
        }
    };

    DS d;
    vector<Node> a;
    vector<int> st;
    vector<int> mark;
    set<pair<ll, int>> q;
    vector<int> high;
    vector<int> popped;
    int timer;

    PriorityUndo() {}
    PriorityUndo(int n) : d(n) {
        init_sets();
    }
    void init_sets() {
        q.clear();
        timer = 0;
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
        q.insert({a[id].p, id});
    }
    void erase_id(int id) {
        q.erase({a[id].p, id});
        a[id].alive = false;
    }
    void apply(Update upd, ll p) {
        int id = a.size();
        a.push_back(Node(upd, p));
        mark.push_back(0);
        push_id(id);
    }
    int get_next(set<pair<ll, int>>::iterator &it, int target) {
        while (it != q.begin()) {
            it--;
            int id = it->second;
            if (id != target) {
                return id;
            }
        }
        return -1;
    }
    int find_len(int target) {
        high.clear();
        int k = 0, need = 0;
        int mx = -1;
        int dep = depth(target);
        auto it = q.end();
        while (true) {
            k++;
            int cur = need_count(k);
            while (need < cur) {
                int id = get_next(it, target);
                if (id != -1) {
                    mx = max(mx, depth(id));
                    high.push_back(id);
                }
                need++;
            }
            if (dep < k && mx < k) {
                return k;
            }
        }
    }
    void mark_big() {
        timer++;
        for (int id : high) {
            mark[id] = timer;
        }
    }
    void undo() {
        if (q.empty()) {
            return;
        }
        int target = q.rbegin()->second;
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
        for (int i = (int)high.size() - 1; i >= 0; i--) {
            push_id(high[i]);
        }
    }
    auto answer() {
        return d.answer();
    }
};

struct PriorityRollbackDSU {
    PriorityUndo<RollbackDSU, pair<int, int>> pq;
    PriorityRollbackDSU(int n) : pq(n) {}
    void apply(int a, int b, ll p) {
        pq.apply(make_pair(a, b), p);
    }
    void undo() {
        pq.undo();
    }
    int answer() {
        return pq.answer();
    }
};

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    PriorityRollbackDSU pq(n);

    set<tuple<int, int, int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;

        ll id = (ll)wt * N + i;
        pq.apply(u, v, id);
        edges.insert({-wt, -i, u, v});

        while (pq.answer() == 0) {
            auto [wt, ind, u, v] = *edges.begin();
            pq.undo();
            if (pq.answer() != 0) {
                wt = -wt;
                ind = -ind;
                pq.apply(u, v, (ll)wt * N + ind);
                break;
            }
            edges.erase(edges.begin());
        }

        if (pq.answer() != 0) {
            cout << -1 << endl;
        } else {
            cout << -get<0>(*edges.begin()) << endl;
        }
    }

    return 0;
}
