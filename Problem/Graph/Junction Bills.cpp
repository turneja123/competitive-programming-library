//https://repovive.com/contests/31/problems/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

vector<int> adj[N];
int deg[N];
int vis[N];
int parent[N];
int depth[N];
ll a[N];

vector<int> cyc;


void dfs(int u, int p) {
    vis[u] = 1;
    parent[u] = p;
    for (int v : adj[u]) {
        if (!vis[v]) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
        } else if (v != p && depth[u] - depth[v] > 1) {
            int w = u;
            cyc.push_back(v);
            while (w != v) {
                cyc.push_back(w);
                w = parent[w];
            }
        }
    }
}

void dfs_par(int u, int p) {
    vis[u] = 1;
    parent[u] = p;
    for (int v : adj[u]) {
        if (!vis[v]) {
            dfs_par(v, u);
        }
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
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
            deg[u]++;
            deg[v]++;
        }
        depth[0] = 0;
        dfs(0, 0);
        for (int i = 0; i < n; i++) {
            vis[i] = 0;
        }
        dfs_par(cyc[0], cyc[0]);

        int l = 1, r = 1e9, ans = -1;
        while (l <= r) {
            int mid = (l + r) / 2;

            vector<int> t_deg(n), t_a(n);
            queue<int> q;
            for (int i = 0; i < n; i++) {
                t_deg[i] = deg[i];
                t_a[i] = a[i];
                if (t_deg[i] == 1) {
                    q.push(i);
                }
            }
            int ok = 1;

            while (q.size()) {
                int u = q.front();
                q.pop();
                t_deg[u]--;
                t_deg[parent[u]]--;
                if (t_a[u] <= 0 || t_a[u] > mid) {
                    ok = 0;
                    break;
                }
                t_a[parent[u]] -= t_a[u];
                t_a[u] = 0;

                if (t_deg[parent[u]] == 1) {
                    q.push(parent[u]);
                }
            }
            if (!ok) {
                l = mid + 1;
                continue;
            }
            ll L = 1, R = mid;
            ll cur = 0;
            for (int i = 0; i < cyc.size(); i++) {
                cur *= -1;
                cur += t_a[cyc[i]];
                if (i == cyc.size() - 1) {
                    break;
                }
                L = max(L, (i % 2 == 1 ? 1 - cur : cur - mid));
                R = min(R, (i % 2 == 1 ? mid - cur : cur - 1));
            }

            if (((int)cyc.size() % 2 == 0 && cur == 0 && L <= R) || ((int)cyc.size() % 2 == 1 && cur % 2 == 0 && L <= cur / 2 && cur / 2 <= R)) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        cout << ans << endl;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            vis[i] = 0;
            deg[i] = 0;
        }
        cyc.clear();

    }

    return 0;
}
