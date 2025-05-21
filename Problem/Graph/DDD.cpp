//https://codeforces.com/contest/2109/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;
const long long INF = 1e18;

int ans[N];
long long dist[N][2];
vector<int> have[2];
vector<int> adj[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m, l;
        cin >> n >> m >> l;
        long long sum = 0;
        for (int i = 0; i < l; i++) {
            int a;
            cin >> a;
            have[a % 2].push_back(a);
            sum += a;
        }
        if (have[0].size()) {
            sort(have[0].begin(), have[0].end());
        }
        if (have[1].size()) {
            sort(have[1].begin(), have[1].end());
        }
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        for (int i = 0; i < n; i++) {
            dist[i][0] = INF;
            dist[i][1] = INF;
        }
        dist[0][0] = 0;
        priority_queue<tuple<long long, int, int>> pq;
        pq.push(make_tuple(0, 0, 0));
        while (pq.size()) {
            auto [d, u, f] = pq.top();
            pq.pop();
            d = -d;
            if (d != dist[u][f]) {
                continue;
            }
            for (int v : adj[u]) {
                if (dist[v][(f + 1) % 2] > dist[u][f] + 1) {
                    dist[v][(f + 1) % 2] = dist[u][f] + 1;
                    pq.push(make_tuple(-dist[v][(f + 1) % 2], v, (f + 1) % 2));
                }
            }
        }
        long long odd = 0, even = 0;
        if ((int)have[1].size() % 2 == 0) {
            even = sum;
            if ((int)have[1].size() != 0) {
                odd = sum - have[1][0];
            }
        } else {
            odd = sum;
            even = sum - have[1][0];
        }
        ans[0] = 1;
        for (int i = 1; i < n; i++) {
            if (dist[i][0] <= even || dist[i][1] <= odd) {
                ans[i] = 1;
            }
        }
        for (int i = 0; i < n; i++) {
            cout << ans[i];
            ans[i] = 0;
            adj[i].clear();
        }
        cout << endl;
        have[0].clear();
        have[1].clear();
    }
    return 0;
}
