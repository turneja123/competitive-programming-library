//https://dmoj.ca/problem/occ19g6
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 150005;

vector<pair<int, int>> adj[N];

int sz[N];
bool seen_c[N];
int parent_c[N];
int depth_cen[N];
ll path_cen[N];


vector<int> id[N];
vector<ll> dist[N];

void dfs_subtree(int u, int p) {
    sz[u] = 1;
    for (auto [v, wt] : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs_subtree(v, u);
            sz[u] += sz[v];
        }
    }
    return;
}

int dfs_centroid(int u, int p, int n) {
    for (auto [v, wt] : adj[u]) {
        if (v != p && !seen_c[v] && sz[v] > n / 2) {
            return dfs_centroid(v, u, n);
        }
    }
    return u;
}

void dfs_depth(int u, int p, int c) {
    id[u].push_back(dist[c].size());
    dist[c].push_back(path_cen[u]);
    for (auto [v, wt] : adj[u]) {
        if (v != p && !seen_c[v]) {
            path_cen[v] = path_cen[u] + wt;
            dfs_depth(v, u, c);
        }
    }
    return;
}

void build_cen(int u, int p, int d) {
    dfs_subtree(u, u);
    int c = dfs_centroid(u, u, sz[u]);
    if (p == -1) {
        p = c;
    }
    depth_cen[c] = d;
    parent_c[c] = p;
    seen_c[c] = true;

    id[c].push_back(0);
    dist[c].push_back(0);
    for (auto [v, wt] : adj[c]) {
        if (!seen_c[v]) {
            path_cen[v] = wt;
            dfs_depth(v, v, c);
        }
    }
    for (auto [v, wt] : adj[c]) {
        if (!seen_c[v]) {
            build_cen(v, c, d + 1);
        }
    }
    return;
}

vector<int> inds[N];
vector<int> inds_rem[N];

vector<ll> sum[N];
vector<ll> sum_rem[N];

void upd(int u, int j) {
    int c = u, de = depth_cen[u], prev = -1;
    while (1) {
        ll d = dist[c][id[u][de]];
        inds[c].push_back(j);
        sum[c].push_back(d);
        if (prev != -1) {
            inds_rem[prev].push_back(j);
            sum_rem[prev].push_back(d);
        }

        if (c == parent_c[c]) {
            break;
        }
        prev = c;
        c = parent_c[c];
        de--;
    }
    return;
}

ll query_cen(int u, int l, int r) {
    int c = u, de = depth_cen[u], prev = -1;
    ll s = 0;
    while (1) {
        ll d = dist[c][id[u][de]];

        int L = lower_bound(inds[c].begin(), inds[c].end(), l) - inds[c].begin();
        int R = upper_bound(inds[c].begin(), inds[c].end(), r) - inds[c].begin() - 1;
        if (L <= R) {
            s += sum[c][R] - (L == 0 ? 0 : sum[c][L - 1]) + d * (R - L + 1);
        }
        if (prev != -1) {
            int L = lower_bound(inds_rem[prev].begin(), inds_rem[prev].end(), l) - inds_rem[prev].begin();
            int R = upper_bound(inds_rem[prev].begin(), inds_rem[prev].end(), r) - inds_rem[prev].begin() - 1;
            if (L <= R) {
                s -= sum_rem[prev][R] - (L == 0 ? 0 : sum_rem[prev][L - 1]) + d * (R - L + 1);
            }
        }
        if (c == parent_c[c]) {
            break;
        }
        prev = c;
        c = parent_c[c];
        de--;
    }
    return s;
}

int a[N];
int val[N];

int main() {
    IOS;
    int n, q, m;
    cin >> n >> q >> m;
    vector<pair<int, int>> ord;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        ord.push_back({a[i], i});
    }
    sort(ord.begin(), ord.end());
    for (int i = 0; i < n; i++) {
        val[i] = ord[i].first;
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }
    build_cen(0, -1, 0);
    for (int i = 0; i < n; i++) {
        upd(ord[i].second, ord[i].first);

    }
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < sum[i].size(); j++) {
            sum[i][j] += sum[i][j - 1];
        }
        for (int j = 1; j < sum_rem[i].size(); j++) {
            sum_rem[i][j] += sum_rem[i][j - 1];
        }
    }
    ll last = 0;
    for (int i = 0; i < q; i++) {
        int u, l, r;
        cin >> u >> l >> r;
        u--;
        l = (l + last) % m;
        r = (r + last) % m;
        if (l > r) {
            swap(l, r);
        }
        if (l > r) {
            last = 0;
            cout << last << endl;
            continue;
        }
        last = query_cen(u, l, r);
        cout << last << endl;


    }


    return 0;
}
