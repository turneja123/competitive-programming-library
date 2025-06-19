//https://dmoj.ca/problem/othscc4p4
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long M = 1e9;

long long lazy[4 * N];
long long val[4 * N];

int a[N];

void apply(int l, int r, int node) {
    val[node] = val[node] * lazy[node] % M;
    if (l != r) {
        lazy[2 * node + 1] = lazy[2 * node + 1] * lazy[node] % M;
        lazy[2 * node + 2] = lazy[2 * node + 2] * lazy[node] % M;
    }
    lazy[node] = 1;
}

void upd(int l, int r, int ind, int x, int node) {
    apply(l, r, node);
    if (l == r) {
        val[node] = (val[node] + x + M) % M;
        return;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        upd(l, mid, ind, x, 2 * node + 1);
    } else {
        upd(mid + 1, r, ind, x, 2 * node + 2);
    }
}

long long get_val(int l, int r, int ind, int node) {
    apply(l, r, node);
    if (l == r) {
        return val[node];
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        return get_val(l, mid, ind, 2 * node + 1);
    }
    return get_val(mid + 1, r, ind, 2 * node + 2);
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    lazy[node] = 1;
    if (l == r) {
        val[node] = a[l] % M;
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(0, n - 1, 0);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int j, x;
            cin >> j >> x;
            j--;
            upd(0, n - 1, j, (x + M) % M, 0);
        } else if (t == 2) {
            int x;
            cin >> x;
            lazy[0] = lazy[0] * (x + M) % M;
        } else {
            int j;
            cin >> j;
            j--;
            cout << get_val(0, n - 1, j, 0) << endl;
        }
    }
    return 0;
}
