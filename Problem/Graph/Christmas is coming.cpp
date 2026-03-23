//https://www.spoj.com/problems/QTGIFT3/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const ll INF = 1e18;
const ll M = 1e15;

int idx = 0;
int L[N];
int R[N];
ll dist[N];
ll ways[N];
int root;

vector<pair<int, int>> adj[N];

void upd(int l, int r, int lq, int rq, int node, int v, int wt) {
    if (l > rq || r < lq) {
        return;
    }

    if (lq <= l && rq >= r) {
        adj[v].push_back({node, wt});
        return;
    }
    int mid = (l + r) / 2;
    upd(l, mid, lq, rq, L[node], v, wt);
    upd(mid + 1, r, lq, rq, R[node], v, wt);
}

void build(int l, int r, int node) {
    if (l == r) {
        adj[node].push_back({l, 0});
        return;
    }

    int mid = (l + r) / 2;
    L[node] = idx;
    build(l, mid, idx++);
    R[node] = idx;
    build(mid + 1, r, idx++);
    adj[node].push_back({L[node], 0});
    adj[node].push_back({R[node], 0});
}


int main() {
    IOS;
    int n, s, t;
    cin >> n >> s >> t;
    s--, t--;
    idx = n;
    root = idx++;
    build(0, n - 1, root);
    for (int i = 0; i < n; i++) {
        int v = i;
        int l, r, wt;
        cin >> l >> r >> wt;
        l--, r--;
        upd(0, n - 1, l, r, root, v, wt);

    }
    for (int i = 0; i < N; i++) {
        dist[i] = INF;
    }
    dist[s] = 0;
    ways[s] = 1;
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
                ways[v] = ways[u];
                pq.push({-dist[v], v});
            } else if (dist[v] == dist[u] + wt) {
                ways[v] = (ways[v] + ways[u]) % M;
            }
        }
    }
    cout << dist[t] << " " << ways[t];
    return 0;
}

