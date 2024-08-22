//https://codeforces.com/contest/1800/problem/G
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long M = 1e9 + 7;

mt19937 generator(chrono::steady_clock::now().time_since_epoch().count());

vector<int> adj[N];
pair<long long, long long> level[N];
pair<long long, long long> prod[N];
int deg[N];
int depth[N];

map<pair<long long, long long>, int> mp[N];

int h = 0;

void dfs(int u, int p) {
    prod[u] = make_pair(1, 1);
    deg[u] = 0;
    h = max(h, depth[u]);
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
            deg[u] = max(deg[u], deg[v] + 1);
        }
    }
    for (int v : adj[u]) {
        if (v != p) {
            prod[u].first = prod[u].first * (level[deg[u]].first + prod[v].first) % M;
            prod[u].second = prod[u].second * (level[deg[u]].second + prod[v].second) % M;
        }
    }
    mp[depth[u]][prod[u]]++;
    return;

}

int main() {
    IOS;
    for (int i = 0; i < N; i++) {
        level[i].first = generator();
        level[i].second = generator();
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(0, -1);
        string ans = "YES";
        for (int i = 0; i <= h; i++) {
            int ct = 0, tot = 0;
            for (auto it = mp[i].begin(); it != mp[i].end(); ++it) {
                if (it->second % 2 == 1) {
                    ct++;
                }
                tot += it->second;
            }
            if (tot % 2 == 0 && ct > 0) {
                ans = "NO";
            }
            if (tot % 2 == 1 && ct > 1) {
                ans = "NO";
            }
        }
        cout << ans << endl;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            mp[i].clear();
        }
        h = 0;
    }
    return 0;
}
