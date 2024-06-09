//https://www.spoj.com/problems/MWPZ029/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e4 + 5;

int v[N];
int parent[N];
int color[N];
bool cyc[N];
bool vis[N];

void dfs(int u) {
    if (color[u] == 1) {
        int p = u;
        while (parent[p] != u) {
            cyc[p] = true;
            p = parent[p];
        }
        cyc[p] = true;
        return;
    }
    color[u] = 1;
    if (!vis[v[u]]) {
        parent[v[u]] = u;
        dfs(v[u]);
    }
    color[u] = 2;
    vis[u] = true;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            int u;
            cin >> u;
            u--;
            v[i] = u;
            cyc[i] = false;
            vis[i] = false;
            color[i] = 0;
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                dfs(i);
            }
            ans += cyc[i];
        }
        cout << ans << endl;
    }
    return 0;
}
