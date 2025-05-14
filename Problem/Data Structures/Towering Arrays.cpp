//https://codeforces.com/contest/2071/problem/F
#pragma GCC optimize("Ofast,fast-math")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int INF = 1e9;

int a[N];

struct Node {
    int val;
    int lazy;
    int pos;
    Node() {
        lazy = 0;
        val = -INF;
        pos = -1;
    }
    Node(int _val, int _pos) {
        val = _val;
        pos = _pos;
        lazy = 0;
    }
};

Node segtree[4 * N];

void compose(int parent, int child) {
    segtree[child].lazy += segtree[parent].lazy;
}

void apply(int node, int l, int r) {
    segtree[node].val += segtree[node].lazy;
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    segtree[node].lazy = 0;
}

void incUpdate(int node, int l, int r, int lq, int rq, int add) {
    apply(node, l, r);
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[node].lazy += add;
        apply(node, l, r);
        return;
    }
    int mid = (l + r) / 2;
    incUpdate(node * 2 + 1, l, mid, lq, rq, add);
    incUpdate(node * 2 + 2, mid + 1, r, lq, rq, add);
    if (segtree[2 * node + 1].val > segtree[2 * node + 2].val) {
        segtree[node].val = segtree[2 * node + 1].val;
        segtree[node].pos = segtree[2 * node + 1].pos;
    } else {
        segtree[node].val = segtree[2 * node + 2].val;
        segtree[node].pos = segtree[2 * node + 2].pos;
    }
}

void setUpdate(int node, int l, int r, int ind, int val) {
    apply(node, l, r);
    if (l == r) {
        segtree[node] = Node(val, l);
        return;
    }

    int mid = (l + r) / 2;
    if (ind <= mid) {
        setUpdate(node * 2 + 1, l, mid, ind, val);
        apply(2 * node + 2, mid + 1, r);
    } else {
        setUpdate(node * 2 + 2, mid + 1, r, ind, val);
        apply(2 * node + 1, l, mid);
    }
    if (segtree[2 * node + 1].val > segtree[2 * node + 2].val) {
        segtree[node].val = segtree[2 * node + 1].val;
        segtree[node].pos = segtree[2 * node + 1].pos;
    } else {
        segtree[node].val = segtree[2 * node + 2].val;
        segtree[node].pos = segtree[2 * node + 2].pos;
    }
}

Node ret;

void query(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        if (segtree[node].val > ret.val) {
            ret.val = segtree[node].val;
            ret.pos = segtree[node].pos;
        }
        return;
    }
    int mid = (l + r) / 2;
    query(l, mid, lq, rq, 2 * node + 1);
    query(mid + 1, r, lq, rq, 2 * node + 2);
}

void build(int l, int r, int node, vector<int> &a) {
    if (l > r) {
        return;
    }
    segtree[node] = Node();
    if (l == r) {
        segtree[node] = Node(a[l], l);
        return;
    }
    int mid = (l + r) / 2;
    build(l, mid, node * 2 + 1, a);
    build(mid + 1, r, node * 2 + 2, a);
    if (segtree[2 * node + 1].val > segtree[2 * node + 2].val) {
        segtree[node].val = segtree[2 * node + 1].val;
        segtree[node].pos = segtree[2 * node + 1].pos;
    } else {
        segtree[node].val = segtree[2 * node + 2].val;
        segtree[node].pos = segtree[2 * node + 2].pos;
    }
}

bool solve(int n, int k, int p) {
    vector<int> a_l(n);
    vector<int> l(n, 0), r(n, 0);;
    for (int i = 0; i < n; i++) {
        a_l[i] = a[i] - p;
    }
    build(0, n - 1, 0, a_l);
    for (int i = 0; i < n; i++) {
        l[i] = (i == 0 ? 0 : l[i - 1]);
        if (a_l[i] < 0) {
            continue;
        }
        l[i]++;
        incUpdate(0, 0, n - 1, 0, i, 1);
        setUpdate(0, 0, n - 1, i, -INF);
        while (1) {
            ret.val = -INF, ret.pos = -1;
            query(0, n - 1, 0, i, 0);
            if (ret.val < 0) {
                break;
            }
            l[i]++;
            int j = ret.pos;
            incUpdate(0, 0, n - 1, 0, j, 1);
            setUpdate(0, 0, n - 1, j, -INF);
        }
        if (l[i] >= n - k) {
            return true;
        }
    }
    vector<int> a_r = a_l;
    reverse(a_r.begin(), a_r.end());
    build(0, n - 1, 0, a_r);
    for (int i = 0; i < n; i++) {
        r[n - 1 - i] = (i == 0 ? 0 : r[n - i]);
        if (a_r[i] < 0) {
            continue;
        }
        r[n - 1 - i]++;
        incUpdate(0, 0, n - 1, 0, i, 1);
        setUpdate(0, 0, n - 1, i, -INF);
        while (1) {
            ret.val = -INF, ret.pos = -1;
            query(0, n - 1, 0, i, 0);
            if (ret.val < 0) {
                break;
            }
            r[n - 1 - i]++;
            int j = ret.pos;
            incUpdate(0, 0, n - 1, 0, j, 1);
            setUpdate(0, 0, n - 1, j, -INF);
        }
        if (l[n - 1 - i] + r[n - 1 - i] - 1 >= n - k) {
            return true;
        }
    }
    int best = 0;
    for (int i = 0; i < n; i++) {
        if (a_l[i] >= 0) {
            best = max(best, l[i] + r[i] - 1);
        }
    }
    if (best >= n - k) {
        return true;
    }
    return false;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        int mx = -INF, mn = INF;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            mx = max(mx, a[i]);
            mn = min(mn, a[i]);
        }
        int l = mn, r = mx, ans = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            bool can = solve(n, k, mid);
            if (can) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        cout << ans << endl;
    }


    return 0;
}
