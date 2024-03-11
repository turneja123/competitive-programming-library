//solution for http://usaco.org/index.php?page=viewproblem2&cpid=1062
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

list <int> adj[N];
bool vis[N];
int sol = 0;

void dfs(int v) {
    vis[v] = true;
    int ct = 1;
    int deg = adj[v].size();
    if (v != 0) {
        deg--;
    }
    while (ct <= deg) {
        ct *= 2;
        sol++;
    }
    for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
        if (!vis[*it]) {
            sol++;
            dfs(*it);
        }
    }
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    dfs(0);
    cout << sol;
    return 0;
}
