//https://qoj.ac/problem/16120
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const ll INFLL = 1e18;

int sz[N];
bool seen_c[N];
int parent_c[N];
int depth[N];
int color[N];
int depth_cen[N];

vector<int> adj[N];
vector<int> id[N];
vector<int> dist[N];

multiset<ll> roots[N];

void dfs_subtree(int u, int p) {
    sz[u] = 1;
    for (int v : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs_subtree(v, u);
            sz[u] += sz[v];
        }
    }
    return;
}

int dfs_centroid(int u, int p, int n) {
    for (int v : adj[u]) {
        if (v != p && !seen_c[v] && sz[v] > n / 2) {
            return dfs_centroid(v, u, n);
        }
    }
    return u;
}

void dfs_depth(int u, int p, int c) {
    id[u].push_back(dist[c].size());
    dist[c].push_back(depth[u]);
    for (int v : adj[u]) {
        if (v != p && !seen_c[v]) {
            depth[v] = depth[u] + 1;
            dfs_depth(v, u, c);
        }
    }
    return;
}

void build(int u, int p, int d) {
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
    for (int v : adj[c]) {
        if (!seen_c[v]) {
            depth[v] = 1;
            dfs_depth(v, v, c);
        }
    }
    for (int v : adj[c]) {
        if (!seen_c[v]) {
            build(v, c, d + 1);
        }
    }
    return;
}

ll ans[N];

void upd(int u, ll val, int f) {
    int c = u, de = depth_cen[u];
    while (1) {
        int d = dist[c][id[u][de]];
        if (f == 1) {
            roots[c].insert(val + d);
        } else {
            roots[c].erase(roots[c].find(val + d));
        }
        if (c == parent_c[c]) {
            break;
        }
        c = parent_c[c];
        de--;
    }
    return;
}

ll query(int u) {
    ll best = INFLL;
    int c = u, de = depth_cen[u];
    while (1) {
        int d = dist[c][id[u][de]];
        if (roots[c].size()) {
            best = min(best, *roots[c].begin() + d + 1);
        }
        if (c == parent_c[c]) {
            break;
        }
        c = parent_c[c];
        de--;
    }
    return best;
}

vector<pair<int, int>> ivals[2 * N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    build(0, -1, 0);
    vector<pair<int, int>> a(n);
    vector<tuple<int, int, int>> compr;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    if (a[0].first > a[n - 1].first) {
        for (int i = 0; i < n; i++) {
            a[i].first *= -1;
            a[i].second *= -1;
            swap(a[i].first, a[i].second);
        }
    }
    for (int i = 0; i < n; i++) {
        compr.push_back({a[i].first, 0, i});
        compr.push_back({a[i].second, 1, i});
    }
    sort(compr.begin(), compr.end());
    int last = -1, m = -1;
    for (int i = 0; i < 2 * n; i++) {
        auto [v, f, j] = compr[i];
        if (v != last) {
            m++;
            last = v;
        }
        if (f == 0) {
            a[j].first = m;
        } else {
            a[j].second = m;
        }
    }
    m++;
    priority_queue<pair<int, int>> pq;
    upd(0, 0, 1);
    pq.push({-a[0].second, 0});

    for (int i = 1; i < n; i++) {
        a[i].first = max(a[i].first, a[0].first);
        if (a[i].first <= a[i].second) {
            ivals[a[i].first].push_back({i, a[i].second});
        }
    }
    for (int i = a[0].first; i < m; i++) {
        for (auto [j, r] : ivals[i]) {
            ans[j] = query(j);
            upd(j, ans[j], 1);
            pq.push({-r, j});
        }
        while (pq.size() && -pq.top().first == i) {
            int u = pq.top().second;
            upd(u, ans[u], -1);
            pq.pop();
        }
    }
    cout << max(0ll, ans[n - 1] - 1);

    return 0;
}
