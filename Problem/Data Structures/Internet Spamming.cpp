//https://www.spoj.com/problems/SPAM_ATX/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 2e5 + 5;

int a[N];
int segtree[4 * N];
int idx = 0;

void query(int l, int r, int val, int node) {
    if (segtree[node] < val) {
        idx = -1;
        return;
    }
    if (l == r) {
        idx = l;
        segtree[node] -= val;
        return;
    }
    int mid = (l + r) / 2;
    if (segtree[2 * node + 1] >= val) {
        query(l, mid, val, 2 * node + 1);
    } else {
        query(mid + 1, r, val, 2 * node + 2);
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
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(0, n - 1, 0);
    for (int i = 0; i < q; i++) {
        int x;
        cin >> x;
        query(0, n - 1, x, 0);
        cout << idx + 1 << " ";
    }
    return 0;
}
