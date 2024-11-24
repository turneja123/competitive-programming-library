//https://www.codechef.com/problems/QUICKEXIT0
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

vector<int> adj[N];
int sz[N];
int seen[N];
vector<int> path;

void dfs(int u, int p, int n) {
    sz[u] = 1;
    if (u == n - 1) {
        seen[u] = true;
    }
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, n);
            sz[u] += sz[v];
            seen[u] |= seen[v];
        }
    }
    if (seen[u]) {
        path.push_back(u);
    }
    return;
}



int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(0, 0, n);
        if (n - k + 1 <= path.size()) {
            cout << path.size() << endl;
        } else {
            int ans = path.size();
            priority_queue<int> pq;
            for (int u : path) {
                if (u == n - 1) {
                    continue;
                }
                for (int v : adj[u]) {
                    if (!seen[v]) {
                        pq.push(sz[v]);
                        ans += sz[v];
                    }
                }
            }
            int j = 1;
            while (pq.size() && j < k) {
                j++;
                ans -= pq.top();
                pq.pop();
            }
            cout << ans << endl;
        }
        for (int i = 0; i < n; i++) {
            seen[i] = false;
            adj[i].clear();
        }
        path.clear();

    }
    return 0;
}

