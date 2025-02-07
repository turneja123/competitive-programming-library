//https://codeforces.com/contest/2059/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;
const int INF = 1e9;

vector<int> g[N], h[N];
int dist[N][N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, s1, s2;
        cin >> n >> s1 >> s2;
        s1--, s2--;
        int m1;
        cin >> m1;
        for (int i = 0; i < m1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            g[u].push_back(v);
            g[v].push_back(u);
        }
        int m2;
        cin >> m2;
        for (int i = 0; i < m2; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            h[u].push_back(v);
            h[v].push_back(u);
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dist[i][j] = INF;
            }
        }
        dist[s1][s2] = 0;
        priority_queue<pair<int, pair<int, int>>> pq;
        pq.push(make_pair(0, make_pair(s1, s2)));
        while (pq.size()) {
            int d = -pq.top().first;
            auto [u1, u2] = pq.top().second;
            pq.pop();
            if (d != dist[u1][u2]) {
                continue;
            }
            for (auto v1 : g[u1]) {
                for (auto v2 : h[u2]) {
                    if (dist[v1][v2] > dist[u1][u2] + abs(v1 - v2)) {
                        dist[v1][v2] = dist[u1][u2] + abs(v1 - v2);
                        pq.push(make_pair(-dist[v1][v2], make_pair(v1, v2)));
                    }
                }
            }
        }
        int ans = INF;
        for (int i = 0; i < n; i++) {
            bool found = false;
            set<int> st;
            for (int v : g[i]) {
                st.insert(v);
            }
            for (int v : h[i]) {
                auto it = st.find(v);
                if (it != st.end()) {
                    found = true;
                    break;
                }
            }
            if (found) {
                ans = min(ans, dist[i][i]);
            }
        }
        if (ans == INF) {
            cout << -1 << endl;
        } else {
            cout << ans << endl;

        }
        for (int i = 0; i < n; i++) {
            g[i].clear();
            h[i].clear();
        }

    }
    return 0;
}
