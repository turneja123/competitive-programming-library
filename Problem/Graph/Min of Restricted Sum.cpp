//https://atcoder.jp/contests/abc396/tasks/abc396_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

vector<pair<int, int>> adj[N];

bool vis[N];
int w[N];

bool can = true;

vector<int> comp;

void dfs(int u) {
    vis[u] = true;
    comp.push_back(u);
    for (auto [v, d] : adj[u]) {
        if (!vis[v]) {
            w[v] = w[u] ^ d;
            dfs(v);
        } else {
            int x = w[u] ^ d;
            if (x != w[v]) {
                can = false;
            }
        }
    }
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, z;
        cin >> u >> v >> z;
        u--, v--;
        adj[u].push_back(make_pair(v, z));
        adj[v].push_back(make_pair(u, z));
    }
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            int x = 0;
            dfs(i);
            vector<int> ct(30, 0);
            for (int u : comp) {
                for (int j = 0; j < 30; j++) {
                    int c = (1 << j) & w[u];
                    if (c) {
                        ct[j]++;
                    }
                }
            }
            int m = comp.size() / 2;
            for (int j = 0; j < 30; j++) {
                if (ct[j] > m) {
                    x ^= 1 << j;
                }
            }
            for (int u : comp) {
                w[u] ^= x;
            }
            comp.clear();
        }
    }
    if (!can) {
        cout << -1;
        return 0;
    }
    for (int i = 0; i < n; i++) {
        cout << w[i] << " ";
    }
    return 0;
}
