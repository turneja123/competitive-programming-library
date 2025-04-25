//https://dmoj.ca/problem/apio19p2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const int MAX = 1e7;
const int SQ = 1800;

int parent[N];
int sz[N];
int ans[N];
int pref[N];

int ptr = 0;
tuple<int, int, int, int> restore[MAX];

vector<pair<int, int>> segtree[4 * N];
vector<tuple<int, int, int, int, int>> buf;
pair<vector<tuple<int, int, int, int, int>>, vector<tuple<int, int, int, int>>> sweep[N];
vector<tuple<int, int, int>> leaf[N];

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
    if (pref[r] - ((l == 0) ? 0 : pref[l - 1]) == 0) {
        return;
    }
    for (auto [u, v] : segtree[node]) {
        int x = dsu_find(u), y = dsu_find(v);
        if (x != y) {
            restore[ptr++] = make_tuple(x, sz[x], y, sz[y]);
            dsu_unite(x, y);
            ct++;
        }
    }
    if (l == r) {
        for (auto [wt, u, ind] : leaf[l]) {
            int ct_leaf = 0;
            for (auto [WT, U, V, L, R] : buf) {
                if (WT >= wt) {
                    if (l >= L && l <= R) {
                        int x = dsu_find(U), y = dsu_find(V);
                        if (x != y) {
                            restore[ptr++] = make_tuple(x, sz[x], y, sz[y]);
                            dsu_unite(x, y);
                            ct_leaf++;
                        }
                    }
                } else {
                    break;
                }
            }

            ans[ind] = sz[dsu_find(u)];
            for (int i = 0; i < ct_leaf; i++) {
                auto [u, su, v, sv] = restore[ptr - 1];
                parent[u] = u;
                parent[v] = v;
                sz[u] = su;
                sz[v] = sv;
                ptr--;
            }
        }
        leaf[l].clear();
    } else {
        int mid = (l + r) / 2;
        dfs(l, mid, 2 * node + 1);
        dfs(mid + 1, r, 2 * node + 2);
    }
    for (int i = 0; i < ct; i++) {
        auto [u, su, v, sv] = restore[ptr - 1];
        parent[u] = u;
        parent[v] = v;
        sz[u] = su;
        sz[v] = sv;
        ptr--;
    }
    return;
}

int main() {
    IOS;
    int n, m, q;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
    set<int> st_x;
    map<int, int> mp_x;
    vector<tuple<int, int, int, int, int>> edges;
    vector<tuple<int, int, int, int>> queries;
    map<int, tuple<int, int, int, int>> mp;
    for (int i = 0; i < m; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        st_x.insert(wt);
        mp[i] = make_tuple(u, v, wt, 0);
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        int u, wt;
        cin >> u >> wt;
        u--;
        st_x.insert(wt);
        if (t == 1) {
            auto it = mp.find(u);
            auto [U, V, WT, I] = it->second;
            edges.push_back(make_tuple(WT, U, V, I, i));
            mp.erase(it);
            mp[u] = make_tuple(U, V, wt, i + 1);
        } else {
            queries.push_back(make_tuple(wt, u, i + 1, queries.size()));
        }
    }
    int j_x = 0;
    for (int x : st_x) {
        mp_x[x] = j_x++;
    }
    for (auto it = mp.begin(); it != mp.end(); ++it) {
        auto [U, V, WT, I] = it->second;
        edges.push_back(make_tuple(WT, U, V, I, q));
    }
    m = edges.size();
    int Q = queries.size();
    for (int i = 0; i < m; i++) {
        get<0>(edges[i]) = mp_x[get<0>(edges[i])];
        sweep[get<0>(edges[i])].first.push_back(edges[i]);
    }
    for (int i = 0; i < Q; i++) {
        get<0>(queries[i]) = mp_x[get<0>(queries[i])];
        sweep[get<0>(queries[i])].second.push_back(queries[i]);
    }
    for (int w = j_x - 1; w >= 0; w--) {
        if (sweep[w].first.size() > SQ) {
            for (int i = 0; i <= q; i++) {
                if (i != 0) {
                    pref[i] = pref[i - 1];
                }
                pref[i] += leaf[i].size();
            }
            dfs(0, q, 0);
            for (auto [_, u, v, l, r] : buf) {
                upd(0, q, l, r, make_pair(u, v), 0);
            }
            for (auto [_, u, v, l, r] : sweep[w].first) {
                upd(0, q, l, r, make_pair(u, v), 0);
            }
            buf.clear();
            for (auto [wt, u, t, ind] : sweep[w].second) {
                leaf[t].push_back(make_tuple(wt, u, ind));
            }
            for (int i = 0; i <= q; i++) {
                if (i != 0) {
                    pref[i] = pref[i - 1];
                }
                pref[i] += leaf[i].size();
            }
            dfs(0, q, 0);
            continue;
        }
        for (int i = 0; i < sweep[w].first.size(); i++) {
            buf.push_back(sweep[w].first[i]);
        }
        for (auto [wt, u, t, ind] : sweep[w].second) {
            leaf[t].push_back(make_tuple(wt, u, ind));
        }
        if (buf.size() > SQ) {
            for (int i = 0; i <= q; i++) {
                if (i != 0) {
                    pref[i] = pref[i - 1];
                }
                pref[i] += leaf[i].size();
            }
            dfs(0, q, 0);
            for (auto [_, u, v, l, r] : buf) {
                upd(0, q, l, r, make_pair(u, v), 0);
            }
            buf.clear();
        }
    }
    for (int i = 0; i <= q; i++) {
        if (i != 0) {
            pref[i] = pref[i - 1];
        }
        pref[i] += leaf[i].size();
    }
    dfs(0, q, 0);
    for (int i = 0; i < Q; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
