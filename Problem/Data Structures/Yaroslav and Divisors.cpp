//https://codeforces.com/contest/301/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
pair<pair<int, int>, int> queries[N];
vector<pair<int, int>> pairs;

int pos[N];
int ans[N];
int segtree[4 * N];

int query(int l, int r, int lq, int rq, int node) {
    if (segtree[node] == 0) {
        return 0;
    }

    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    if (l > rq || r < lq) {
        return 0;
    }

    int mid = (l + r) / 2;
    return query(l, mid, lq, rq, 2 * node + 1) + query(mid + 1, r, lq, rq, 2 * node + 2);
}

void update(int l, int r, int ind, int node) {
    if (l == r) {
        segtree[node] = a[l];
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, 2 * node + 2);
    }
    segtree[node] = segtree[2 * node + 1] + segtree[2 * node + 2];
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
    segtree[node] = segtree[2 * node + 1] + segtree[2 * node + 2];
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        int k;
        cin >> k;
        pos[k] = i;
    }
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j += i) {
            int x = pos[i], y = pos[j];
            if (x > y) {
                swap(x, y);
            }
            pairs.push_back(make_pair(x, y));
            a[y]++;
        }
    }
    build(0, n - 1, 0);
    sort(pairs.begin(), pairs.end());
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        queries[i] = make_pair(make_pair(l, r), i);
    }
    sort(queries, queries + q);
    int j = 0;
    for (int i = 0; i < q; i++) {
        int l = queries[i].first.first, r = queries[i].first.second;
        while (j < pairs.size() && pairs[j].first < l) {
            a[pairs[j].second]--;
            update(0, n - 1, pairs[j].second, 0);
            j++;
        }
        ans[queries[i].second] = query(0, n - 1, l, r, 0);
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }

    return 0;
}
