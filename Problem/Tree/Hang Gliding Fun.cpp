//solution for https://dmoj.ca/problem/gcc16p3
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int MAX = 1e9;

list <int> adj[N];

int sz[N];
int tour[N];
int parent[N];
ll h[N], v[N];
pair<ll, ll> d[N];
tuple<ll, ll, ll> queries[N];
ll ans[N];
bool vis[N];
int euler = 0;

ll segtree[4 * N];
ll lazy[4 * N];

int dfs(int v, int ct) {
    tour[v] = euler++;
    vis[v] = true;
    for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
        if (!vis[*it]) {
            parent[*it] = v;
            ct += dfs(*it, 1);
        }
    }
    return sz[v] = ct;
}

void compose(int parent, int child) {
    lazy[child] += lazy[parent];
}

void apply(int node, int l, int r) {
    segtree[node] += lazy[node];
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    lazy[node] = 0;
}

void incUpdate(int node, int l, int r, int lq, int rq, ll add) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        lazy[node] += add;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    incUpdate(node * 2 + 1, l, mid, lq, rq, add);
    incUpdate(node * 2 + 2, mid + 1, r, lq, rq, add);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = max(segtree[node * 2 + 1], segtree[node * 2 + 2]);
}

ll getMax(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return 0;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree[node];
    }

    int mid = (l + r) / 2;
    return max(getMax(l, mid, lq, rq, 2 * node + 1),
           getMax(mid + 1, r, lq, rq, 2 * node + 2));
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    h[0] = MAX;

    for (int i = 1; i < n + 1; i++) {
        cin >> h[i] >> v[i] >> d[i].first;
        d[i].second = i;
    }

    stack<pair<int, int>> s;
    s.push({h[0], 0});
    for (int i = 1; i < n + 1; i++) {
        while (s.top().first <= h[i]) {
            s.pop();
        }
        adj[s.top().second].push_back(i);
        adj[i].push_back(s.top().second);
        s.push({h[i], i});
    }
    dfs(0, 1);

    for (int i = 0; i < q; i++) {
        cin >> get<1>(queries[i]) >> get<0>(queries[i]);
        get<2>(queries[i]) = i;
    }
    sort(queries, queries + q);

    int l = 0;
    sort(d, d + n + 1);

    for (int i = 0; i < q; i++) {
        int b = get<1>(queries[i]), m = get<0>(queries[i]);
        while (l < n + 1 && d[l].first <= m) {
            int city = d[l].second;
            incUpdate(0, 0, n, tour[city], tour[city] + sz[city] - 1, v[city]);
            l++;
        }
        ans[get<2>(queries[i])] = getMax(0, n, tour[b], tour[b] + sz[b] - 1, 0) - getMax(0, n, tour[parent[b]], tour[parent[b]], 0);
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }

    return 0;
}
