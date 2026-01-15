//https://atcoder.jp/contests/arc211/tasks/arc211_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

vector<int> adj[N];
int seen[N][2];
bool vis[N][2];

void dfs(int u, int j) {
    vis[u][j] = 1;
    for (int v : adj[u]) {
        if (!vis[v][j] && seen[v][j] != u) {
            seen[v][j ^ 1] = u;
            dfs(v, j);
        }
    }
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        seen[i][0] = -1;
        seen[i][1] = -1;
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, 1);
    dfs(1, 0);
    for (int i = 0; i < n; i++) {
        if (!vis[i][0] || !vis[i][1]) {
            cout << "No";
            return 0;
        }
    }
    cout << "Yes" << endl;
    for (int i = 0; i < n; i++) {
        if (seen[i][0] != -1) {
            cout << seen[i][0] + 1 << " ";
        }
        if (seen[i][1] != -1) {
            cout << seen[i][1] + 1 << " ";
        }
        cout << endl;
    }
    return 0;
}
