//https://codeforces.com/contest/1843/problem/F2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 21;

int up[K][N];
int pref_mx[K][N];
int suf_mx[K][N];
int best_mx[K][N];

int pref_mn[K][N];
int suf_mn[K][N];
int best_mn[K][N];

int sum[K][N];

int depth[N];
int a[N];

int lca(int u, int v) {
    if (depth[v] > depth[u]) {
        swap(u, v);
    }
    int x = depth[u] - depth[v];
    for (int k = K - 1; k >= 0; k--) {
        int c = x & (1 << k);
        if (c) {
            u = up[k][u];
        }
    }
    if (u == v) {
        return u;
    }
    for (int k = K - 1; k >= 0; k--) {
        if (up[k][u]!= up[k][v]) {
            u = up[k][u], v = up[k][v];
        }
    }
    return up[0][u];
}

vector<pair<int, int>> nodes;
vector<int> pref_nodes;
vector<int> suf_nodes;
vector<int> sum_nodes;
vector<int> segtree_nodes;

void build_ans(int l, int r, int node, int flag) {
    if (l > r) {
        return;
    }
    if (l == r) {
        int k = nodes[l].first, u = nodes[l].second;
        sum_nodes[node] = sum[k][u];
        if (flag) {
            pref_nodes[node] = pref_mx[k][u];
            suf_nodes[node] = suf_mx[k][u];
            segtree_nodes[node] = best_mx[k][u];
        } else {
            pref_nodes[node] = pref_mn[k][u];
            suf_nodes[node] = suf_mn[k][u];
            segtree_nodes[node] = best_mn[k][u];
        }
        return;
    }

    int mid = (l + r) / 2;
    build_ans(l, mid, 2 * node + 1, flag);
    build_ans(mid + 1, r, 2 * node + 2, flag);
    sum_nodes[node] = sum_nodes[2 * node + 1] + sum_nodes[2 * node + 2];
    if (flag) {
        pref_nodes[node] = max(pref_nodes[2 * node + 1], sum_nodes[2 * node + 1] + pref_nodes[2 * node + 2]);
        suf_nodes[node] = max(suf_nodes[2 * node + 2], sum_nodes[2 * node + 2] + suf_nodes[2 * node + 1]);
        segtree_nodes[node] = max({segtree_nodes[2 * node + 1], segtree_nodes[2 * node + 2], pref_nodes[node], suf_nodes[node], suf_nodes[2 * node + 1] + pref_nodes[2 * node + 2]});
    } else {
        pref_nodes[node] = min(pref_nodes[2 * node + 1], sum_nodes[2 * node + 1] + pref_nodes[2 * node + 2]);
        suf_nodes[node] = min(suf_nodes[2 * node + 2], sum_nodes[2 * node + 2] + suf_nodes[2 * node + 1]);
        segtree_nodes[node] = min({segtree_nodes[2 * node + 1], segtree_nodes[2 * node + 2], pref_nodes[node], suf_nodes[node], suf_nodes[2 * node + 1] + pref_nodes[2 * node + 2]});
    }
}

pair<int, int> calc(int u, int d, int flag) {
    for (int k = K - 1; k >= 0; k--) {
        int c = d & (1 << k);
        if (c) {
            nodes.push_back(make_pair(k, u));
            u = up[k][u];
        }
    }
    int m = nodes.size();
    pref_nodes.resize(4 * m);
    suf_nodes.resize(4 * m);
    sum_nodes.resize(4 * m);
    segtree_nodes.resize(4 * m);
    build_ans(0, m - 1, 0, flag);
    pair<int, int> ans = make_pair(segtree_nodes[0], suf_nodes[0]);
    nodes.clear();
    pref_nodes.clear();
    suf_nodes.clear();
    sum_nodes.clear();
    segtree_nodes.clear();
    return ans;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        depth[0] = 0;
        a[0] = 1;
        int q, n = 1;
        cin >> q;
        while (q--) {
            char c;
            cin >> c;
            if (c == '+') {
                int p, val;
                cin >> p >> val;
                p--;
                depth[n] = depth[p] + 1;
                a[n] = val;
                up[0][n] = p;
                sum[0][n] = a[n];

                pref_mx[0][n] = max(0, a[n]);
                suf_mx[0][n] = max(0, a[n]);
                best_mx[0][n] = max(0, a[n]);

                pref_mn[0][n] = min(0, a[n]);
                suf_mn[0][n] = min(0, a[n]);
                best_mn[0][n] = min(0, a[n]);

                for (int k = 1; k < K; k++) {
                    int m = up[k - 1][n];
                    up[k][n] = up[k - 1][m];
                    sum[k][n] = sum[k - 1][n] + sum[k - 1][m];

                    pref_mx[k][n] = max(pref_mx[k - 1][n], sum[k - 1][n] + pref_mx[k - 1][m]);
                    suf_mx[k][n] = max(suf_mx[k - 1][m], sum[k - 1][m] + suf_mx[k - 1][n]);
                    best_mx[k][n] = max({best_mx[k - 1][n], best_mx[k - 1][m], pref_mx[k][n], suf_mx[k][n], suf_mx[k - 1][n] + pref_mx[k - 1][m]});

                    pref_mn[k][n] = min(pref_mn[k - 1][n], sum[k - 1][n] + pref_mn[k - 1][m]);
                    suf_mn[k][n] = min(suf_mn[k - 1][m], sum[k - 1][m] + suf_mn[k - 1][n]);
                    best_mn[k][n] = min({best_mn[k - 1][n], best_mn[k - 1][m], pref_mn[k][n], suf_mn[k][n], suf_mn[k - 1][n] + pref_mn[k - 1][m]});
                }
                n++;
            } else {
                int u, v, k;
                cin >> u >> v >> k;
                u--, v--;
                int l = lca(u, v);
                int mx = -N, mn = N;
                int best_mx_u, suf_mx_u;
                int best_mn_u, suf_mn_u;
                int best_mx_v, suf_mx_v;
                int best_mn_v, suf_mn_v;
                if (u != l) {
                    pair<int, int> u_mx = calc(u, depth[u] - depth[l], 1);
                    best_mx_u = u_mx.first, suf_mx_u = u_mx.second;
                    pair<int, int> u_mn = calc(u, depth[u] - depth[l], 0);
                    best_mn_u = u_mn.first, suf_mn_u = u_mn.second;
                    mx = max({mx, best_mx_u, suf_mx_u + a[l]});
                    mn = min({mn, best_mn_u, suf_mn_u + a[l]});
                }
                if (v != l) {
                    pair<int, int> v_mx = calc(v, depth[v] - depth[l], 1);
                    best_mx_v = v_mx.first, suf_mx_v = v_mx.second;
                    pair<int, int> v_mn = calc(v, depth[v] - depth[l], 0);
                    best_mn_v = v_mn.first, suf_mn_v = v_mn.second;
                    mx = max({mx, best_mx_v, suf_mx_v + a[l]});
                    mn = min({mn, best_mn_v, suf_mn_v + a[l]});
                }
                if (u != l && v != l) {
                    mx = max(mx, suf_mx_u + a[l] + suf_mx_v);
                    mn = min(mn, suf_mn_u + a[l] + suf_mn_v);
                }
                if (u == v) {
                    mx = max(0, a[u]);
                    mn = min(0, a[u]);
                }
                if (mn <= k && k <= mx) {
                    cout << "YES" << endl;
                } else {
                    cout << "NO" << endl;
                }
            }
        }
    }


    return 0;
}
