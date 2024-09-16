//https://dmoj.ca/problem/bts24p3
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 3e5 + 5;

int a[N], b[N];
long long segtree[4 * N];

long long ans = 0;

void update(int l, int r, int node, int ind, int x) {
    if (l == r) {
        segtree[node] = x;
        return;
    }
    int mid = (l + r) / 2;
    ans -= (segtree[2 * node + 1] - segtree[2 * node + 2]) * (segtree[2 * node + 1] - segtree[2 * node + 2]);
    if (ind <= mid) {
        update(l, mid, 2 * node + 1, ind, x);
    } else {
        update(mid + 1, r, 2 * node + 2, ind, x);
    }
    ans += (segtree[2 * node + 1] - segtree[2 * node + 2]) * (segtree[2 * node + 1] - segtree[2 * node + 2]);
    segtree[node] = max(segtree[2 * node + 1], segtree[2 * node + 2]);
    return;
}

void build(int l, int r, int node) {
    if (l == r) {
        segtree[node] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    ans += (segtree[2 * node + 1] - segtree[2 * node + 2]) * (segtree[2 * node + 1] - segtree[2 * node + 2]);
    segtree[node] = max(segtree[2 * node + 1], segtree[2 * node + 2]);
    return;
}


int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 1; i < n; i++) {
        cin >> a[i];
        b[a[i]]++;
    }
    int d = 0;
    for (int i = 1; i <= n; i++) {
        if (b[i] == 0) {
            d = i;
        }
    }
    a[0] = d;
    build(0, n - 1, 0);
    cout << ans << " ";
    for (int i = 0; i < n - 1; i++) {
        update(0, n - 1, 0, i, a[i + 1]);
        update(0, n - 1, 0, i + 1, a[i]);
        swap(a[i], a[i + 1]);
        cout << ans << " ";
    }



    return 0;
}
