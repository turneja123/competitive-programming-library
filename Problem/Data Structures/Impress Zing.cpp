//https://www.spoj.com/problems/ZING01/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

string a;
int segtree[26][4 * N];
int setVal[4 * N];
bool setValid[4 * N];

int ans;

void compose(int parent, int child) {
    if (setValid[parent]) {
        setValid[child] = 1;
        setVal[child] = setVal[parent];
    }
}

void apply(int node, int l, int r) {
    if (setValid[node]) {
        for (int i = 0; i < 26; i++) {
            if (setVal[node] == i) {
                segtree[i][node] = r - l + 1;
            } else {
                segtree[i][node] = 0;
            }
        }
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
    for (int i = 0; i < 26; i++) {
        segtree[i][node] = segtree[i][node * 2 + 1] + segtree[i][node * 2 + 2];
    }
}

void query(int l, int r, int node, int i, int k) {
    apply(node, l, r);
    if (segtree[i][node] < k) {
        ans = -2;
        return;
    }
    if (l == r) {
        ans = l;
        return;
    }
    int mid = (l + r) / 2;
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    if (segtree[i][2 * node + 1] >= k) {
        query(l, mid, 2 * node + 1, i, k);
    } else {
        query(mid + 1, r, 2 * node + 2, i, k - segtree[i][2 * node + 1]);
    }
    return;
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[a[l] - 'a'][node] = 1;
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1);
    build(mid + 1, r, node * 2 + 2);
    for (int i = 0; i < 26; i++) {
        segtree[i][node] = segtree[i][node * 2 + 1] + segtree[i][node * 2 + 2];
    }
}

int main() {
    IOS;
    cin >> a;
    int n = a.size(), q;
    build(0, n - 1, 0);
    cin >> q;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            char x;
            cin >> x;
            int val = x - 'a';
            setUpdate(0, 0, n - 1, l, r, val);
        } else {
            int k;
            cin >> k;
            char x;
            cin >> x;
            int val = x - 'a';
            query(0, n - 1, 0, val, k);
            cout << ans + 1 << endl;
        }
    }
    return 0;
}
