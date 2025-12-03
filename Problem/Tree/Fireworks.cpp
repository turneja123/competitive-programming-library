//https://dmoj.ca/problem/apio16p2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const ll INF = 1e18;


vector<pair<int, int>> adj[N];
int parent[N];
int sz[N];
multiset<ll> st[N];

int dsu_find(int p) {
    if (parent[p] == p) {
        return p;
    }
    parent[p] = dsu_find(parent[p]);
    return parent[p];
}

void dsu_merge(int a, int b) {
    if (st[a].size() > st[b].size()) {
        swap(a, b);
    }
    parent[a] = b;
    for (auto x : st[a]) {
        st[b].insert(x);
    }
    return;
}

void dfs(int u, int p) {
    sz[u] = 0;
    int c = 1;
    for (auto [v, wt] : adj[u]) {
        if (v != p) {
            c = 0;
            dfs(v, u);
            sz[u] += sz[v];
            int a = dsu_find(u), b = dsu_find(v);
            while (st[b].size() > sz[v] + 1) {
                auto it = st[b].end();
                it--;
                st[b].erase(it);
            }
            auto it = st[b].end();
            it--;
            ll y = *it;
            it--;
            ll x = *it;
            st[b].erase(st[b].find(x));
            st[b].erase(st[b].find(y));
            st[b].insert(x + wt);
            st[b].insert(y + wt);


            dsu_merge(a, b);
        }
    }
    if (c) {
        sz[u] = 1;
        st[u].insert(0);
        st[u].insert(0);
    }
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    n += m;
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        if (i == 0) {
            continue;
        }
        int p, wt;
        cin >> p >> wt;
        ans += wt;
        p--;
        adj[p].push_back({i, wt});
        adj[i].push_back({p, wt});
    }

    dfs(0, 0);
    int a = dsu_find(0);
    vector<ll> points;
    auto it = st[a].begin();
    for (int i = 0; i < m; i++) {
        points.push_back(*it);
        it = st[a].erase(it);
    }
    ll last = 0; int ct = m;
    for (int i = 0; i < m; i++) {
        ans -= (points[i] - last) * ct;
        last = points[i];
        ct--;
    }
    cout << ans;

    return 0;
}
