//https://atcoder.jp/contests/abc379/tasks/abc379_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);
#define tr tree<int, null_type, greater<int>, rb_tree_tag, tree_order_statistics_node_update>

const int N = 2e5 + 5;
const int K = 20;

int a[N];
tr segtree[4 * N];

vector<int> nodes;

int table[K][N];

void build_sparse(int n) {
    for (int i = 1; i <= n; i++) {
        table[0][i] = a[i - 1];
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            table[k][i] = max(table[k - 1][i], table[k - 1][i + (1 << (k - 1))]);
        }
    }
    return;
}

int query(int l, int r) {
    int k = 31 - __builtin_clz(r - l + 1);
    return max(table[k][l], table[k][r - (1 << k) + 1]);
}

tr treeMerge(tr& t1, tr& t2) {
    tr t;
    for (auto it = t1.begin(); it != t1.end(); ++it) {
        t.insert(*it);
    }
    for (auto it = t2.rbegin(); it != t2.rend(); ++it) {
        if (*it > *t.begin()) {
            t.insert(*it);
        }
    }
    return t;
}

void getNodes(int l, int r, int lq, int rq, int node) {
    if (l > rq || r < lq) {
        return;
    }

    if (lq <= l && rq >= r) {
        nodes.push_back(node);
        return;
    }

    int mid = (l + r) / 2;
    getNodes(l, mid, lq, rq, 2 * node + 1);
    getNodes(mid + 1, r, lq, rq, 2 * node + 2);
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node].insert(a[l]);
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
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    build(0, n - 1, 0);
    build_sparse(n);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        if (r == n - 1) {
            cout << 0 << endl;
            continue;
        }
        int mx = query(l + 2, r + 1);
        getNodes(0, n - 1, r + 1, n - 1, 0);
        int ans = 0;
        for (int j = 0; j < nodes.size(); j++) {
            ans += segtree[nodes[j]].order_of_key(mx);
            mx = max(mx, *segtree[nodes[j]].begin());
        }
        cout << ans << endl;
        nodes.clear();
    }

    return 0;
}
