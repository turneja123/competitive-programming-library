//https://www.codechef.com/problems/XOP
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 60;

long long a[N];
int lf[K][2];

int segtree[4 * N];
int setVal[4 * N];
bool setValid[4 * N];

void compose(int parent, int child) {
    if (setValid[parent]) {
        setValid[child] = 1;
        setVal[child] = setVal[parent];
    }
}

void apply(int node, int l, int r) {
    if (setValid[node]) {
        segtree[node] = (r - l + 1) * setVal[node];
    }
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    setValid[node] = false;
}

void setUpdate(int node, int l, int r, int lq, int rq, int val) {
    if (l > rq || lq > r || lq > rq) {
        return;
    }
    if (l >= lq && r <= rq) {
        setValid[node] = true;
        setVal[node] = val;

        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    setUpdate(node * 2 + 1, l, mid, lq, rq, val);
    setUpdate(node * 2 + 2, mid + 1, r, lq, rq, val);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = segtree[node * 2 + 1] + segtree[node * 2 + 2];
}

int query(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return 0;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree[node];
    }
    int mid = (l + r) / 2;
    return query(l, mid, lq, rq, 2 * node + 1) + query(mid + 1, r, lq, rq, 2 * node + 2);
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    setVal[node] = 0;
    setValid[node] = 0;
    if (l == r) {
        segtree[node] = 1;
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree[node] = segtree[node * 2 + 1] + segtree[node * 2 + 2];
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
        }
        for (int j = 0; j < K; j++) {
            lf[j][0] = -1;
            lf[j][1] = -1;
        }
        build(0, n - 1, 0);
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            for (long long j = 0; j < K; j++) {
                long long c = a[i] & (1ll << j);
                if (c == 0) {
                    int l = lf[j][1];
                    lf[j][0] = i;
                    if (l == -1) {
                        continue;
                    }
                    long long can = (long long)i - ((1ll << j) - 1);
                    can = max(can, (long long)-1);
                    setUpdate(0, 0, n - 1, can + 1, l, 0);

                } else {
                    int l = lf[j][0];
                    lf[j][1] = i;
                    if (l == -1) {
                        continue;
                    }
                    long long can = (long long)i - ((1ll << j) - 1);
                    can = max(can, (long long)-1);
                    setUpdate(0, 0, n - 1, can + 1, l, 0);
                }
            }
            ans += query(0, n - 1, 0, i, 0);
        }
        cout << ans << endl;
    }

    return 0;
}
