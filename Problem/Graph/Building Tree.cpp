//https://codeforces.com/contest/2222/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

int parent[N];
int sz[N];

int leader[N];
int sz_c[N];
int parent_c[N];

vector<pair<int, int>> segtree[4 * N];
vector<tuple<int, int, int, int, int, int>> restore;
int comps;
ll ans;

int dsu_find(int a, int *par) {
    if (par[a] == a) {
        return a;
    }
    return dsu_find(par[a], par);
}

void dsu_unite_c(int a, int b) {
    if (sz_c[b] > sz_c[a]) {
        swap(a, b);
    }
    sz_c[a] += sz_c[b];
    parent_c[b] = a;
}

void dsu_unite(int a, int b, int cost) {
    if (sz[b] > sz[a]) {
        swap(a, b);
    }
    sz[a] += sz[b];
    if (leader[a] == -1) {
        leader[a] = leader[b];
    } else if (leader[b] != -1) {
        int A = dsu_find(leader[a], parent_c);
        int B = dsu_find(leader[b], parent_c);
        if (A != B) {
            comps--;
            dsu_unite_c(A, B);
            ans += cost;
        }
    }

    parent[b] = a;
}

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

void dfs(int l, int r, int node) {
    int ct = 0;

    for (auto [u, v] : segtree[node]) {
        int x = dsu_find(u, parent), y = dsu_find(v, parent);
        if (x != y) {
            restore.push_back(make_tuple(x, sz[x], leader[x], y, sz[y], leader[y]));
            dsu_unite(x, y, l);
            ct++;
        }
    }
    if (l == r) {

    } else {
        int mid = (l + r) / 2;
        dfs(l, mid, 2 * node + 1);
        dfs(mid + 1, r, 2 * node + 2);
    }
    for (int i = 0; i < ct; i++) {
        auto [u, su, lu, v, sv, lv] = restore.back();
        parent[u] = u;
        parent[v] = v;
        sz[u] = su;
        sz[v] = sv;
        leader[u] = lu;
        leader[v] = lv;
        restore.pop_back();
    }
    return;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m, q;
        cin >> n >> m >> q;
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            sz[i] = 1;

            parent_c[i] = i;
            sz_c[i] = 1;
            leader[i] = -1;
        }
        for (int i = 0; i < m; i++) {
            int u, v, wt;
            cin >> u >> v >> wt;
            u--, v--;
            if (wt != 0) {
                upd(0, m + 1, 0, wt - 1, {u, v}, 0);
            }
            upd(0, m + 1, wt + 1, m + 1, {u, v}, 0);
        }
        comps = 0;
        for (int i = 0; i < q; i++) {
            int c;
            cin >> c;
            c--;
            if (leader[c] == -1) {
                comps++;
            }
            leader[c] = c;
        }
        ans = 0;
        dfs(0, m + 1, 0);
        if (comps > 1) {
            cout << -1 << endl;
        } else {
            cout << ans << endl;
        }
        for (int i = 0; i <= 4 * m + 5; i++) {
            segtree[i].clear();
        }
    }

    return 0;
}
