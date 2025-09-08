//https://cses.fi/problemset/task/3158/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const ll INF = 1e18;

ll ans[N];
ll cost[N];
ll dist[N];
vector<int> group[N];
vector<int> belong[N];


int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < max(n, m); i++) {
        ans[i] = INF;
        dist[i] = INF;
    }
    for (int i = 0; i < m; i++) {
        cin >> cost[i];
    }
    priority_queue<pair<ll, int>> pq;
    for (int i = 0; i < m; i++) {
        int k, seen = 0;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int u;
            cin >> u;
            u--;
            seen |= !u;
            group[i].push_back(u);
            belong[u].push_back(i);
        }
        if (seen) {
            pq.push({0, i});
            dist[i] = 0;
        }
    }
    ans[0] = 0;
    while (pq.size()) {
        auto [d, g] = pq.top();
        pq.pop();
        d = -d;
        if (dist[g] != d) {
            continue;
        }
        for (int u : group[g]) {
            ans[u] = min(ans[u], d + cost[g]);
            for (int v : belong[u]) {
                if (dist[v] > ans[u]) {
                    dist[v] = ans[u];
                    pq.push({-dist[v], v});
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }

    return 0;
}
