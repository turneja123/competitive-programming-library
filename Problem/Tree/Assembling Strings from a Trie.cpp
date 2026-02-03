//https://ocpc2026w.eolymp.space/en/compete/g6s5o5k4n93719vrc5sak0hi3k/problem/1
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const unsigned ll M = 998244353;

vector<int> adj[N];
vector<int> level[N];
vector<int> ids[N];

int ans[N];
int depth[N];
int sz[N];

int mx = 0;
vector<unsigned ll> strings;

void dfs(int u) {
    sz[u] = 1;
    mx = max(mx, depth[u]);
    level[depth[u]].push_back(u);
    for (int v : adj[u]) {
        depth[v] = depth[u] + 1;
        dfs(v);
        sz[u] += sz[v];
    }
}

void dfs_build(int u, unsigned ll cur) {
    if (adj[u].empty()) {
        strings.push_back(cur);
        return;
    }
    sort(adj[u].begin(), adj[u].end(), [&](int a, int b) {
         return ans[a] < ans[b];
    });
    int j = 1;
    for (int v : adj[u]) {
        dfs_build(v, cur * M + j++);
    }

}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int u = 1; u < n; u++) {
            int v;
            cin >> v;
            v--;
            adj[v].push_back(u);
        }
        dfs(0);
        for (int i = mx; i >= 0; i--) {
            if (level[i].empty()) {
                continue;
            }

            for (int u : level[i]) {
                for (int v : adj[u]) {
                    ids[u].push_back(ans[v]);
                }
                sort(ids[u].begin(), ids[u].end());
            }
            sort(level[i].begin(), level[i].end(), [&](int a, int b) {
                if (ids[a].size() == ids[b].size()) {
                    for (int i = 0; i < ids[a].size(); i++) {
                        if (ids[a][i] < ids[b][i]) {
                            return 1;
                        }
                        if (ids[a][i] > ids[b][i]) {
                            return 0;
                        }

                    }
                    return 0;
                }
                if (ids[a].empty()) {
                    return 1;
                }
                if (ids[b].empty()) {
                    return 0;
                }

                if (ids[a].size() < ids[b].size()) {
                    for (int i = 0; i < ids[a].size(); i++) {
                        if (ids[a][i] < ids[b][i]) {
                            return 1;
                        }
                        if (ids[a][i] > ids[b][i]) {
                            return 0;
                        }

                    }
                    return 0;
                } else {
                    for (int i = 0; i < ids[b].size(); i++) {
                        if (ids[a][i] < ids[b][i]) {
                            return 1;
                        }
                        if (ids[a][i] > ids[b][i]) {
                            return 0;
                        }

                    }
                    return 1;
                }
            });
            int k = 0;
            for (int j = 0; j < level[i].size(); j++) {
                if (j != 0 && ids[level[i][j - 1]] != ids[level[i][j]]) {
                    k++;
                }
                ans[level[i][j]] = k;
            }
        }
        dfs_build(0, 0);
        cout << strings.size() << endl;
        for (auto s : strings) {
            cout << s << endl;
        }
        strings.clear();
        mx = 0;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            level[i].clear();
            ids[i].clear();
        }
    }


    return 0;
}
