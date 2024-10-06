//https://www.codechef.com/problems/TREECUTXOR
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int deg[N];
vector<int> adj[N];
vector<tuple<int, int, int>> ans;
int lf = 2;

void dfs_check(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            dfs_check(v, u);
        }
    }
    if (deg[u] == 1 && lf > 0) {
        int x = u;
        ans.push_back(make_tuple(u, p, x));
        deg[p]--;
        deg[u]--;
        lf--;
    }
}

void dfs(int u, int p, int flag) {
    for (int v : adj[u]) {
        if (v != p && deg[v] > 0) {
            dfs(v, u, flag);
        }
    }
    if (deg[u] == 1) {
        int x = u;
        if (flag) {
            x = p;
        }
        ans.push_back(make_tuple(u, p, x));
        deg[p]--;
        deg[u]--;
    }
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            deg[i] = 0;
            adj[i].clear();
        }
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
            deg[u]++;
            deg[v]++;
        }
        if (n == 2) {
            cout << 1 << endl;
        } else {
            cout << 0 << endl;
        }
        if (n % 4 == 1 || n % 4 == 3) {
            dfs(0, 0, 0);
        } else if (n % 4 == 0) {
            dfs(0, 0, 1);
        } else {
            lf = 2;
            dfs_check(0, 0);
            dfs(0, 0, 1);

        }
        for (int i = 0; i < ans.size(); i++) {
            cout << get<0>(ans[i]) + 1 << " " << get<1>(ans[i]) + 1 << " " << get<2>(ans[i]) + 1 << endl;;
        }
        ans.clear();

    }

    return 0;
}
