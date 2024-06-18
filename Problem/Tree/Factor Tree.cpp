//https://www.codechef.com/problems/FCTRE?tab=statement
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const long long M = 1e9 + 7;
const int sz = 320;

list<int> adj[N];
vector<int> tin, tout;
vector<vector<int>> up;
int timer = 0, lg;

int a[N];
int freq[N];
tuple<int, int, int, int> queries[N];
int ans[N];
int tour[2 * N];
int vis[N];
vector<vector<pair<int, int>>> factors;

int spf[N];
bool is_prime[N];
bool sorted[N];
long long inv[20 * N];

long long prod = 1;

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

void sieve(int n){
    for (int i = 1; i < n; i++) {
        spf[i] = i;
        is_prime[i] = true;
    }
    is_prime[1] = false;
    for (int i = 2; i < n; i++) {
        if (is_prime[i]) {
            for (int j = 2 * i; j < n; j += i) {
                is_prime[j] = false;
                spf[j] = min(spf[j], i);
            }
        }
    }
}

void factor(int n, vector<pair<int, int>> &f) {
    int last = -1, ct = 0, cnt = 1;
    while (n > 1) {
        int p = spf[n];
        if (p != last) {
            if (last != -1) {
                f.push_back(make_pair(last, ct));
            }
            last = p;
            cnt *= ct + 1;
            ct = 1;
        } else {
            ct++;
        }
        n = n / p;
    }
    if (ct > 0) {
        cnt *= ct + 1;
        f.push_back(make_pair(last, ct));
    }
    return;
}

bool comp(tuple<int, int, int, int> a, tuple<int, int, int, int> b) {
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

void query(int x, int sgn) {
    for (int j = 0; j < factors[x].size(); j++) {
        int f = factors[x][j].first, e = factors[x][j].second;
        prod = (prod * inv[freq[f] + 1]) % M;
        freq[f] += e * sgn;
        prod = (prod * (freq[f] + 1)) % M;
    }
    return;
}

int main() {
    IOS;
    sieve(N);
    factors.resize(N);
    for (int i = 1; i < N; i++) {
        factor(i, factors[i]);
    }
    inv[1] = 1;
    for(int i = 2; i < 20 * N; i++) {
        inv[i] = M - (M / i) * inv[M % i] % M;
    }
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n;
        lg = ceil(log2(n));
        up.assign(n, vector<int>(lg + 1));
        tin.resize(n);
        tout.resize(n);
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        dfs(0, 0);
        cin >> q;
        for (int i = 0; i < q; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            if (tin[u] > tin[v]) {
                swap(u, v);
            }
            int l = lca(u, v);
            if (l == u) {
                queries[i] = make_tuple(tin[u], tin[v], i, -1);
            } else {
                queries[i] = make_tuple(tout[u], tin[v], i, l);
            }
        }
        sort(queries, queries + q, comp);
        int l = 0;
        int r = -1;
        for (int i = 0; i < q; i++) {
            int cur = get<2>(queries[i]);
            int lq = get<0>(queries[i]);
            int rq = get<1>(queries[i]);
            int u;
            while (r < rq) {
                r++;
                u = tour[r];
                vis[u]++;
                if (vis[u] == 1) {
                    query(a[u], 1);
                } else if (vis[u] == 2) {
                    query(a[u], -1);
                }
            }
            while (r > rq) {
                u = tour[r];
                vis[u]--;
                if (vis[u] == 1) {
                    query(a[u], 1);
                } else if (vis[u] == 0) {
                    query(a[u], -1);
                }
                r--;
            }
            while (l < lq) {
                u = tour[l];
                vis[u]--;
                if (vis[u] == 1) {
                    query(a[u], 1);
                } else if (vis[u] == 0) {
                    query(a[u], -1);
                }
                l++;
            }
            while (l > lq) {
                l--;
                u = tour[l];
                vis[u]++;
                if (vis[u] == 1) {
                    query(a[u], 1);
                } else if (vis[u] == 2) {
                    query(a[u], -1);
                }
            }
            int t = get<3>(queries[i]);
            if (t == -1) {
                ans[cur] = prod;
            } else {
                query(a[t], 1);
                ans[cur] = prod;
                query(a[t], -1);
            }
        }
        for (int i = 0; i < q; i++) {
            cout << ans[i] << endl;
        }
        for (int i = 0; i < n; i++ ){
            adj[i].clear();
        }
        tin.clear();
        tout.clear();
        up.clear();
        for (int i = 0; i < N; i++) {
            freq[i] = 0;
            vis[i] = 0;
        }
        prod = 1;
    }
    return 0;
}
