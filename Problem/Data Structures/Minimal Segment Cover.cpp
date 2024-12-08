//https://codeforces.com/contest/1175/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const int K = 20;

int segtree[4 * N];
int setVal[4 * N];
bool setValid[4 * N];

void compose(int parent, int child) {
    if (setValid[parent]) {
        if (setValid[child]) {
            setVal[child] = max(setVal[child], setVal[parent]);
        } else {
            setValid[child] = 1;
            setVal[child] = setVal[parent];
        }
    }
}

void apply(int node, int l, int r) {
    if (setValid[node]) {
        segtree[node] = max(segtree[node], setVal[node]);
    }
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    setValid[node] = false;
}

void setUpdate(int node, int l, int r, int lq, int rq, int val) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        if (setValid[node]) {
            setVal[node] = max(setVal[node], val);
        } else {
            setValid[node] = true;
            setVal[node] = val;
        }
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    setUpdate(node * 2 + 1, l, mid, lq, rq, val);
    setUpdate(node * 2 + 2, mid + 1, r, lq, rq, val);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = max(segtree[node * 2 + 1], segtree[node * 2 + 2]);
}

int getMax(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return -1;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree[node];
    }
    int mid = (l + r) / 2;
    return max(getMax(l, mid, lq, rq, 2 * node + 1),
           getMax(mid + 1, r, lq, rq, 2 * node + 2));
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    setVal[node] = 0;
    setValid[node] = 0;
    if (l == r) {
        segtree[node] = -1;
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree[node] = max(segtree[node * 2 + 1], segtree[node * 2 + 2]);
}

int a[N];
int up[K][N];

int main() {
    IOS;
    build(0, N - 1, 0);
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        setUpdate(0, 0, N - 1, l, r, r);
    }
    for (int i = 0; i < N; i++) {
        a[i] = getMax(0, N - 1, i, i, 0);
        if (a[i] != -1) {
            up[0][i] = a[i];
        } else {
            up[0][i] = -1;
        }
    }
    for (int k = 1; k < K; k++) {
        for (int i = 0; i < N; i++) {
            int j = up[k - 1][i];
            if (j != -1) {
                up[k][i] = up[k - 1][j];
            } else {
                up[k][i] = -1;
            }
        }
    }
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        int ans = 0;
        for (int k = K - 1; k >= 0; k--) {
            if (up[k][l] != -1 && up[k][l] < r) {
                ans += 1 << k;
                l = up[k][l];
            }
        }
        if (up[0][l] >= r) {
            cout << ans + 1 << endl;
        } else {
            cout << -1 << endl;
        }
    }
    return 0;
}
