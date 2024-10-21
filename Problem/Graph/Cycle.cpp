//https://atcoder.jp/contests/abc376/tasks/abc376_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int dist[N];
vector<int> adj[N];
vector<int> rev[N];


int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        rev[v].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        dist[i] = 1e9;
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
    int ans = 1e9;
    for (int u : rev[0]) {
        ans = min(ans, dist[u] + 1);
    }
    if (ans == 1e9) {
        cout << -1;
    } else {
        cout << ans;
    }

    return 0;
}
