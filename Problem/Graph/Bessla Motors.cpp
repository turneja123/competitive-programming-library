//https://usaco.org/index.php?page=viewproblem2&cpid=1401
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e4 + 5;
const int INF = 2e9 + 5;

list<pair<int, int>> adj[N];
int ans[N];
int dist[N];
bool visited[N];

int main() {
    IOS;
    int n, m, c, r, k;
    cin >> n >> m >> c >> r >> k;
    for (int i = 0; i < m; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        adj[u].push_back(make_pair(v, wt));
        adj[v].push_back(make_pair(u, wt));
    }
    for (int j = 0; j < n; j++) {
        dist[j] = INF;
        visited[j] = false;
    }

    if (c < sqrt(N)) {
        int ct = 0;
        for (int i = 0; i < c; i++) {
            for (int j = 0; j < n; j++) {
                dist[j] = INF;
                visited[j] = false;
            }
            dist[i] = 0;
            priority_queue<pair<int, int>> pq;
            pq.push(make_pair(-dist[i], i));
            while (pq.size()) {
                int u = pq.top().second;
                pq.pop();
                if (visited[u]) {
                    continue;
                }
                visited[u] = true;
                if (u >= c) {
                    ans[u]++;
                    if (ans[u] == k) {
                        ct++;
                    }
                }
                for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
                    int v = it->first;
                    if (!visited[v] && dist[u] + it->second < dist[v] && dist[u] + it->second <= r) {
                        dist[v] = dist[u] + it->second;
                        pq.push(make_pair(-dist[v], v));
                    }

                }
            }

        }
        cout << ct << endl;
        for (int i = c; i < n; i++) {
            if (ans[i] >= k) {
                cout << i + 1 << endl;
            }
        }
    } else {
        vector<int> v;
        for (int i = c; i < n; i++) {
            dist[i] = 0;
            priority_queue<pair<int, int>> pq;
            vector<int> vis;
            vector<int> del;
            del.push_back(i);
            pq.push(make_pair(-dist[i], i));
            while (pq.size()) {
                int u = pq.top().second;
                pq.pop();
                if (visited[u]) {
                    continue;
                }
                visited[u] = true;
                if (u < c) {
                    vis.push_back(u);
                    if (vis.size() == k) {
                        break;
                    }
                }
                for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
                    int v = it->first;
                    if (!visited[v] && dist[u] + it->second < dist[v] && dist[u] + it->second <= r) {
                        if (dist[v] == INF) {
                            del.push_back(v);
                        }
                        dist[v] = dist[u] + it->second;
                        pq.push(make_pair(-dist[v], v));
                    }

                }
            }
            for (int j = 0; j < del.size(); j++) {
                dist[del[j]] = INF;
                visited[del[j]] = false;
            }
            if (vis.size() == k) {
                v.push_back(i + 1);
            }
        }
        cout << v.size() << endl;
        for (int i = 0; i < v.size(); i++) {
            cout << v[i] << endl;
        }
    }
    return 0;
}
