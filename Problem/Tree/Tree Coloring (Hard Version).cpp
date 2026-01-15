//https://codeforces.com/contest/2183/problem/D2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

vector<int> adj[N];

int ans = 0;
int depth[N];
int freq[N];
int par[N];
int c[N];
vector<int> g[N];
vector<int> dep_g[N];

void dfs(int u, int p) {
    freq[depth[u]]++;
    dep_g[depth[u]].push_back(u);
    int ct = 1;
    for (int v : adj[u]) {
        if (v != p) {
            par[v] = u;
            depth[v] = depth[u] + 1;
            dfs(v, u);
            ct++;
        }
    }
    ans = max(ans, ct);
}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(0, 0);
        for (int i = 0; i < n; i++) {
            ans = max(ans, freq[i]);
            freq[i] = 0;
            adj[i].clear();
        }
        c[0] = 0;
        for (int i = 1; i < n; i++) {
            if (dep_g[i].empty()) {
                break;
            }
            vector<int> skip;
            int j = 0;
            int bad = -1;

            for (int u : dep_g[i]) {
                if (skip.size()) {
                    if (c[par[u]] != skip.back()) {
                        c[u] = skip.back();
                        skip.pop_back();
                        continue;
                    }
                }
                if (j < ans && c[par[u]] != j) {
                    c[u] = j;
                    j++;
                    continue;
                }
                if (j < ans) {
                    skip.push_back(j);
                    j++;
                }
                if (j < ans) {
                    c[u] = j;
                    j++;
                    continue;
                }
                bad = u;
                c[u] = skip.back();
            }
            if (bad != -1) {
                for (int u : dep_g[i]) {
                    if (u == bad) {
                        continue;
                    }
                    if (c[par[u]] != c[bad] && c[par[bad]] != c[u]) {
                        swap(c[u], c[bad]);
                        break;
                    }
                }
            }
        }
        for (int i = 0; i < n; i++) {
            g[c[i]].push_back(i);
        }
        cout << ans << endl;
        for (int i = 0; i < ans; i++) {
            cout << g[i].size() << " ";
            for (int j : g[i]) {
                cout << j + 1 << " ";
            }
            cout << endl;
        }
        ans = 0;
        for (int i = 0; i <= n; i++) {
            g[i].clear();
            dep_g[i].clear();
            c[i] = 0;
        }
    }
    return 0;
}
