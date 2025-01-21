//https://www.codechef.com/problems/MINMAXPATHS
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int parent[N];
int ans[N];
int tout[N];
int tin[N];
int temp[N];
int mx[N];
bool vis[N];
vector<int> adj[N];

int timer = 0;

void dfs(int u, int p) {
    parent[u] = p;
    tin[u] = timer++;
    for (auto v : adj[u]) {
        if (v != p) {
            mx[v] = max(mx[u], v);
            dfs(v, u);
        }
    }
    tout[u] = timer++;
}

void calc(int u) {
    vis[u] = true;
    for (auto v : adj[u]) {
        if (!vis[v]) {
            temp[v] = max(temp[u], v);
            calc(v);
        }
    }
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, r;
        cin >> n >> r;
        for (int i = 1; i <= n; i++) {
            ans[i] = 2 * N;
            adj[i].clear();
        }
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        timer = 0;
        mx[r] = r;
        dfs(r, -1);
        for (int i = 1; i <= max(50, 2 * (int)sqrt(n)); i++) {
            if (i > n) {
                break;
            }
            int path = mx[i] * i;
            if (path > 2 * N) {
                continue;
            }
            if (parent[i] != -1) {
                temp[parent[i]] = max(i, parent[i]);
                vis[i] = true;
                calc(parent[i]);
            }
            for (int j = 1; j <= n; j++) {
                vis[j] = false;
                if (tin[j] >= tin[i] && tout[j] <= tout[i]) {
                    ans[j] = min(ans[j], mx[j] * i);
                } else {
                    ans[j] = min(ans[j], path + temp[j] * i);
                }
            }
        }
        ans[r] = 0;
        for (int i = 1; i <= n; i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
    }

    return 0;
}
