//https://dmoj.ca/problem/coci15c3p5
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

typedef long long ll;

const int N = 1e5 + 5;
const int K = 50;
const int INF = 1e9;

int a[N];
int segtree[4 * N];
int mx[50][4 * N];
int mn[50][4 * N];

set<int> pos[4 * N];
vector<pair<long long, int>> masks[4 * N];

void build(int l, int r, int k, int node) {
    if (l == r) {
        for (int i = 0; i < k; i++) {
            mn[i][node] = INF;
            mx[i][node] = -1;
        }
        mx[a[l]][node] = l;
        mn[a[l]][node] = l;
        segtree[node] = ((k == 1) ? 1 : INF);
        masks[node].push_back(make_pair(1ll << a[l], 1));
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, k, 2 * node + 1);
    build(mid + 1, r, k, 2 * node + 2);
    segtree[node] = min(segtree[2 * node + 1], segtree[2 * node + 2]);
    for (int i = 0; i < k; i++) {
        mn[i][node] = min(mn[i][2 * node + 1], mn[i][2 * node + 2]);
        mx[i][node] = max(mx[i][2 * node + 1], mx[i][2 * node + 2]);
    }

    long long need = (1ll << k) - 1;
    int lf = 0, rt = masks[2 * node + 2].size() - 1;
    while (lf < masks[2 * node + 1].size() && rt >= 0) {
        long long mask = masks[2 * node + 1][lf].first | masks[2 * node + 2][rt].first;
        if (mask == need) {
            segtree[node] = min(segtree[node], masks[2 * node + 1][lf].second +  masks[2 * node + 2][rt].second);
            rt--;
        } else {
            lf++;
        }
    }
    if (node % 2 == 0) {
        for (int i = 0; i < k; i++) {
            if (mn[i][node] != INF) {
                pos[node].insert(mn[i][node]);
            }
        }
        long long mask = 0;
        for (auto it = pos[node].begin(); it != pos[node].end(); ++it) {
            long long nx = mask | (1ll << a[*it]);
            if (nx != mask) {
                mask = nx;
                masks[node].push_back(make_pair(mask, *it - l + 1));
            }
        }
    } else {
        for (int i = 0; i < k; i++) {
            if (mx[i][node] != -1) {
                 pos[node].insert(mx[i][node]);
            }
        }
        long long mask = 0;
        for (auto it = pos[node].rbegin(); it != pos[node].rend(); ++it) {
            long long nx = mask | (1ll << a[*it]);
            if (nx != mask) {
                mask = nx;
                masks[node].push_back(make_pair(mask, r - *it + 1));
            }
        }
    }
    return;
}

void update(int l, int r, int node, int k, int ind, int val, int old) {
    if (l == r) {
        mx[a[l]][node] = -1;
        mn[a[l]][node] = INF;
        a[l] = val;
        mx[a[l]][node] = l;
        mn[a[l]][node] = l;
        segtree[node] = ((k == 1) ? 1 : INF);
        masks[node].push_back(make_pair(1ll << a[l], 1));
        return;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        update(l, mid, 2 * node + 1, k, ind, val, old);
    } else {
        update(mid + 1, r, 2 * node + 2, k, ind, val, old);
    }
    segtree[node] = min(segtree[2 * node + 1], segtree[2 * node + 2]);
    int oldpos = ((node % 2 == 0) ? mn[old][node] : mx[old][node]);
    int valpos = ((node % 2 == 0) ? mn[val][node] : mx[val][node]);

    mn[old][node] = min(mn[old][2 * node + 1], mn[old][2 * node + 2]);
    mn[val][node] = min(mn[val][2 * node + 1], mn[val][2 * node + 2]);
    mx[old][node] = max(mx[old][2 * node + 1], mx[old][2 * node + 2]);
    mx[val][node] = max(mx[val][2 * node + 1], mx[val][2 * node + 2]);

    if (node % 2 == 0) {
        if (oldpos != mn[old][node] && oldpos != INF) {
            pos[node].erase(oldpos);
        }
        if (valpos != mn[val][node] && valpos != INF) {
            pos[node].erase(valpos);
        }
        if (oldpos != mn[old][node] && mn[old][node] != INF) {
            pos[node].insert(mn[old][node]);
        }
        if (valpos != mn[val][node] && mn[val][node] != INF) {
            pos[node].insert(mn[val][node]);
        }
    } else {
        if (oldpos != mx[old][node] && oldpos != -1) {
            pos[node].erase(oldpos);
        }
        if (valpos != mx[val][node] && valpos != -1) {
            pos[node].erase(valpos);
        }
        if (oldpos != mx[old][node] && mx[old][node] != -1) {
            pos[node].insert(mx[old][node]);
        }
        if (valpos != mx[val][node] && mx[val][node] != -1) {
            pos[node].insert(mx[val][node]);
        }
    }

    long long need = (1ll << k) - 1;
    int lf = 0, rt = masks[2 * node + 2].size() - 1;
    while (lf < masks[2 * node + 1].size() && rt >= 0) {
        long long mask = masks[2 * node + 1][lf].first | masks[2 * node + 2][rt].first;
        if (mask == need) {
            segtree[node] = min(segtree[node], masks[2 * node + 1][lf].second +  masks[2 * node + 2][rt].second);
            rt--;
        } else {
            lf++;
        }
    }

    if (node % 2 == 0) {
        if (oldpos != ind && mn[val][node] != ind) {
            return;
        }
        masks[node].clear();
        long long mask = 0;
        for (auto it = pos[node].begin(); it != pos[node].end(); ++it) {
            mask |= 1ll << a[*it];
            masks[node].push_back(make_pair(mask, *it - l + 1));
        }
    } else {
        if (oldpos != ind && mx[val][node] != ind) {
            return;
        }
        masks[node].clear();
        long long mask = 0;
        for (auto it = pos[node].rbegin(); it != pos[node].rend(); ++it) {
            mask |= 1ll << a[*it];
            masks[node].push_back(make_pair(mask, r - *it + 1));
        }
    }
    return;
}

int main() {
    //freopen("248.in", "r", stdin);
    //freopen("248.out", "w", stdout);
    IOS;
    int n, k, m;
    cin >> n >> k >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
    }
    build(0, n - 1, k, 0);
    for (int i = 0; i < m; i++) {
        int t;
        cin >> t;
        if (t == 2) {
            cout << ((segtree[0] == INF) ? -1 : segtree[0]) << endl;
        } else {
            int j, x;
            cin >> j >> x;
            j--, x--;
            if (a[j] != x) {
                update(0, n - 1, 0, k, j, x, a[j]);
            }
        }
    }
    return 0;
}
