//https://ocpc2026w.eolymp.space/en/compete/g6s5o5k4n93719vrc5sak0hi3k/problem/7
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const ll M = 998244353;

ll modPow(ll a, ll y) {
    ll res = 1;
    while (y > 0) {
        if (y % 2 != 0) {
            res = res * a % M;
        }
        y /= 2;
        a = a * a % M;
    }
    return res;
}

struct Node {
    ll sum;
    ll mul;
    ll ct;
    int ct_uniq;
    ll lazy;

    Node() {
        sum = 0; ct = 0; ct_uniq = 0; lazy = 1, mul = 1;
    }
};

int a[N];
Node segtree[4 * N];

Node combine(Node left, Node right) {
    Node node = Node();
    node.sum = (left.sum + right.sum) % M;
    node.ct = left.ct + right.ct;
    node.ct_uniq = left.ct_uniq + right.ct_uniq;
    return node;
}

void compose(int parent, int child) {
    segtree[child].lazy = segtree[child].lazy * segtree[parent].lazy % M;
}

void apply(int node, int l, int r) {
    segtree[node].sum = segtree[node].sum * segtree[node].lazy % M;
    segtree[node].mul = segtree[node].mul * segtree[node].lazy % M;
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    segtree[node].lazy = 1;
}

void incUpdate(int node, int l, int r, int lq, int rq, ll add) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[node].lazy = segtree[node].lazy * add % M;
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

void setUpdate(int node, int l, int r, int ind, ll val) {
    apply(node, l, r);
    if (l == r) {
        segtree[node].ct += val;
        if (segtree[node].ct_uniq == 0) {
            segtree[node].ct_uniq = 1;
            segtree[node].sum = (segtree[node].sum + segtree[node].mul) % M;
        }
        return;
    }

    int mid = (l + r) / 2;
    if (ind <= mid) {
        setUpdate(2 * node + 1, l, mid, ind, val);
    } else {
        setUpdate(2 * node + 2, mid + 1, r, ind, val);
    }
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
    segtree[node] = combine(segtree[2 * node + 1], segtree[2 * node + 2]);
}

ll getSum(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r) {
        return 0;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree[node].sum;
    }
    int mid = (l + r) / 2;
    return (getSum(l, mid, lq, rq, 2 * node + 1) + getSum(mid + 1, r, lq, rq, 2 * node + 2)) % M;
}

ll getCt(int l, int r, int lq, int rq, int node) {
    if (l > rq || lq > r || lq > rq) {
        return 0;
    }
    apply(node, l, r);
    if (l >= lq && r <= rq) {
        return segtree[node].ct;
    }
    int mid = (l + r) / 2;
    return getCt(l, mid, lq, rq, 2 * node + 1) + getCt(mid + 1, r, lq, rq, 2 * node + 2);
}

int main() {
    IOS;
    int q;
    cin >> q;
    vector<int> compr;
    vector<tuple<int, int, int>> queries;
    for (int i = 0; i < q; i++) {
        int t, x, y;
        cin >> t >> x >> y;
        if (t == 1) {
            compr.push_back(x);
        }
        queries.push_back({t, x, y});
    }
    sort(compr.begin(), compr.end());
    compr.erase(unique(compr.begin(), compr.end()), compr.end());
    int m = compr.size();
    for (auto [t, x, y] : queries) {
        if (t == 1) {
            x = lower_bound(compr.begin(), compr.end(), x) - compr.begin();
            setUpdate(0, 0, m - 1, x, y);
            if (x >= 0) {
                incUpdate(0, 0, m - 1, 0, x - 1, modPow((M + 1) / 2, y));
            }
        } else {
            x = lower_bound(compr.begin(), compr.end(), x) - compr.begin();
            y = upper_bound(compr.begin(), compr.end(), y) - compr.begin() - 1;
            if (x > y) {
                cout << 0 << endl;
                continue;
            }
            ll ans = (M + 1) / 2 * getSum(0, m - 1, x, y, 0) % M * modPow(2, getCt(0, m - 1, y + 1, m - 1, 0)) % M;
            cout << ans << endl;
        }
    }



    return 0;
}
