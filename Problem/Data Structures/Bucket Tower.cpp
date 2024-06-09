//https://www.spoj.com/problems/MWPZ034/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const int M = 1e4 + 5;

pair<int, int> a[N];


int segtree[4 * M];
int lazy[4 * M];

void compose(int parent, int child) {
    lazy[child] = max(lazy[child], lazy[parent]);
}

void apply(int node, int l, int r) {
    segtree[node] = max(segtree[node], lazy[node]);
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    lazy[node] = 0;
}

void maxUpdate(int node, int l, int r, int lq, int rq, int add) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        lazy[node] = max(lazy[node], add);
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    maxUpdate(node * 2 + 1, l, mid, lq, rq, add);
    maxUpdate(node * 2 + 2, mid + 1, r, lq, rq, add);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = max(segtree[node * 2 + 1], segtree[node * 2 + 2]);
}

int getMax(int l, int r, int ind, int node) {
    apply(node, l, r);
    if (l == r) {
        return segtree[node];
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        return getMax(l, mid, ind, 2 * node + 1);
    } else {
        return getMax(mid + 1, r, ind, 2 * node + 2);
    }
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    segtree[node] = 0;
    lazy[node] = 0;
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i].first >> a[i].second;
        }
        build(0, M - 1, 0);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int h = getMax(0, M - 1, a[i].first, 0), cur = h + a[i].second;
            ans = max(ans, cur);
            maxUpdate(0, 0, M - 1, a[i].first, M - 1, cur);
            maxUpdate(0, 0, M - 1, 0, a[i].first - 1, h);
        }
        cout << ans << endl;
    }

    return 0;
}
