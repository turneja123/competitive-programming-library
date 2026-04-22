//https://dmoj.ca/problem/ccoprep3p1
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6;
const ll M = 1e9 + 7;

ll pw[N + 1];
int deg[N + 1];
int freq[N + 1];
bool vis[N + 1];
vector<pair<int, int>> adj[N + 1];
vector<int> comp;
int span[2 * N];

void dfs(int u) {
    comp.push_back(u);
    vis[u] = 1;
    for (auto [v, e] : adj[u]) {
        if (!vis[v]) {
            span[e] = 1;
            dfs(v);
        }
    }
    return;
}

int vis2[N + 1];
int forced[N + 1];
ll dp[N + 1][2];

void calc(int u, int p) {
    vis2[u] = 1;
    dp[u][0] = (forced[u] == 1 ? 0 : 1);
    dp[u][1] = (forced[u] == 0 ? 0 : pw[freq[u]] - 1);
    for (auto [v, e] : adj[u]) {
        if (v != p && !vis2[v]) {
            calc(v, u);
            dp[u][0] = dp[u][0] * (dp[v][0] + dp[v][1]) % M;
            dp[u][1] = dp[u][1] * dp[v][0] % M;
        }
    }

}

int main() {
    IOS;
    int n;
    cin >> n;
    int L = 20000, R = 1e6;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        freq[a]++;
        if (a < 20000) {
            L = 1;
            R = 2e5;
        }
    }
    vector<pair<int, int>> edges;
    pw[0] = 1;
    for (int i = 1; i <= N; i++) {
        pw[i] = pw[i - 1] * 2 % M;
        for (int j = i + 1; j <= N; j++) {
            ll b = (ll)2 * i * j;
            if (b > R) {
                break;
            }
            ll a =(ll)j * j - (ll)i * i;
            if ((j - i) % 2 == 1 && __gcd(i, j) == 1 && a <= R && a >= L && b >= L) {
                edges.push_back({a, b});
            }
        }
    }
    int e = 0;
    for (auto [u, v] : edges) {
        adj[u].push_back({v, e});
        adj[v].push_back({u, e});
        e++;
    }
    for (int i = L; i <= R; i++) {
        sort(adj[i].begin(), adj[i].end());
    }
    ll ans = 1;
    for (int i = L; i <= R; i++) {
        if (!vis[i]) {
            dfs(i);
            int m = comp.size();

            vector<int> nodes;
            for (int u : comp) {
                int ok = 1;
                for (auto [v, e] : adj[u]) {
                    if (!span[e]) {
                        ok = 0;
                    }
                }
                if (!ok) {
                    nodes.push_back(u);
                }
            }
            if (nodes.empty()) {
                for (int u : comp) {
                    forced[u] = -1;
                    vis2[u] = 0;
                }
                calc(i, i);
                ans = ans * (dp[i][0] + dp[i][1]) % M;
                comp.clear();
                continue;
            }
            ll ways = 0;
            int b = nodes.size();
            for (int i = 0; i < 1 << b; i++) {
                int ok = 1;
                for (int j = 0; j < b; j++) {
                    for (int k = 0; k < b; k++) {
                        if (j == k) {
                            continue;
                        }
                        int cj = i & (1 << j), ck = i & (1 << k);
                        if (cj && ck) {
                            auto it = lower_bound(adj[nodes[j]].begin(), adj[nodes[j]].end(), make_pair(nodes[k], -1));
                            if (it != adj[nodes[j]].end() && it->first == nodes[k]) {
                                ok = 0;
                            }
                        }
                    }
                }
                if (!ok) {
                    continue;
                }
                for (int u : comp) {
                    forced[u] = -1;
                    vis2[u] = 0;
                }
                for (int u : nodes) {
                    vis2[u] = 1;
                }
                ll prod = 1;
                for (int j = 0; j < b; j++) {
                    int cj = i & (1 << j);
                    if (cj) {
                        prod = prod * (pw[freq[nodes[j]]] - 1) % M;
                        for (auto [v, _] : adj[nodes[j]]) {
                            forced[v] = 0;
                        }
                    }
                }
                for (int u : comp) {
                    if (!vis2[u]) {
                        calc(u, u);
                        prod = prod * (dp[u][0] + dp[u][1]) % M;
                    }
                }
                ways = (ways + prod) % M;
            }
            ans = ans * ways % M;

            comp.clear();


        }
    }
    cout << (ans - 1 + M) % M;



    return 0;
}
