//https://usaco.org/index.php?page=viewproblem&cpid=1586
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 20;
const int INF = 1e9;

vector<pair<int, int>> add_min[N], rem_min[N];
vector<pair<int, int>> add_max[N], rem_max[N];
int val[N];


struct Matching {
    int n, m;

    vector<int> pairU, pairV, dist;
    vector<vector<int>> adj;

    Matching(int _n, int _m) {
        n = _n, m = _m;
        adj.resize(n);
        dist.resize(n);
        pairU.resize(n, -1);
        pairV.resize(m, -1);
    }

    void add_edge(int u, int v) {
        adj[u].push_back(v);
    }

    bool bfs() {
        queue<int> q;
        for (int u = 0; u < n; u++) {
            if (pairU[u] == -1) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = INF;
            }
        }

        bool f = false;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            if (dist[u] < INF) {
                for (auto v : adj[u]) {
                    if (pairV[v] == -1) {
                        f = true;
                    } else if (dist[pairV[v]] == INF) {
                        dist[pairV[v]] = dist[u] + 1;
                        q.push(pairV[v]);
                    }
                }
            }
        }
        return f;
    }

    bool dfs(int u) {
        if (u != -1) {
            for (auto v : adj[u]) {
                if (pairV[v] == -1 || (dist[pairV[v]] == dist[u] + 1 && dfs(pairV[v]))) {
                    pairV[v] = u;
                    pairU[u] = v;
                    return true;
                }
            }
            dist[u] = INF;
            return false;
        }
        return true;
    }

    void bpm() {
        for (int i = 0; i < n; i++) {
            pairU[i] = -1;
        }
        for (int i = 0; i < m; i++) {
            pairV[i] = -1;
        }
        while (bfs()) {
            for (int u = 0; u < n; u++) {
                if (pairU[u] == -1) {
                    dfs(u);
                }
            }
        }
        return;
    }
};

int table[K][N][2];

void build(int n, vector<int> &a) {
    for (int i = 1; i <= n; i++) {
        table[0][i][0] = a[i - 1];
        table[0][i][1] = a[i - 1];
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            table[k][i][0] = min(table[k - 1][i][0], table[k - 1][i + (1 << (k - 1))][0]);
            table[k][i][1] = max(table[k - 1][i][1], table[k - 1][i + (1 << (k - 1))][1]);
        }
    }
    return;
}

int query(int l, int r, int t) {
    int k = 31 - __builtin_clz(r - l + 1);
    if (t == 1) {
        return min(table[k][l][0], table[k][r - (1 << k) + 1][0]);
    } else {
        return max(table[k][l][1], table[k][r - (1 << k) + 1][1]);
    }
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        vector<int> a(n, 0);
        vector<tuple<int, int, int, int>> queries;
        for (int i = 0; i < q; i++) {
            int t, l, r, k;
            cin >> t >> l >> r >> k;
            val[i] = k;
            l--, r--;
            queries.push_back({t, l, r, k});
            if (t == 1) {
                add_min[l].push_back({k, i});
                rem_min[r].push_back({k, i});
            } else {
                add_max[l].push_back({k, i});
                rem_max[r].push_back({k, i});
            }
        }
        Matching mc(n, q);
        set<pair<int, int>> st_mx, st_mn;
        int ok = 1;
        for (int i = 0; i < n; i++) {
            for (auto x : add_min[i]) {
                st_mn.insert(x);
            }
            for (auto x : add_max[i]) {
                st_mx.insert(x);
            }
            if (st_mn.size() && st_mx.size() && st_mn.rbegin()->first > st_mx.begin()->first) {
                ok = 0;
                break;
            }
            if (st_mn.size()) {
                mc.add_edge(i, st_mn.rbegin()->second);
                a[i] = st_mn.rbegin()->first;
            }
            if (st_mx.size()) {
                mc.add_edge(i, st_mx.begin()->second);
                a[i] = st_mx.begin()->first;
            }
            for (auto x : rem_min[i]) {
                st_mn.erase(x);
            }
            for (auto x : rem_max[i]) {
                st_mx.erase(x);
            }
        }
        if (!ok) {
            cout << -1;
            if (t) cout << endl;
        } else {
            mc.bpm();
            for (int i = 0; i < n; i++) {
                if (mc.pairU[i] != -1) {
                    a[i] = val[mc.pairU[i]];
                }
            }
            build(n, a);
            for (int i = 0; i < q; i++) {
                auto [t, l, r, k] = queries[i];
                int v = query(l + 1, r + 1, t);
                if (v != k) {
                    ok = 0;
                }
            }
            if (!ok) {
                cout << -1;
                if (t) cout << endl;
            } else {
                for (int i = 0; i < n; i++) {
                    cout << a[i];
                    if (i != n - 1) cout << " ";
                }
                if (t) cout << endl;
            }

        }
        for (int i = 0; i < n; i++) {
            add_max[i].clear();
            rem_max[i].clear();
            add_min[i].clear();
            rem_min[i].clear();
        }
    }
    return 0;
}
