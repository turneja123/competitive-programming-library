//https://codeforces.com/contest/1217/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 5005;

int ans[N];
vector<int> adj[N];

bool cycle = false;
int color[N];

void dfs(int u) {
    color[u] = 1;
    for (int v : adj[u]) {
        if (color[v] == 0) {
            dfs(v);
        } else if (color[v] == 1) {
            cycle = true;
        }
        if (cycle) {
            color[u] = 2;
            return;
        }
    }
    color[u] = 2;
    return;

}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (u < v) {
            ans[i] = 1;
        } else {
            ans[i] = 2;
        }
        adj[u].push_back(v);
    }
    for (int i = 0; i < n; i++) {
        if (!color[i]) {
            dfs(i);
        }
    }
    if (!cycle) {
        cout << 1 << endl;
        for (int i = 0; i < m; i++) {
            cout << 1 << " ";
        }
    } else {
        cout << 2 << endl;
        for (int i = 0; i < m; i++) {
            cout << ans[i] << " ";
        }
    }
    return 0;
}
