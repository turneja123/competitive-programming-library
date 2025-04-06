//https://www.spoj.com/problems/INS16F/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int K = 17;
const int P = 25;
const long long M = 1e9 + 7;

vector<int> adj[N];
int tin[N];
int tout[N];
int up[K][N];
bool is_prime[N];
int spf[N];
int primes[N];
int mp[N];
int depth[N];
int tour[N];
int sz[N];

int timer = 0, idx = 0, euler = 0;

int ct[P][N];
long long mul[N];

struct BIT {
    int n;
    vector<int> t;
    BIT(int _n) {
        n = _n;
        t.assign(n + 1, 0);
    }
    BIT(int _n, vector<int> &a) {
        n = _n;
        t.assign(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            t[i] += a[i - 1];
            int j = i + (i & -i);
            if (j <= n) {
                t[j] += t[i];
            }
        }
    }
    void upd(int i, int val) {
        if (i <= 0) {
            return;
        }
        for (; i <= n; i += (i & -i)) {
            t[i] += val;
        }
    }
    void upd(int l, int r, int val) {
        upd(l, val);
        upd(r + 1, -val);
    }
    int query(int i) {
        int ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans += t[i];
        }
        return ans;
    }
    int query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

void sieve(int n){
    for (int i = 1; i < n; i++) {
        spf[i] = i;
        is_prime[i] = true;
    }
    is_prime[1] = false;
    for (int i = 2; i < n; i++) {
        if (is_prime[i]) {
            if (i < 100) {
                mp[i] = idx;
                primes[idx++] = i;
            }
            for (int j = 2 * i; j < n; j += i) {
                is_prime[j] = false;
                spf[j] = min(spf[j], i);
            }
        }
    }
}

void dfs(int u, int p) {
    tin[u] = timer++;
    tour[u] = euler++;
    sz[u] = 1;
    up[0][u] = p;
    for (int k = 1; k < K; k++) {
        up[k][u] = up[k - 1][up[k - 1][u]];
    }
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
            sz[u] += sz[v];
        }
    }
    tout[u] = timer++;
}

int kth(int u, int x) {
    for (int k = K - 1; k >= 0; k--) {
        int c = x & (1 << k);
        if (c) {
            u = up[k][u];
        }
    }
    return u;
}

bool is_ancestor(int u, int v) {
    return tin[u] <= tin[v] && tout[u] >= tout[v];
}

int lca(int u, int v) {
    if (is_ancestor(u, v)) {
        return u;
    }
    if (is_ancestor(v, u)) {
        return v;
    }
    for (int k = K - 1; k >= 0; k--) {
        if (!is_ancestor(up[k][u], v)) {
            u = up[k][u];
        }
    }
    return up[0][u];
}

int main() {
    IOS;
    sieve(N);
    int n, q;
    cin >> n >> q;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        mul[i] = 1;
        int x;
        cin >> x;
        while (x > 1) {
            int p = spf[x], e = 0;
            while (x % p == 0) {
                x /= p;
                e++;
            }
            if (p > 100) {
                mul[i] = mul[i] * (2 * e + 1) % M;
            } else {
                ct[mp[p]][i] += e;
            }
        }
    }
    dfs(0, 0);
    vector<BIT> bit = vector<BIT>(P, BIT(n));
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int u, v, x;
            cin >> u >> v >> x;
            u--, v--;
            if (depth[u] < depth[v]) {
                swap(u, v);
            }
            int l = lca(u, v);
            while (x > 1) {
                int p = spf[x], e = 0;
                while (x % p == 0) {
                    x /= p;
                    e++;
                }
                bit[mp[p]].upd(tour[u] + 1, e);
                if (l != 0) {
                    bit[mp[p]].upd(tour[up[0][l]] + 1, -e);
                }
                if (v != l) {
                    bit[mp[p]].upd(tour[v] + 1, e);
                    bit[mp[p]].upd(tour[l] + 1, -e);
                }
            }
        } else {
            int u;
            cin >> u;
            u--;
            long long ans = mul[u];
            for (int i = 0; i < P; i++) {
                int e = ct[i][u];
                e += bit[i].query(tour[u] + 1, tour[u] + 1 + sz[u] - 1);
                ans = ans * (2 * e + 1) % M;
            }
            cout << ans << endl;
        }
    }


    return 0;
}
