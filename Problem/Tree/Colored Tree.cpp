//https://codeforces.com/contest/1260/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const ll M = 1e9 + 7;

int l[N], r[N];
int sz[N];
bool seen_c[N];
int parent_c[N];
int depth[N];
ll inv[N];
vector<int> adj[N];
ll prod = 1;
ll ans = 0;

struct BIT {
    int n;
    vector<int> t1, t2;

    BIT(int _n) {
        n = _n;
        t1.assign(n + 1, 0);
        t2.assign(n + 1, 0);
    }

    void add(vector<int> &t, int i, int v) {
        if (i <= 0) {
            return;
        }
        for (; i <= n; i += (i & -i)) {
            t[i] += v;
            if (t[i] > M) {
                t[i] -= M;
            }
        }
    }

    int sum(vector<int> &t, int i) {
        int s = 0;
        for (; i >= 1; i -= (i & -i)) {
            s += t[i];
            if (s > M) {
                s -= M;
            }
        }
        return s;
    }

    void upd(int l, int r, int val) {
        if (l > r) {
            return;
        }
        add(t1, l, val);
        add(t1, r + 1, M - val);
        add(t2, l, (ll)val * (l - 1) % M);
        add(t2, r + 1, (ll)(M - val) * r % M);
    }

    int query(int i) {
        if (i <= 0) {
            return 0;
        }
        return ((ll)sum(t1, i) * i - sum(t2, i) + M) % M;
    }

    int query(int l, int r) {
        if (l > r) {
            return 0;
        }
        return (query(r) - query(l - 1) + M) % M;
    }
};

BIT bit_sum(N), bit_ct(N);

long long modPow(long long a, long long y) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
}

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

void dfs_depth1(int u, int p) {
    ans += (ll)bit_sum.query(l[u], r[u]) * inv[u] % M;
    ans += (ll)bit_ct.query(l[u], r[u]) * inv[u] % M * depth[u] % M;
    ans %= M;
    for (int v : adj[u]) {
        if (v != p && !seen_c[v]) {
            depth[v] = depth[u] + 1;
            dfs_depth1(v, u);
        }
    }
    return;
}

void dfs_depth2(int u, int p) {
    bit_ct.upd(l[u], r[u], prod * inv[u] % M);
    bit_sum.upd(l[u], r[u], prod * inv[u] % M * depth[u] % M);

    for (int v : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs_depth2(v, u);
        }
    }
    return;
}

void dfs_depth3(int u, int p) {
    bit_ct.upd(l[u], r[u], (M - prod * inv[u] % M));
    bit_sum.upd(l[u], r[u], (M - prod * inv[u] % M * depth[u] % M));

    for (int v : adj[u]) {
        if (v != p && !seen_c[v]) {
            dfs_depth3(v, u);
        }
    }
    return;
}

void build(int u, int p) {
    dfs_subtree(u, u);
    int c = dfs_centroid(u, u, sz[u]);
    if (p == -1) {
        p = c;
    }
    parent_c[c] = p;
    seen_c[c] = true;

    bit_ct.upd(l[c], r[c], prod * inv[c] % M);
    for (int v : adj[c]) {
        if (!seen_c[v]) {
            depth[v] = 1;
            dfs_depth1(v, v);
            dfs_depth2(v, v);
        }
    }

    bit_ct.upd(l[c], r[c], (M - prod * inv[c] % M));
    for (int v : adj[c]) {
        if (!seen_c[v]) {
            dfs_depth3(v, v);
        }
    }


    for (int v : adj[c]) {
        if (!seen_c[v]) {
            build(v, c);
        }
    }
    return;
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
        prod = prod * (r[i] - l[i] + 1) % M;
        inv[i] = modPow(r[i] - l[i] + 1, M - 2);
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    build(0, -1);
    cout << ans;


    return 0;
}
