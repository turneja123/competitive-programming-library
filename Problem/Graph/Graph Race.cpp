//https://qoj.ac/contest/1452/problem/7938
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const int INF = 1e9;

vector<int> adj[N];
vector<pair<int, int>> cross[N];
vector<pair<int, int>> same[N];

int dist[N];
int a[N], b[N];

ll dp[N][2];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        dist[i] = INF;
    }
    vector<pair<int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        edges.push_back({u, v});
    }
    dist[0] = 0;
    queue<int> q;
    q.push(0);
    while (q.size()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    for (auto [u, v] : edges) {
        if (dist[u] > dist[v]) {
            swap(u, v);
        }
        if (dist[u] != dist[v]) {
            cross[dist[u]].push_back({u, v});
        } else {
            same[dist[u]].push_back({u, v});
        }
    }
    set<pair<ll, int>> st;
    for (int i = 0; i < n; i++) {
        if (dist[i] != 1) {
            dp[i][0] = a[i] - (ll)(dist[i] - 1) * b[i];
            dp[i][1] = a[i] - (ll)dist[i] * b[i];
        } else {
            dp[i][0] = -INF;
            dp[i][1] = -INF;
        }
        st.insert(make_pair(a[i] - (ll)(dist[i] + 1) * b[i], i));
    }
    for (int i = n - 1; i > 0; i--) {
        for (auto [u, v] : cross[i]) {
            dp[u][0] = max(dp[u][0], dp[v][0]);
            dp[u][1] = max(dp[u][1], dp[v][1]);
        }
        for (auto [u, v] : same[i]) {
            dp[u][0] = max(dp[u][0], dp[v][1]);
            dp[v][0] = max(dp[v][0], dp[u][1]);
        }
    }
    for (auto [u, v] : edges) {
        if (dist[u] == 1 && dist[v] == 1) {
            dp[u][0] = max(dp[u][0], (ll)a[v] - b[v]);
            dp[v][0] = max(dp[v][0], (ll)a[u] - b[u]);
        }
    }
    for (int i = 0; i < n; i++) {
        if (dist[i] == 1) {
            auto it = st.end();
            it--;
            if (it->second == i) {
                auto p = *it;
                st.erase(it);
                cout << max({st.rbegin()->first, dp[i][0], dp[i][1]}) << endl;
                st.insert(p);
            } else {
                cout << max({st.rbegin()->first, dp[i][0], dp[i][1]}) << endl;
            }
        }
    }


    return 0;
}
