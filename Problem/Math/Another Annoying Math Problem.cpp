//https://ocpc2026w.eolymp.space/en/compete/mi9vnankul3g72sfvkn0heloj8/problem/1
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e4 + 5;
const ll M = 998244353;

vector<int> adj[N];
int color[N];
int parent[N];
int spf[N];
bool is_prime[N];
int e[N];
int dist[N];
int cycle[N];

vector<int> cyc[N];
vector<int> nodes;
int sz;

ll modPow(ll a, ll y) {
    ll res = 1;
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

void dfs(int u, int p) {
    nodes.push_back(u);
    color[u] = 1;
    parent[u] = p;
    for (int v : adj[u]) {
        if (color[v] == 0) {
            dfs(v, u);
        } else if (color[v] == 1) {
            int x = u;
            while (x != v) {
                cyc[v].push_back(x);
                x = parent[x];
            }
            cyc[v].push_back(v);
            reverse(cyc[v].begin(), cyc[v].end());
            for (int i = 0; i < cyc[v].size(); i++) {
                int x = cyc[v][i];
                cycle[x] = true;
                dist[x] = 0;
            }
            sz = cyc[v].size();
        }
        if (!cycle[u]) {
            if (cycle[v]) {
                dist[u] = 1;
            } else {
                dist[u] = 1 + dist[v];
            }
        }
    }
    color[u] = 2;
    return;
}

int main() {
    IOS;
    sieve(N);
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        n++;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            a[i] = (a[i] % k + k) % k;
        }
        for (int i = 0; i < k; i++) {
            ll s = 0; int x = 1;
            for (int j = 0; j < n; j++) {
                s += a[j] * x;
                x = x * i % k;
            }
            s %= k;
            adj[i].push_back(s);
        }
        int mx = 0;
        for (int i = 0; i < k; i++) {
            if (!color[i]) {
                nodes.clear();

                dfs(i, i);
                for (int j : nodes) {
                    mx = max(mx, dist[j]);
                }
                while (sz > 1) {
                    int p = spf[sz], ct = 0;
                    while (sz % p == 0) {
                        ct++;
                        sz /= p;
                    }
                    e[p] = max(e[p], ct);
                }
            }
        }
        ll ans = 1;
        for (int i = 1; i <= k; i++) {
            ans = ans * modPow(i, e[i]) % M;
        }
        cout << (ans + mx) % M << endl;
        for (int i = 0; i <= max(n, k); i++) {
            adj[i].clear();
            cyc[i].clear();
            color[i] = 0;
            cycle[i] = 0;
            e[i] = 0;
            parent[i] = 0;
            dist[i] = 0;
        }
    }

    return 0;
}
