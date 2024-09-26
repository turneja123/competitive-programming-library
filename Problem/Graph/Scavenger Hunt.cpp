//https://dmoj.ca/problem/othscc1p5
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int K = 31;
const long long INF = 1e18;

int s[K];
int cost[K];
long long dist[N * K];
vector<int> items[N];

vector<pair<int, int>> adj[N];
vector<pair<int, int>> graph[N * K];

int calc(int i, vector<int> &v) {
    int j = lower_bound(v.begin(), v.end(), i) - v.begin();
    if (j == v.size() || v[j] != i) {
        return i;
    }
    while (j < v.size() && v[j] == i) {
        i++, j++;
    }
    return i;
}

int main() {
    IOS;
    int n, m, k;
    cin >> n >> m >> k;
    for (int i = 0; i < k; i++) {
        cin >> cost[i];
    }
    for (int i = 0; i < k; i++) {
        cin >> s[i];
    }
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < s[i]; j++) {
            int u;
            cin >> u;
            u--;
            items[u].push_back(i);
        }
    }
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        adj[u].push_back(make_pair(v, w));
        adj[v].push_back(make_pair(u, w));
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < k; j++) {
            int x = calc(j, items[i]);
            if (x != j) {
                graph[i + n * j].push_back(make_pair(i + n * x, 0));
            }
            graph[i + n * j].push_back(make_pair(i + n * (j + 1), cost[j]));
            for (pair<int, int> v : adj[i]) {
                graph[i + n * j].push_back(make_pair(v.first + n * j, v.second));
            }
            dist[i + n * j] = INF;
        }
    }
    for (int i = 0; i < n; i++) {
        dist[i + n * k] = INF;
    }
    dist[0] = 0;
    priority_queue<pair<long long, int>> pq;
    pq.push(make_pair(0, 0));
    while (pq.size()) {
        int ind = pq.top().second; long long wt = -pq.top().first;
        pq.pop();
        for (pair<int, int> v : graph[ind]) {
            if (wt + v.second < dist[v.first]) {
                dist[v.first] = wt + v.second;
                pq.push(make_pair(-dist[v.first], v.first));
            }
        }
    }
    long long ans = 1e18;
    for (int i = 0; i < n; i++) {
        ans = min(ans, dist[i + n * k]);
    }
    cout << ans;
    return 0;
}
