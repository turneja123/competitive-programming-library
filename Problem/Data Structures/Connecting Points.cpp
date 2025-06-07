//https://atcoder.jp/contests/abc409/tasks/abc409_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3005;
const int INF = 2e9;

int parent[N];
int sz[N];
pair<int, int> a[N];
int dist[N];

int dsu_find(int a) {
    if (parent[a] == a) {
        return a;
    }
    return parent[a] = dsu_find(parent[a]);
}

void dsu_unite(int a, int b) {
    if (sz[b] > sz[a]) {
        swap(a, b);
    }
    sz[a] += sz[b];
    parent[b] = a;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
        parent[i] = i;
        sz[i] = 1;
    }
    priority_queue<pair<int, pair<int, int>>> pq;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int d = abs(a[i].first - a[j].first) + abs(a[i].second - a[j].second);
            pq.push(make_pair(-d, make_pair(i, j)));
        }
    }
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            cin >> a[n].first >> a[n].second;
            parent[n] = n;
            for (int j = 0; j < n; j++) {
                dist[j] = INF;
            }
            for (int j = 0; j < n; j++) {
                int u = dsu_find(j);
                int d = abs(a[n].first - a[j].first) + abs(a[n].second - a[j].second);
                dist[u] = min(dist[u], d);
            }
            for (int j = 0; j < n; j++) {
                if (dsu_find(j) == j) {
                    pq.push(make_pair(-dist[j], make_pair(j, n)));
                }
            }
            n++;
        } else if (t == 2) {
            while (pq.size()) {
                auto [u, v] = pq.top().second;
                u = dsu_find(u), v = dsu_find(v);
                if (u != v) {
                    break;
                }
                pq.pop();
            }
            if (pq.size() == 0) {
                cout << -1 << endl;
                continue;
            }
            int d = pq.top().first;
            cout << -d << endl;
            while (pq.size() && pq.top().first == d) {
                auto [u, v] = pq.top().second;
                pq.pop();
                u = dsu_find(u), v = dsu_find(v);
                if (u != v) {
                    dsu_unite(u, v);
                }
            }
        } else {
            int u, v;
            cin >> u >> v;
            u--, v--;
            u = dsu_find(u), v = dsu_find(v);
            if (u == v) {
                cout << "Yes" << endl;
            } else {
                cout << "No" << endl;
            }
        }
    }
    return 0;
}
