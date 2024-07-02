//https://cses.fi/problemset/task/1701/
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
int center_deg[N];
bool vis[N];

vector<int> find_center(int n) {
    vector<int> leaves;
    if (n == 1) {
        leaves.push_back(0);
        return leaves;
    }
    int ct = n;
    for (int i = 0; i < n; i++) {
        if (center_deg[i] == 1) {
            leaves.push_back(i);
            vis[i] = true;
            ct--;
        }
    }
    while (ct > 0) {
        vector<int> nxt;
        for (int u : leaves) {
            for (int v : adj[u]) {
                if (!vis[v]) {
                    center_deg[v]--;
                    if (center_deg[v] == 1) {
                        nxt.push_back(v);
                        vis[v] = true;
                        ct--;
                    }
                }
            }
        }
        leaves = nxt;
    }
    return leaves;
}

void dfs(int u, int p) {
    prod[u] = make_pair(1, 1);
    deg[u] = 0;
    for (int v : adj[u]) {
        if (v != p) {
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
            center_deg[u]++, center_deg[v]++;
        }
        vector<int> center_a = find_center(n);
        dfs(center_a[0], -1);
        pair<long long, long long> f = prod[center_a[0]];
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            center_deg[i] = 0;
            vis[i] = false;
        }
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
            center_deg[u]++, center_deg[v]++;
        }
        vector<int> center_b = find_center(n);
        if (center_a.size() != center_b.size()) {
            cout << "NO" << endl;
        } else {
            string ans = "NO";
            dfs(center_b[0], -1);
            if (f.first == prod[center_b[0]].first && f.second == prod[center_b[0]].second) {
                ans = "YES";
            }
            if (center_b.size() == 2) {
                dfs(center_b[1], -1);
                if (f.first == prod[center_b[1]].first && f.second == prod[center_b[1]].second) {
                    ans = "YES";
                }
            }
            cout << ans << endl;
        }
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            center_deg[i] = 0;
            vis[i] = false;
        }
    }
    return 0;
}
