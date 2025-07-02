//https://ocpc2025s.eolymp.space/en/compete/ejd99p3q1p1tnem8befqm7318o/problem/3
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

vector<int> adj[N];
bool flag[N];
bool vis[N];

int need = 0;
vector<int> restore;
vector<pair<int, int>> ans;

void dfs(int u) {
    vis[u] = true;
    for (int v : adj[u]) {
        if (!vis[v]) {
            if (!flag[v]) {
                dfs(v);
            } else {
                vis[v] = true;
                restore.push_back(v);
                need--;
            }
        }
    }
}

void dfs_first(int u) {
    vis[u] = true;
    for (int v : adj[u]) {
        if (!vis[v]) {
            ans.push_back({u, v});
            vis[v] = true;
            if (!flag[v]) {
                dfs_first(v);
            }
        }
    }
}

void dfs_second(int u) {
    vis[u] = true;
    for (int v : adj[u]) {
        if (!vis[v]) {
            ans.push_back({u, v});
            dfs_second(v);
        }
    }

}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int k;
    cin >> k;
    vector<int> subs;
    for (int i = 0; i < k; i++) {
        int u;
        cin >> u;
        u--;
        flag[u] = true;
        subs.push_back(u);
    }
    if (k == n) {
        cout << "NO";
        return 0;
    }
    for (int i = 0; i < n; i++) {
        if (!flag[i] && !vis[i]) {
            restore.clear();
            need = k;
            dfs(i);
            for (int v : restore) {
                vis[v] = false;
            }
            if (need == 0) {
                cout << "YES" << endl;
                cout << i + 1 << endl;
                for (int j = 0; j < n; j++) {
                    vis[j] = false;
                }
                dfs_first(i);
                for (int v : subs) {
                    dfs_second(v);
                }
                for (auto [u, v] : ans) {
                    cout << u + 1 << " " << v + 1 << endl;
                }
                return 0;
            }
        }
    }
    cout << "NO";

    return 0;
}
