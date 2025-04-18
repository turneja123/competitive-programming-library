//https://arena.petlja.org/sr-Latn-RS/competition/bubblecup17finals#tab_136694
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const int SQ = 600;

int parent[N];
int sz[N];
int ans[N];

vector<pair<int, int>> segtree[4 * N];
vector<tuple<int, int, int, int>> restore;
vector<tuple<int, int, int, int, int>> buf;
pair<vector<tuple<int, int, int, int, int>>, vector<tuple<int, int, int, int, int>>> sweep[N];
vector<tuple<int, int, int, int>> leaf[N];

int dsu_find(int a) {
    while (parent[a] != a) {
        a = parent[a];
    }
    return a;
}

void dsu_unite(int a, int b) {
    if (sz[b] > sz[a]) {
        swap(a, b);
    }
    sz[a] += sz[b];
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
        int x = dsu_find(u), y = dsu_find(v);
        if (x != y) {
            restore.push_back(make_tuple(x, sz[x], y, sz[y]));
            dsu_unite(x, y);
            ct++;
        }
    }
    if (l == r) {
        for (auto [wt, u, v, ind] : leaf[l]) {
            int ct_leaf = 0;
            for (auto [WT, U, V, L, R] : buf) {
                if (WT >= wt && l >= L && l <= R) {
                    int x = dsu_find(U), y = dsu_find(V);
                    if (x != y) {
                        restore.push_back(make_tuple(x, sz[x], y, sz[y]));
                        dsu_unite(x, y);
                        ct_leaf++;
                    }
                }
            }
            ans[ind] = dsu_find(u) == dsu_find(v);
            for (int i = 0; i < ct_leaf; i++) {
                auto [u, su, v, sv] = restore.back();
                parent[u] = u;
                parent[v] = v;
                sz[u] = su;
                sz[v] = sv;
                restore.pop_back();
            }
        }
        leaf[l].clear();
    } else {
        int mid = (l + r) / 2;
        dfs(l, mid, 2 * node + 1);
        dfs(mid + 1, r, 2 * node + 2);
    }
    for (int i = 0; i < ct; i++) {
        auto [u, su, v, sv] = restore.back();
        parent[u] = u;
        parent[v] = v;
        sz[u] = su;
        sz[v] = sv;
        restore.pop_back();
    }
    return;
}

int main() {
    IOS;
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
    set<int> st_x, st_y;
    map<int, int> mp_x, mp_y;
    vector<tuple<int, int, int, int, int>> edges;
    vector<tuple<int, int, int, int, int>> queries;
    for (int i = 0; i < m; i++) {
        int u, v, wt, l, r;
        cin >> u >> v >> wt >> l >> r;
        u--, v--;
        st_x.insert(wt);
        st_y.insert(l);
        st_y.insert(r);
        edges.push_back(make_tuple(wt, u, v, l, r));
    }
    for (int i = 0; i < q; i++) {
        int u, v, wt, t;
        cin >> u >> v >> wt >> t;
        u--, v--;
        st_x.insert(wt);
        st_y.insert(t);
        queries.push_back(make_tuple(wt, u, v, t, i));
    }
    int j_x = 0;
    for (int x : st_x) {
        mp_x[x] = j_x++;
    }
    int j_y = 0;
    for (int y : st_y) {
        mp_y[y] = j_y++;
    }

    for (int i = 0; i < m; i++) {
        get<0>(edges[i]) = mp_x[get<0>(edges[i])];
        get<3>(edges[i]) = mp_y[get<3>(edges[i])];
        get<4>(edges[i]) = mp_y[get<4>(edges[i])];
        sweep[get<0>(edges[i])].first.push_back(edges[i]);
    }
    for (int i = 0; i < q; i++) {
        get<0>(queries[i]) = mp_x[get<0>(queries[i])];
        get<3>(queries[i]) = mp_y[get<3>(queries[i])];
        sweep[get<0>(queries[i])].second.push_back(queries[i]);
    }
    for (int w = j_x - 1; w >= 0; w--) {
        if (sweep[w].first.size() > SQ) {
            dfs(0, j_y - 1, 0);
            for (auto [_, u, v, l, r] : buf) {
                upd(0, j_y - 1, l, r, make_pair(u, v), 0);
            }
            for (auto [_, u, v, l, r] : sweep[w].first) {
                upd(0, j_y - 1, l, r, make_pair(u, v), 0);
            }
            buf.clear();
            for (auto [wt, u, v, t, ind] : sweep[w].second) {
                leaf[t].push_back(make_tuple(wt, u, v, ind));
            }
            dfs(0, j_y - 1, 0);
            continue;
        }
        for (int i = 0; i < sweep[w].first.size(); i++) {
            buf.push_back(sweep[w].first[i]);
        }
        for (auto [wt, u, v, t, ind] : sweep[w].second) {
            leaf[t].push_back(make_tuple(wt, u, v, ind));
        }
        if (buf.size() > SQ) {
            dfs(0, j_y - 1, 0);
            for (auto [_, u, v, l, r] : buf) {
                upd(0, j_y - 1, l, r, make_pair(u, v), 0);
            }
            buf.clear();
        }
    }
    dfs(0, j_y - 1, 0);
    for (int i = 0; i < q; i++) {
        if (ans[i]) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}
