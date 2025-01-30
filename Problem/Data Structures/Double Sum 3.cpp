//https://atcoder.jp/contests/abc390/tasks/abc390_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

int a[N];
int l[N];

ll segtree[4 * N];
ll lazy[4 * N];

void compose(int parent, int child) {
    lazy[child] += lazy[parent];
}

void apply(int node, int l, int r) {
    segtree[node] += (r - l + 1) * lazy[node];
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
    segtree[node] = segtree[node * 2 + 1] + segtree[node * 2 + 2];
}

ll getSum(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return 0;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree[node];
    }
    int mid = (l + r) / 2;
    return getSum(l, mid, lq, rq, 2 * node + 1) +
           getSum(mid + 1, r, lq, rq, 2 * node + 2);
}


int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < N; i++) {
        l[i] = -1;
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        int r = l[a[i]];
        incUpdate(0, 0, n - 1, r + 1, i, 1);
        if (l[a[i] - 1] != -1 && l[a[i] - 1] > r) {
            incUpdate(0, 0, n - 1, r + 1, l[a[i] - 1], -1);
        }
        if (l[a[i] + 1] != -1 && l[a[i] + 1] > r) {
            incUpdate(0, 0, n - 1, r + 1, l[a[i] + 1], -1);
        }
        l[a[i]] = i;
        ans += getSum(0, n - 1, 0, i, 0);
    }
    cout << ans;
    return 0;
}
