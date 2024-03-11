#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);
#define tr tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag, tree_order_statistics_node_update>

const int N = 2e5 + 5;
const int INF = 1e9;

int a[N];
tr segtree[4 * N];

tr treeMerge(tr& t1, tr& t2) {
    tr t;
    for (auto it = t1.begin(); it != t1.end(); ++it) {
        t.insert({it->first, it->second});
    }
    for (auto it = t2.begin(); it != t2.end(); ++it) {
        t.insert({it->first, it->second});
    }
    return t;
}

int query(int l, int r, int lq, int rq, int node, int k) {
    if (l > rq || r < lq) {
        return 0;
    }

    if (lq <= l && rq >= r) {
        return segtree[node].size() -
               segtree[node].order_of_key({k, INF});
    }

    int mid = (l + r) / 2;
    return query(l, mid, lq, rq, 2 * node + 1, k) +
           query(mid + 1, r, lq, rq, 2 * node + 2, k);
}

void update(int l, int r, int ind, int val, int node) {

    segtree[node].erase(segtree[node].find({a[ind], ind}));
    segtree[node].insert({val, ind});
    if (l == r) {
        a[ind] = val;
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2);
    }

}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node].insert({a[l], l});
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = treeMerge(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int main() {
    IOS;
    int n, q;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(0, n - 1, 0);
    cin >> q;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            int ind, val;
            cin >> ind >> val;
            ind--;
            update(0, n - 1, ind, val, 0);

        } else {
            int l, r, k;
            cin >> l >> r >> k;
            l--, r--;
            cout << query(0, n - 1, l, r, 0, k) << endl;
        }

    }

    return 0;
}
