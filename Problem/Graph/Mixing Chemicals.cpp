//https://www.spoj.com/problems/AMR10J/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 105;
const long long M = 1e9 + 7;

vector<pair<int, int>> adj[N];
vector<int> cycle;
vector<vector<int>> cycles;

bool on_cycle[N];
int color[N];
int parent[N];
int sz[N];

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

void dfs_root(int u, int p) {
    sz[u] = 1;
    for (auto [v, _] : adj[u]) {
        if (v == p || on_cycle[v]) {
            continue;
        }
        dfs_root(v, u);
        sz[u] += sz[v];
    }
    return;
}



void dfs(int u, int p, int e) {
    color[u] = 1;
    parent[u] = p;

    for (auto [v, ed] : adj[u]) {
        if (color[v] == 0) {
            dfs(v, u, ed);
        } else if (color[v] == 1 && ed != e) {
            cycle.push_back(v);
            on_cycle[v] = true;
            int x = u;
            while (x != v) {
                cycle.push_back(x);
                on_cycle[x] = true;
                x = parent[x];
            }
            cycles.push_back(cycle);
            cycle.clear();
        }
    }
    color[u] = 2;
    return;

}

int main() {
    IOS;

    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        for (int i = 0; i < n; i++) {
            int p;
            cin >> p;
            adj[i].push_back(make_pair(p, i));
            adj[p].push_back(make_pair(i, i));
        }
        for (int i = 0; i < n; i++) {
            if (!color[i]) {
                dfs(i, i, -1);
            }
        }

        long long ans = 1;
        for (vector<int> cycle : cycles) {
            int m = cycle.size();
            long long cur = (modPow(k - 1, m) + (k - 1) * ((m % 2) ? -1 : 1) + M) % M;
            for (int x : cycle) {
                dfs_root(x, x);
                cur = cur * modPow(k - 1, sz[x] - 1) % M;
            }
            ans = ans * cur % M;
        }

        cout << ans << endl;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            on_cycle[i] = false;
            color[i] = 0;
        }
        cycles.clear();
    }
    return 0;
}
