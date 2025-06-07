//https://codeforces.com/contest/2064/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long M = 998244353;

int a[N];
int c[N];
vector<int> pos[N];

int segtree[4 * N];

int parent[N];
int sz[N];
int mn[N];
int mx[N];
int slots[N];

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
    mn[a] = min(mn[a], mn[b]);
    mx[a] = max(mx[a], mx[b]);
    slots[a] += slots[b];
    parent[b] = a;
}

int rmq(int l, int r, int lq, int rq, int node) {
    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    if (l > rq || r < lq) {
        return -N;
    }

    int mid = (l + r) / 2;
    return max(rmq(l, mid, lq, rq, 2 * node + 1),
               rmq(mid + 1, r, lq, rq, 2 * node + 2));
}

void update(int l, int r, int ind, ll val, int node) {
    if (l == r) {
        segtree[node] = val;
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2);
    }
    segtree[node] = max(segtree[2 * node + 1], segtree[2 * node + 2]);
}


void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = a[l];
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = max(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            parent[i] = i;
            mn[i] = i;
            mx[i] = i;
            sz[i] = 1;
            slots[i] = 0;
        }
        for (int i = 0; i < n; i++) {
            cin >> c[i];
            pos[c[i]].push_back(i);
        }
        build(0, n - 1, 0);
        long long ans = 1;
        for (int i = 1; i <= n; i++) {
            if (pos[i].empty()) {
                continue;
            }
            vector<pair<int, int>> inds;
            for (int j : pos[i]) {
                update(0, n - 1, j, 0, 0);
                inds.push_back(make_pair(a[j], j));
            }
            sort(inds.begin(), inds.end());
            for (auto [_, j] : inds) {
                while (1) {
                    int u = dsu_find(j);
                    int r = upper_bound(pos[i].begin(), pos[i].end(), mx[u]) - pos[i].begin();
                    if (r == pos[i].size() || rmq(0, n - 1, mn[u], pos[i][r], 0) > a[j]) {
                        break;
                    }
                    dsu_unite(u, dsu_find(pos[i][r]));
                }
                while (1) {
                    int u = dsu_find(j);
                    int l = lower_bound(pos[i].begin(), pos[i].end(), mn[u]) - pos[i].begin() - 1;
                    if (l == -1 || rmq(0, n - 1, pos[i][l], mx[u], 0) > a[j]) {
                        break;
                    }
                    dsu_unite(u, dsu_find(pos[i][l]));
                }
                int u = dsu_find(j);
                ans = (ans * (sz[u] - slots[u])) % M;
                slots[u]++;
            }
            for (int j : pos[i]) {
                update(0, n - 1, j, a[j], 0);
            }
            pos[i].clear();
        }
        cout << ans << endl;
    }
    return 0;
}
