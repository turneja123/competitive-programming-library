//https://atcoder.jp/contests/abc428/tasks/abc428_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

struct Node {
    int setValid;
    int setVal;
    int val;
    Node() {
        setValid = 0, setVal = 0, val = 0;
    }
};

int a[N];
Node segtree[4 * N];

Node combine(Node left, Node right) {
    Node node = Node();
    node.val = min(left.val, right.val);
    return node;
}



void apply(int node, int l, int r) {
    if (segtree[node].setValid == 1) {
        segtree[node].val = segtree[node].setVal;
    } else if (segtree[node].setValid == 2) {
        segtree[node].val = segtree[node].setVal - a[r];
    }

    if (l != r && segtree[node].setValid) {
        segtree[2 * node + 1].setValid = segtree[node].setValid;
        segtree[2 * node + 2].setValid = segtree[node].setValid;
        segtree[2 * node + 1].setVal = segtree[node].setVal;
        segtree[2 * node + 2].setVal = segtree[node].setVal;

    }
    segtree[node].setValid = 0;
    segtree[node].setVal = 0;
}


void setUpdate(int node, int l, int r, int lq, int rq, int val, int f) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[node].setValid = f;
        segtree[node].setVal = val;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    setUpdate(node * 2 + 1, l, mid, lq, rq, val, f);
    setUpdate(node * 2 + 2, mid + 1, r, lq, rq, val, f);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int getSum(int l, int r, int ind, int node) {
    apply(node, l, r);
    if (l == r) {
        return segtree[node].val;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        return getSum(l, mid, ind, 2 * node + 1);
    } else {
        return getSum(mid + 1, r, ind, 2 * node + 2);
    }
}


int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int t, j;
        cin >> t >> j;
        if (t == 1) {
            j--;
            int x = getSum(0, n - 1, j, 0);
            setUpdate(0, 0, n - 1, 0, j, x, 1);
        } else if (t == 2) {
            j--;
            int x = getSum(0, n - 1, j, 0) + a[j];
            setUpdate(0, 0, n - 1, 0, j, x, 2);
        } else {
            int l = 0, r = n - 1, ans = n;
            while (l <= r) {
                int mid = (l + r) / 2;
                int x = getSum(0, n - 1, mid, 0);
                if (j >= x && j < x + a[mid]) {
                    ans = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            cout << n - ans << endl;
        }
    }


    return 0;
}
