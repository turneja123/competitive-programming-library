//https://codeforces.com/contest/2117/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long M = 1e9 + 7;

long long pw[N];
int spl;
int depth[N];
vector<int> adj[N];
vector<int> leaf;

void dfs(int u, int p) {
    int ct = 0;
    for (int v : adj[u]) {
        if (v != p) {
            ct++;
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }
    if (ct == 0) {
        leaf.push_back(u);
    }
    if (ct == 2) {
        spl = u;
    }
}

int main() {
    IOS;
    pw[0] = 1;
    for (int i = 1; i < N; i++) {
        pw[i] = pw[i - 1] * 2 % M;
    }
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
        depth[0] = 1;
        dfs(0, 0);
        if (leaf.size() > 2) {
            cout << 0 << endl;
        } else if (leaf.size() == 2) {
            int x = depth[leaf[0]] - depth[spl], y = depth[leaf[1]] - depth[spl];
            if (x < y) {
                swap(x, y);
            }
            if (x == y) {
                cout << pw[n - x - y + 1] << endl;
            } else {
                cout << (pw[n - 2 * y - 1] + pw[n - 2 * y]) % M << endl;
            }
        } else {
            cout << pw[n] << endl;
        }
        leaf.clear();
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
    }

    return 0;
}
