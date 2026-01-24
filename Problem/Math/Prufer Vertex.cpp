//https://codeforces.com/contest/2190/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const ll M = 998244353;

vector<int> adj[N];
bool vis[N];
int sz[N];
int comp[N];
ll inv[N];
int id[N];
int ok[N];
int f;

vector<int> st;

void dfs(int u, int p, int j, int n) {
    st.push_back(u);
    vis[u] = 1;
    sz[u] = 1;
    id[u] = j;
    comp[j]++;
    for (int v : adj[u]) {
        if (v != p) {
            ok[v] |= u == n - 1;
            dfs(v, u, j, n);
            sz[u] += sz[v];
        }
    }
    if (u == n - 2 && f == -1) {
        f = st[1];
    }
    st.pop_back();

}

int main() {
    IOS;
    for (int i = 1; i < N; i++) {
        inv[i] = (i == 1 ? 1 : M - (M / i) * inv[M % i] % M);
    }

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        f = -1; int j = 0;
        ll ans = inv[n] * inv[n] % M;
        dfs(n - 1, -1, j++, n);
        ans = ans * n % M * comp[0] % M;
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                dfs(i, i, j++, n);
                ans = ans * n % M * comp[j - 1] % M;
            }
        }
        for (int i = 0; i < n - 1; i++) {
            ll cur;
            if (id[n - 2] == 0) {
                cur = (f == i ? ans : 0);
            } else if (id[i] == 0) {
                cur = ans * sz[i] % M * inv[comp[0]] % M * ok[i];
            } else if (id[i] == id[n - 2]) {
                cur = ans * inv[n] % M * inv[comp[0]] % M * inv[comp[id[n - 2]]] % M * (comp[0] + comp[id[n - 2]]) % M;
            } else {
                cur = ans * inv[n] % M * inv[comp[0]] % M;
            }
            cout << cur << " ";
        }
        cout << endl;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            vis[i] = 0;
            comp[i] = 0;
            ok[i] = 0;
        }

    }
    return 0;
}
