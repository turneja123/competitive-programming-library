//https://codeforces.com/contest/2024/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;
const long long INF = 1e18;

long long a[N];
int b[N];

long long segtree[4 * N];
long long setVal[4 * N];
bool setValid[4 * N];

void compose(int parent, int child) {
    if (setValid[parent]) {
        if (setValid[child]) {
            setVal[child] = min(setVal[child], setVal[parent]);
        } else {
            setValid[child] = 1;
            setVal[child] = setVal[parent];
        }

    }
}

void apply(int node, int l, int r) {
    if (setValid[node]) {
        segtree[node] = min(segtree[node], setVal[node]);
    }
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    setValid[node] = false;
}

void setUpdate(int node, int l, int r, int lq, int rq, long long val) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        if (setValid[node]) {
            setVal[node] = min(setVal[node], val);
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
    segtree[node] = min(segtree[node * 2 + 1], segtree[node * 2 + 2]);
}

long long getMin(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return INF;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree[node];
    }
    int mid = (l + r) / 2;
    return min(getMin(l, mid, lq, rq, 2 * node + 1),
           getMin(mid + 1, r, lq, rq, 2 * node + 2));
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    setVal[node] = 0;
    setValid[node] = 0;
    if (l == r) {
        segtree[node] = INF;
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    segtree[node] = min(segtree[node * 2 + 1], segtree[node * 2 + 2]);
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
        for (int i = 0; i < n; i++) {
            cin >> b[i];
            b[i]--;
        }
        build(0, n - 1, 0);
        setUpdate(0, 0, n - 1, 0, 0, 0);
        long long ans = 0, sum = 0;
        for (int i = 0; i < n; i++) {
            sum += a[i];
            long long best = getMin(0, n - 1, i, i, 0);
            if (best == INF) {
                break;
            }
            ans = max(ans, sum - best);
            setUpdate(0, 0, n - 1, 0, b[i], best + a[i]);
        }
        cout << ans << endl;

    }

    return 0;
}
