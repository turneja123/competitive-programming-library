//https://codeforces.com/contest/786/problem/B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const ll INF = 1e18;

int idx = 0;
int L[N];
int R[N];
ll dist[N];
int root[2];

vector<pair<int, int>> adj[N];

void upd(int l, int r, int lq, int rq, int node, int f, int v, int wt) {
    if (l > rq || r < lq) {
        return;
    }

    if (lq <= l && rq >= r) {
        if (f == 0) {
            adj[v].push_back({node, wt});
        } else {
            adj[node].push_back({v, wt});
        }
        return;
    }



    int mid = (l + r) / 2;
    upd(l, mid, lq, rq, L[node], f, v, wt);
    upd(mid + 1, r, lq, rq, R[node], f, v, wt);
}

void build(int l, int r, int node, int f) {
    if (l == r) {
        if (f == 0) {
            adj[node].push_back({l, 0});
        } else {
            adj[l].push_back({node, 0});
        }
        return;
    }

    int mid = (l + r) / 2;
    L[node] = idx;
    build(l, mid, idx++, f);
    R[node] = idx;
    build(mid + 1, r, idx++, f);
    if (f == 0) {
        adj[node].push_back({L[node], 0});
        adj[node].push_back({R[node], 0});
    } else {
        adj[L[node]].push_back({node, 0});
        adj[R[node]].push_back({node, 0});
    }
}


int main() {
    IOS;
    int n, q, s;
    cin >> n >> q >> s;
    s--;
    idx = n;
    root[0] = idx++;
    build(0, n - 1, root[0], 0);
    root[1] = idx++;
    build(0, n - 1, root[1], 1);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int u, v, wt;
            cin >> u >> v >> wt;
            u--, v--;
            adj[u].push_back({v, wt});
        } else {
            t -= 2;
            int v, l, r, wt;
            cin >> v >> l >> r >> wt;
            v--, l--, r--;
            upd(0, n - 1, l, r, root[t], t, v, wt);
        }
    }
    for (int i = 0; i < N; i++) {
        dist[i] = INF;
    }
    dist[s] = 0;
    priority_queue<pair<ll, int>> pq;
    pq.push({0, s});
    while (pq.size()) {
        auto [d, u] = pq.top();
        pq.pop();
        d = -d;
        if (d != dist[u]) {
            continue;
        }
        for (auto [v, wt] : adj[u]) {
            if (dist[v] > dist[u] + wt) {
                dist[v] = dist[u] + wt;
                pq.push({-dist[v], v});
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << (dist[i] == INF ? -1 : dist[i]) << " ";
    }

    return 0;
}

