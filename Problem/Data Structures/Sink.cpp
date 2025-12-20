//https://codeforces.com/contest/2158/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int S = 40 * N;

struct Node {
    int parent;
    int val;
    int sz;
    Node() {}
}__attribute__((packed));
static_assert(sizeof(Node) == 12, "");

Node dsu[2 * N];
int ans[N];

int dsu_find(int a) {
    if (dsu[a].parent == a) {
        return a;
    }
    return dsu_find(dsu[a].parent);
}

int dsu_unite(int a, int b) {
    if (dsu[b].sz > dsu[a].sz) {
        swap(a, b);
    }
    dsu[a].sz += dsu[b].sz;
    dsu[b].parent = a;
    int ret;
    if (dsu[a].val + dsu[b].val == 0) {
        ret = 0;
    } else {
        ret = 1;
    }
    dsu[a].val &= dsu[b].val;
    return ret;
}

pair<int, int> segtree_data[S];
int segtree_head[4 * N];
int segtree_next[S];
int segtree_sz = 0;

void upd(int l, int r, int lq, int rq, pair<int, int> edge, int node) {
    if (r < lq || l > rq) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree_data[segtree_sz] = edge;
        segtree_next[segtree_sz] = segtree_head[node];
        segtree_head[node] = segtree_sz++;
        return;
    }
    int mid = (l + r) / 2;
    upd(l, mid, lq, rq, edge, 2 * node + 1);
    upd(mid + 1, r, lq, rq, edge, 2 * node + 2);
    return;
}

int comps;
tuple<int, int, Node, Node, int> restore[4 * N];
int m = 0;

void dfs(int l, int r, int node) {
    int ct = 0;
    for (int e = segtree_head[node]; e != -1; e = segtree_next[e]) {
        int x = segtree_data[e].first;
        int y = segtree_data[e].second;
        if (x >= 2 * N) {
            x -= 2 * N;
            int a = dsu_find(x), b = dsu_find(y);
            if (a != b) {
                restore[m++] = make_tuple(a, b, dsu[a], dsu[b], comps);
                comps -= dsu_unite(a, b);
                ct++;
            }
        } else {
            int a = dsu_find(x), b = dsu_find(y);
            restore[m++] = make_tuple(a, b, dsu[a], dsu[b], comps);

            comps -= dsu[b].val;
            dsu[b].val = 0;
            ct++;
        }
    }

    if (l == r) {
        ans[l] = comps;
    } else {
        int mid = (l + r) / 2;
        dfs(l, mid, 2 * node + 1);
        dfs(mid + 1, r, 2 * node + 2);
    }
    for (int i = 0; i < ct; i++) {
        auto [a, b, A, B, c] = restore[m - 1];
        comps = c;
        dsu[a] = A;
        dsu[b] = B;
        m--;
    }

    return;
}


int main() {
    IOS;
    for (int i = 0; i < 4 * N; i++) {
        segtree_head[i] = -1;
    }
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<vector<int>> id(n, vector<int>(m, 0));
        vector<vector<int>> a(n, vector<int>(m, 0));
        vector<int> val;

        int k = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                id[i][j] = k++;
                cin >> a[i][j];
                val.push_back(a[i][j]);
            }
        }
        map<pair<int, int>, int> mp_e;
        map<pair<int, int>, int> mp_d;

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int dx = 0; dx <= 1; dx++) {
                    for (int dy = 0; dy <= 1; dy++) {
                        if (abs(dx) + abs(dy) == 1 && i + dx >= 0 && i + dx < n && j + dy >= 0 && j + dy < m) {
                            int l = id[i][j], r = id[i + dx][j + dy];
                            if (a[i][j] > a[i + dx][j + dy]) {
                                swap(l, r);
                            }
                            if (a[i][j] == a[i + dx][j + dy] && l > r) {
                                swap(l, r);
                            }

                            if (a[i][j] == a[i + dx][j + dy]) {
                                mp_e[{l, r}] = 0;
                            } else {
                                mp_d[{l, r}] = 0;
                            }
                        }
                    }
                }
            }
        }
        vector<tuple<int, int, int, int, int>> edges;
        int q;
        cin >> q;
        for (int tim = 1; tim <= q; tim++) {
            int i, j, z;
            cin >> i >> j >> z;
            i--, j--;
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (abs(dx) + abs(dy) == 1 && i + dx >= 0 && i + dx < n && j + dy >= 0 && j + dy < m) {
                        int l = id[i][j], r = id[i + dx][j + dy];
                        if (a[i][j] > a[i + dx][j + dy]) {
                            swap(l, r);
                        }
                        if (a[i][j] == a[i + dx][j + dy] && l > r) {
                            swap(l, r);
                        }

                        if (a[i][j] == a[i + dx][j + dy]) {
                            auto it = mp_e.find({l, r});
                            edges.push_back(make_tuple(l, r, it->second, tim - 1, -1));
                            mp_e.erase(it);
                        } else {
                            auto it = mp_d.find({l, r});
                            edges.push_back(make_tuple(l, r, it->second, tim - 1, a[i][j]));
                            mp_d.erase(it);
                        }
                    }
                }
            }
            id[i][j] = k++;
            a[i][j] -= z;
            val.push_back(a[i][j]);
            for (int dx = -1; dx <= 1; dx++) {
                for (int dy = -1; dy <= 1; dy++) {
                    if (abs(dx) + abs(dy) == 1 && i + dx >= 0 && i + dx < n && j + dy >= 0 && j + dy < m) {
                        int l = id[i][j], r = id[i + dx][j + dy];
                        if (a[i][j] > a[i + dx][j + dy]) {
                            swap(l, r);
                        }
                        if (a[i][j] == a[i + dx][j + dy] && l > r) {
                            swap(l, r);
                        }

                        if (a[i][j] == a[i + dx][j + dy]) {
                            mp_e[{l, r}] = tim;
                        } else {
                            mp_d[{l, r}] = tim;
                        }
                    }
                }
            }
        }
        for (auto it : mp_e) {
            auto [l, r] = it.first;
            int tim = it.second;
            edges.push_back(make_tuple(l, r, tim, q, -1));
        }
        for (auto it : mp_d) {
            auto [l, r] = it.first;
            int tim = it.second;
            edges.push_back(make_tuple(l, r, tim, q, val[l]));
        }
        for (auto [l, r, lq, rq, v] : edges) {
            upd(0, q, lq, rq, make_pair((v < 0 ? l + 2 * N : l), r), 0);
        }
        for (int i = 0; i < k; i++) {
            dsu[i].parent = i;
            dsu[i].sz = 1;
            dsu[i].val = 1;
        }
        comps = k;
        edges.clear();
        mp_d.clear();
        mp_e.clear();
        m = 0;
        dfs(0, q, 0);
        for (int i = 0; i <= q; i++) {
            cout << ans[i] - q << endl;
        }
        for (int i = 0; i <= 4 * (q + 1); i++) {
            segtree_head[i] = -1;
        }
        segtree_sz = 0;
    }

    return 0;
}
