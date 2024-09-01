//https://codeforces.com/contest/986/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int SQ = 3200;
const int MAX = 1e7 + 5;

const long long M = 1e9 + 7;

list<int> adj[N];
vector<int> tin, tout;
vector<vector<int>> up;
int timer = 0, lg;

int a[N];
int freq[N];
int sz;
tuple<int, int, int, int, int> queries[N];
int ans[N];
int tour[2 * N];
int vis[N];

int seen[N];
int val[N];

int ct[32][SQ];
int ct_heavy[MAX];
vector<int> primes;

bool composite[SQ];
vector<pair<int, int>> f[N];

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

bool comp(tuple<int, int, int, int, int> a, tuple<int, int, int, int, int> b) {
    int block1 = get<0>(a) / sz;
    int block2 = get<0>(b) / sz;
    if (block1 != block2) {
        return block1 < block2;
    }
    int r1 = get<1>(a);
    int r2 = get<1>(b);
    return r1 < r2;
}

void dfs(int v, int p) {
    tour[timer] = v;
    tin[v] = timer++;
    up[v][0] = p;
    for (int i = 1; i <= lg; i++) {
        up[v][i] = up[up[v][i - 1]][i - 1];
    }
    for (int u : adj[v]) {
        if (u != p) {
            dfs(u, v);
        }
    }
    tour[timer] = v;
    tout[v] = timer++;
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
    for (int i = lg; i >= 0; --i) {
        if (!is_ancestor(up[u][i], v)) {
            u = up[u][i];
        }
    }
    return up[u][0];
}

void sieve() {
    for (int i = 2; i < SQ; i++) {
        if (!composite[i]) {
            primes.push_back(i);
            for (int j = 2 * i; j < SQ; j += i) {
                composite[j] = true;
            }
        }
    }
}

void add(int i, int sgn) {
    for (pair<int, int> pr : f[i]) {
        if (pr.first < SQ) {
            ct[pr.second][pr.first] += sgn;
        } else {
            ct_heavy[pr.first] += sgn;
        }
    }
}

int get(int x) {
    long long ans = 1;
    int t = x;
    for (int p : primes) {
        int j = 0;
        while (t % p == 0) {
            t /= p;
            j++;
        }
        if (j > 0) {
            int e = 0;
            for (int k = 1; k < 32; k++) {
                e += min(j, k) * ct[k][p];
            }
            ans = ans * modPow(p, e) % M;
        }
    }
    if (t > 1) {
        ans = ans * modPow(t, ct_heavy[t]) % M;
    }
    return ans;
}

int main() {
    IOS;
    sieve();
    int n, q;
    cin >> n;
    lg = ceil(log2(n));
    up.assign(n, vector<int>(lg + 1));
    tin.resize(n);
    tout.resize(n);
    sz = sqrt(2 * n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        int t = a[i];
        for (int p : primes) {
            int j = 0;
            while (t % p == 0) {
                t /= p;
                j++;
            }
            if (j > 0) {
                f[i].push_back(make_pair(p, j));
            }
        }
        if (t > 1) {
            f[i].push_back(make_pair(t, 1));
        }
    }
    dfs(0, 0);
    cin >> q;
    for (int i = 0; i < q; i++) {
        int u, v, x;
        cin >> u >> v >> x;
        u--, v--;
        if (tin[u] > tin[v]) {
            swap(u, v);
        }
        int l = lca(u, v);
        if (l == u) {
            queries[i] = make_tuple(tin[u], tin[v], i, -1, x);
        } else {
            queries[i] = make_tuple(tout[u], tin[v], i, l, x);
        }
    }
    sort(queries, queries + q, comp);
    int l = 0;
    int r = -1;
    int ct = 0;
    for (int i = 0; i < q; i++) {
        int cur = get<2>(queries[i]);
        int lq = get<0>(queries[i]);
        int rq = get<1>(queries[i]);
        int x = get<4>(queries[i]);
        int u;
        vector<int> qq;
        while (r < rq) {
            r++;
            u = tour[r];
            vis[u]++;
            if (!seen[u]) {
                seen[u] = true;
                qq.push_back(u);
            }
            if (vis[u] == 1) {
                val[u]++;
            } else if (vis[u] == 2) {
                val[u]--;
            }
        }
        while (r > rq) {
            u = tour[r];
            vis[u]--;
            if (!seen[u]) {
                seen[u] = true;
                qq.push_back(u);
            }
            if (vis[u] == 1) {
                val[u]++;
            } else if (vis[u] == 0) {
                val[u]--;
            }
            r--;
        }
        while (l < lq) {
            u = tour[l];
            vis[u]--;
            if (!seen[u]) {
                seen[u] = true;
                qq.push_back(u);
            }
            if (vis[u] == 1) {
                val[u]++;
            } else if (vis[u] == 0) {
                val[u]--;
            }
            l++;
        }
        while (l > lq) {
            l--;
            u = tour[l];
            vis[u]++;
            if (!seen[u]) {
                seen[u] = true;
                qq.push_back(u);
            }
            if (vis[u] == 1) {
                val[u]++;
            } else if (vis[u] == 2) {
                val[u]--;
            }
        }
        for (int u : qq) {
            if (val[u] != 0) {
                add(u, val[u]);
            }
            seen[u] = false;
            val[u] = 0;
        }
        int t = get<3>(queries[i]);
        if (t == -1) {
            ans[cur] = get(x);
        } else {
            add(t, 1);

            ans[cur] = get(x);

            add(t, -1);
        }
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
