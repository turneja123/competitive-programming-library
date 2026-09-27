//https://codeforces.com/contest/852/problem/I
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int K = 20;
const int SQ = 320;

int f[N];
int c[N];

int up[K][N];
vector<int> ord;
vector<int> adj[N];
int tin[N];
int tout[N];
int depth[N];
ll ans[N];
int freq[N];
int ct[2][N];

struct Query {
    int l;
    int r;
    int lca;
    int i;
};


void dfs(int u, int p) {
    tin[u] = ord.size();
    ord.push_back(u);

    up[0][u] = p;
    for (int i = 1; i < K; i++) {
        int v = up[i - 1][u];
        up[i][u] = up[i - 1][v];
    }
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }

    tout[u] = ord.size();
    ord.push_back(u);
}


int lca(int u, int v) {
    if (depth[u] > depth[v]) {
        swap(u, v);
    }
    int d = depth[v] - depth[u];
    for (int i = K - 1; i >= 0; i--) {
        int c = d & (1 << i);
        if (c) {
            v = up[i][v];
        }
    }
    if (u == v) {
        return u;
    }
    for (int i = K - 1; i >= 0; i--) {
        if (up[i][u] != up[i][v]) {
            u = up[i][u];
            v = up[i][v];
        }
    }
    return up[0][u];
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> f[i];
    }
    vector<int> compr;
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        compr.push_back(c[i]);
    }
    sort(compr.begin(), compr.end());
    compr.erase(unique(compr.begin(), compr.end()), compr.end());
    for (int i = 0; i < n; i++) {
        c[i] = lower_bound(compr.begin(), compr.end(), c[i]) - compr.begin();
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, 0);
    int q;
    cin >> q;
    vector<Query> queries;
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (tin[u] > tin[v]) {
            swap(u, v);
        }
        int l = lca(u, v);
        if (u == l) {
            queries.push_back({tin[u], tin[v], -1, i});
        } else {
            queries.push_back({tout[u], tin[v], l, i});
        }
    }
    sort(queries.begin(), queries.end(), [&](Query &a, Query &b) {
        if (a.l / SQ != b.l / SQ) {
            return a.l / SQ < b.l / SQ;
        }
        return a.r < b.r;
    });
    ll sum = 0;
    auto add = [&](int u) -> void {
        freq[u]++;
        if (freq[u] == 1) {
            sum += ct[f[u] ^ 1][c[u]];
            ct[f[u]][c[u]]++;
        }
        if (freq[u] == 0 || freq[u] == 2) {
            sum -= ct[f[u] ^ 1][c[u]];
            ct[f[u]][c[u]]--;
        }
    };
    auto rem = [&](int u) -> void {
        freq[u]--;
        if (freq[u] == 1) {
            sum += ct[f[u] ^ 1][c[u]];
            ct[f[u]][c[u]]++;
        }
        if (freq[u] == 0 || freq[u] == 2) {
            sum -= ct[f[u] ^ 1][c[u]];
            ct[f[u]][c[u]]--;
        }
    };

    int l = 0, r = -1;
    for (int i = 0; i < q; i++) {
        auto [lq, rq, x, ind] = queries[i];
        while (r < rq) {
            r++;
            add(ord[r]);
        }
        while (l > lq) {
            l--;
            add(ord[l]);
        }
        while (l < lq) {
            rem(ord[l]);
            l++;
        }
        while (r > rq) {
            rem(ord[r]);
            r--;
        }
        if (x != -1) {
            add(x);
            ans[ind] = sum;
            rem(x);
        } else {
            ans[ind] = sum;
        }
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
