//https://codeforces.com/contest/575/problem/G
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int INF = 1e9;

vector<pair<int, int>> adj[N];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        adj[u].push_back({v, wt});
        adj[v].push_back({u, wt});
    }

    vector<int> dist(n, INF);
    dist[0] = 0;
    queue<int> q;
    q.push(0);

    while (q.size()) {
        auto u = q.front();
        q.pop();
        for (auto [v, wt] : adj[u]) {
            if (dist[v] > dist[u] + 1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    vector<int> par(n, -1);
    vector<int> ed(n, -1);

    q.push(n - 1);
    par[n - 1] = n - 1;
    vector<int> go{n - 1};

    while (q.size()) {
        auto u = q.front();
        q.pop();
        for (auto [v, wt] : adj[u]) {
            if (par[v] == -1 && wt == 0) {
                par[v] = u;
                ed[v] = wt;
                q.push(v);
                go.push_back(v);
            }
        }
    }
    sort(go.begin(), go.end());
    int mn = INF;
    for (int u : go) {
        mn = min(mn, dist[u]);
    }
    for (int u : go) {
        dist[u] = mn;
    }

    while (1) {
        if (go[0] == 0) {
            break;
        }
        vector<int> go_nx;
        int best = 10;
        for (int u : go) {
            for (auto [v, wt] : adj[u]) {
                if (dist[v] == dist[u] - 1) {
                    best = min(best, wt);
                }
            }
        }

        for (int u : go) {
            for (auto [v, wt] : adj[u]) {
                if (dist[v] == dist[u] - 1 && wt == best) {
                    par[v] = u;
                    ed[v] = wt;
                    go_nx.push_back(v);
                }
            }
        }

        go = go_nx;
    }
    string ans = "";
    int u = 0;
    vector<int> path{u};
    while (u != n - 1) {
        ans += '0' + ed[u];
        u = par[u];
        path.push_back(u);
    }

    while (ans.size() && ans.back() == '0') {
        ans.pop_back();
    }
    if (ans.empty()) {
        ans = '0';
    }
    reverse(ans.begin(), ans.end());
    cout << ans << endl;
    cout << path.size() << endl;
    for (int u : path) {
        cout << u << " ";
    }


    return 0;
}
