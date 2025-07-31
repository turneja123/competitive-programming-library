//https://olympicode.rs/problem/30
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const int K = 21;

int table[K][N];
int mx[K][N];

int a[N];
vector<tuple<int, int, int>> queries[N];
int ans[N];

void build(int n) {
    for (int i = 1; i <= n; i++) {
        table[0][i] = a[i - 1];
        mx[0][i] = i - 1;
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            if (table[k - 1][i] > table[k - 1][i + (1 << (k - 1))]) {
                table[k][i] = table[k - 1][i];
                mx[k][i] = mx[k - 1][i];
            } else {
                table[k][i] = table[k - 1][i + (1 << (k - 1))];
                mx[k][i] = mx[k - 1][i + (1 << (k - 1))];
            }
        }
    }
    return;
}

int query(int l, int r) {
    l++, r++;
    int k = 31 - __builtin_clz(r - l + 1);
    if (table[k][l] > table[k][r - (1 << k) + 1]) {
        return mx[k][l];
    }
    return mx[k][r - (1 << k) + 1];
}


struct Node {
    bool setValid;
    int setVal;
    int sum;
    int lazy;
    Node() {
        setValid = 0, setVal = 0, lazy = 0;
    }
    Node(int x) : setValid(0), setVal(0), sum(x), lazy(0) {}
};


Node combine(Node left, Node right) {
    Node node = Node();
    node.sum = max(left.sum, right.sum);
    return node;
}

struct Seg {
    Node segtree[4 * N];
    void compose(int parent, int child) {
        if (segtree[parent].setValid) {
            segtree[child].setValid = 1;
            segtree[child].setVal = segtree[parent].setVal;
            segtree[child].lazy = segtree[parent].lazy;
        } else {
            segtree[child].lazy += segtree[parent].lazy;
        }
    }

    void apply(int node, int l, int r) {
        if (segtree[node].setValid) {
            segtree[node].sum = segtree[node].setVal;
        }
        segtree[node].sum += segtree[node].lazy;
        if (l != r) {
            compose(node, 2 * node + 1);
            compose(node, 2 * node + 2);
        }
        segtree[node].setValid = false;
        segtree[node].lazy = 0;
    }

    void incUpdate(int node, int l, int r, int lq, int rq, int add) {
        if (l > rq || lq > r) {
            return;
        }
        if (l >= lq && r <= rq) {
            segtree[node].lazy += add;
            return;
        }
        apply(node, l, r);
        int mid = (l + r) / 2;
        incUpdate(node * 2 + 1, l, mid, lq, rq, add);
        incUpdate(node * 2 + 2, mid + 1, r, lq, rq, add);
        apply(2 * node + 1, l, mid);
        apply(2 * node + 2, mid + 1, r);
        segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
    }

    void setUpdate(int node, int l, int r, int lq, int rq, int val) {
        if (l > rq || lq > r) {
            return;
        }
        if (l >= lq && r <= rq) {
            segtree[node].setValid = true;
            segtree[node].setVal = val;
            segtree[node].lazy = 0;
            return;
        }
        apply(node, l, r);
        int mid = (l + r) / 2;
        setUpdate(node * 2 + 1, l, mid, lq, rq, val);
        setUpdate(node * 2 + 2, mid + 1, r, lq, rq, val);
        apply(2 * node + 1, l, mid);
        apply(2 * node + 2, mid + 1, r);
        segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
    }

    int getSum(int l, int r, int lq, int rq, int node) {
        if (l > rq || lq > r) {
            return 0;
        }
        apply(node, l, r);
        if (l >= lq && r <= rq) {
            return segtree[node].sum;
        }
        int mid = (l + r) / 2;
        return max(getSum(l, mid, lq, rq, 2 * node + 1), getSum(mid + 1, r, lq, rq, 2 * node + 2));
    }
};

Seg L;
Seg R;

void calc(int l, int r, int n) {
    if (l > r) {
        return;
    }
    int mid = query(l, r);
    calc(l, mid - 1, n);
    calc(mid + 1, r, n);
    for (auto [lq, rq, i] : queries[mid]) {
        if (lq < mid) {
            ans[i] = max(ans[i], L.getSum(0, n - 1, lq, mid - 1, 0));
        }
        if (mid < rq) {
            ans[i] = max(ans[i], R.getSum(0, n - 1, mid + 1, rq, 0));
        }
    }
    int y = 1 + ((mid == r) ? 0 : R.getSum(0, n - 1, mid + 1, r, 0));
    int z = 1 + ((l == mid) ? 0 : L.getSum(0, n - 1, l, mid - 1, 0));
    if (l < mid) {
        L.incUpdate(0, 0, n - 1, l, mid - 1, 1);
    }
    L.setUpdate(0, 0, n - 1, mid, mid, y);
    if (mid < r) {
        R.incUpdate(0, 0, n - 1, mid + 1, r, 1);
    }
    R.setUpdate(0, 0, n - 1, mid, mid, z);
    return;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(n);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        int mid = query(l, r);
        queries[mid].push_back({l, r, i});
    }
    calc(0, n - 1, n);
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }

    return 0;
}
