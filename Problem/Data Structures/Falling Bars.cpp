//https://atcoder.jp/contests/abc382/tasks/abc382_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 2e5 + 5;

tuple<int, int, int, int> a[N];

const int INF = 1e9;

int segtree[4 * N];
int setVal[4 * N];
bool setValid[4 * N];
int ans[N];

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

void setUpdate(int node, int l, int r, int lq, int rq, int val) {
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

int getMin(int l, int r, int lq, int rq, int node) {
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
	int n, m, k;
	cin >> n >> m >> k;
	for (int i = 0; i < k; i++) {
        int r, c, l;
        cin >> r >> c >> l;
        r--, c--;
        a[i] = make_tuple(r, c, c + l - 1, i);
	}
	sort(a, a + k);
	build(0, m - 1, 0);
	for (int i = k - 1; i >= 0; i--) {
        auto [rw, l, r, ind] = a[i];
        int mn = getMin(0, m - 1, l, r, 0);
        if (mn == INF) {
            mn = n - 1;
        } else {
            mn--;
        }
        ans[ind] = mn;
        setUpdate(0, 0, m - 1, l, r, mn);
	}
	for (int i = 0; i < k; i++) {
        cout << ans[i] + 1 << endl;
	}
	return 0;
}
