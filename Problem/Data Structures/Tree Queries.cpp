//https://www.codechef.com/problems/P8169
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int K = 20;

vector<tuple<int, int, int>> edges_init;
vector<pair<int, int>> adj_init[N];
vector<tuple<int, int, int>> queries_init;

long long sum = 0; int e = 0;
long long ans[N];

int parent[N];
int sz[N];

vector<pair<int, int>> segtree[4 * N];
vector<tuple<int, int, int, int, long long>> restore;

int dsu_find(int a) {
    if (parent[a] == a) {
        return a;
    }
    return dsu_find(parent[a]);
}

void dsu_unite(int a, int b) {
    if (sz[b] > sz[a]) {
        swap(a, b);
    }
    sum -= (long long)sz[a] * (sz[a] - 1) / 2;
    sum -= (long long)sz[b] * (sz[b] - 1) / 2;
    sz[a] += sz[b];
    sum += (long long)sz[a] * (sz[a] - 1) / 2;
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
            restore.push_back(make_tuple(x, sz[x], y, sz[y], sum));
            dsu_unite(x, y);
            ct++;
        }
    }
    if (l == r) {
        ans[l] -= sum * e;
    } else {
        int mid = (l + r) / 2;
        dfs(l, mid, 2 * node + 1);
        dfs(mid + 1, r, 2 * node + 2);
    }
    for (int i = 0; i < ct; i++) {
        auto [u, su, v, sv, s] = restore.back();
        parent[u] = u;
        parent[v] = v;
        sz[u] = su;
        sz[v] = sv;
        sum = s;
        restore.pop_back();
    }
    return;
}

void build(int l, int r, int node) {
    segtree[node].clear();
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        for (int i = 0; i < n - 1; i++) {
            int u, v, wt;
            cin >> u >> v >> wt;
            u--, v--;
            if (u > v) {
                swap(u, v);
            }
            edges_init.push_back(make_tuple(u, v, wt));
            adj_init[u].push_back(make_pair(v, wt));
            adj_init[v].push_back(make_pair(u, wt));
        }
        for (int i = 0; i < q; i++) {
            int x, y;
            cin >> x >> y;
            x--;
            auto [u, v, wt] = edges_init[x];
            queries_init.push_back(make_tuple(u, v, y));
        }


        for (int k = 0; k < K; k++) {
            e = 1 << k;
            for (int i = 0; i <= q; i++) {
                ans[i] += (long long)n * (n - 1) / 2 * e;
            }
            vector<tuple<int, int, int, int>> edges;
            map<pair<int, int>, int> mp;
            for (int i = 0; i < n; i++) {
                parent[i] = i;
                sz[i] = 1;
            }

            for (int i = 0; i < n - 1; i++) {
                auto [u, v, wt] = edges_init[i];
                int c = wt & e;
                if (!c) {
                    mp[{u, v}] = 0;
                }
            }
            for (int i = 1; i <= q; i++) {
                auto [u, v, wt] = queries_init[i - 1];
                int c = wt & e;
                auto it = mp.find(make_pair(u, v));
                if (it == mp.end()) {
                    if (!c) {
                        mp[{u, v}] = i;
                    }
                } else{
                    if (c) {
                        edges.push_back(make_tuple(u, v, it->second, i - 1));
                        mp.erase(it);
                    }
                }
            }
            while (mp.size()) {
                auto [u, v] = mp.begin()->first;
                edges.push_back(make_tuple(u, v, mp.begin()->second, q));
                mp.erase(mp.begin());
            }
            for (auto [u, v, l, r] : edges) {
                upd(0, q, l, r, {u, v}, 0);
            }
            dfs(0, q, 0);
            build(0, q, 0);
        }
        for (int i = 0; i <= q; i++) {
            cout << ans[i] << " ";
            ans[i] = 0;
        }
        cout << endl;
        edges_init.clear();
        queries_init.clear();
        for (int i = 0; i < n; i++) {
            adj_init[i].clear();
        }
    }

    return 0;
}
