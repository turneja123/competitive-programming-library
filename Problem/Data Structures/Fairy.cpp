//https://codeforces.com/contest/19/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

vector<pair<int, int>> segtree[4 * N];
vector<int> answer;

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

void upd(int l, int r, int lq, int rq, pair<int, int> edge, int node) {
    if (r < lq || l > rq) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[node].push_back(edge);
        return;
    }
    int mid = (l + r) / 2;
    upd(l, mid, lq, rq, edge, 2 * node + 1);
    upd(mid + 1, r, lq, rq, edge, 2 * node + 2);
    return;
}

void dfs(int l, int r, int node, RollbackDSU &dsu) {
    int ct = 0;
    for (auto [u, v] : segtree[node]) {
        dsu.apply(make_pair(u, v));
        ct++;
    }
    if (l == r) {
        if (dsu.answer()) {
            answer.push_back(l + 1);
        }
    } else {
        int mid = (l + r) / 2;
        dfs(l, mid, 2 * node + 1, dsu);
        dfs(mid + 1, r, 2 * node + 2, dsu);
    }
    for (int i = 0; i < ct; i++) {
        dsu.undo();
    }
    return;
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (i != 0) {
            upd(0, m - 1, 0, i - 1, make_pair(u, v), 0);
        }
        if (i != m - 1) {
            upd(0, m - 1, i + 1, m - 1, make_pair(u, v), 0);
        }
    }
    if (m == 0) {
        cout << 0 << endl << endl;
        return 0;
    }

    RollbackDSU dsu(n);
    dfs(0, m - 1, 0, dsu);
    cout << answer.size() << endl;
    for (int x : answer) {
        cout << x << " ";
    }

    return 0;
}
