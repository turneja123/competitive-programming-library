//https://codeforces.com/contest/2219/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


const int N = 2e5 + 5;

vector<int> adj[N];
int a[N];
int segtree[4 * N];

int mex[N];
int gain[N];
ll qans[N];
int sz[N];


int found;


int timer = 0;
ll ans = 0;

void walk(int l, int r, int node) {
    if (l == r) {
        found = l;
        return;
    }
    int mid = (l + r) / 2;
    if (segtree[2 * node + 1]) {
        walk(mid + 1, r, 2 * node + 2);
    } else {
        walk(l, mid, 2 * node + 1);
    }
}

void traverse(int l, int r, int node, int lq, int rq) {
    if (l > rq || lq > r || found != -1) {
        return;
    }
    if (l >= lq && r <= rq) {
        if (segtree[node] == 0) {
            walk(l, r, node);
        }
        return;
    }
    int mid = (l + r) / 2;
    traverse(l, mid, 2 * node + 1, lq, rq);
    traverse(mid + 1, r, 2 * node + 2, lq, rq);

}

void update(int l, int r, int ind, ll val, int node) {
    if (l == r) {
        segtree[node] = val;
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2);
    }
    segtree[node] = segtree[2 * node + 1] & segtree[2 * node + 2];
}


struct BIT {
    int n;
    vector<ll> t;
    BIT(int _n) {
        n = _n;
        t.assign(n + 1, 0);
    }
    void upd(int i, ll val) {
        i++;
        if (i <= 0) {
            return;
        }
        for (; i <= n; i += (i & -i)) {
            t[i] += val;
        }
    }
    ll query(int i) {
        ll ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans += t[i];
        }
        return ans;
    }
    ll query(int l, int r) {
        l++, r++;
        return query(r) - query(l - 1);
    }
};

vector<pair<int, int>> add_gain[N];
vector<tuple<int, int, int, int>> query_gain[N];
vector<tuple<int, int, int>> query_prdno[N];

int pos[N];
int tour[N];
vector<int> ord[N];

void dfs(int u, int p, int n) {
    pos[u] = timer;
    tour[timer++] = u;
    update(0, n,  a[u], 1, 0);

    found = -1;
    traverse(0, n, 0, 0, n);
    mex[u] = found;
    found = -1;
    sz[u] = 1;

    ord[mex[u]].push_back(u);

    if (mex[u] == n) {
        gain[u] = 1;
    } else {
        traverse(0, n, 0, mex[u] + 1, n);
        gain[u] = found - mex[u];
    }
    ans += mex[u];
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, n);
            sz[u] += sz[v];
        }
    }
    add_gain[mex[u]].push_back({gain[u], pos[u]});
    query_gain[mex[u]].push_back({a[u] - mex[u], pos[u], pos[u] + sz[u] - 1, u});


    query_prdno[a[u]].push_back({pos[u], pos[u] + sz[u] - 1, u});

    update(0, n,  a[u], 0, 0);
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        ans = 0;
        dfs(0, 0, n);

        BIT bit(n + 2);
        BIT bit_cnt(n + 2);
        for (int i = 0; i <= n; i++) {
            if (add_gain[i].empty()) {
                continue;
            }
            sort(add_gain[i].begin(), add_gain[i].end());
            sort(query_gain[i].begin(), query_gain[i].end());
            for (auto [x, j] : add_gain[i]) {
                bit_cnt.upd(j, 1);
            }
            int ptr = 0;

            for (auto [c, l, r, u] : query_gain[i]) {
                if (c < 0) {
                    continue;
                }
                while (ptr < add_gain[i].size()) {
                    auto [x, j] = add_gain[i][ptr];
                    if (x > c) {
                        break;
                    }
                    bit_cnt.upd(j, -1);
                    bit.upd(j, x);
                    ptr++;
                }
                qans[u] += bit.query(l, r) + (ll)c * bit_cnt.query(l, r);
            }
            for (int k = 0; k < ptr; k++) {
                auto [x, j] = add_gain[i][k];
                bit.upd(j, -x);
            }
            for (int k = ptr; k < add_gain[i].size(); k++) {
                auto [x, j] = add_gain[i][k];
                bit_cnt.upd(j, -1);
            }
        }


        for (int i = n; i >= 0; i--) {
            for (int u : ord[i]) {

                bit.upd(pos[u], i);
                bit_cnt.upd(pos[u], 1);
            }
            for (auto [l, r, u] : query_prdno[i]) {
                qans[u] -= bit.query(l, r) - (ll)bit_cnt.query(l, r) * i;
            }
        }

        ll best = ans;
        for (int i = 0; i < n; i++) {
            best = max(best, ans + qans[i]);
        }
        cout << best << endl;
        for (int i = 0; i <= n; i++) {
            adj[i].clear();
            query_prdno[i].clear();
            query_gain[i].clear();
            add_gain[i].clear();
            ord[i].clear();
            qans[i] = 0;
        }
        timer = 0;

    }
    return 0;
}
