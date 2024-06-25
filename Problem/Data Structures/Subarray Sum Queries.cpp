//https://www.spoj.com/problems/GSS3/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

long long a[N];
long long pref[4 * N];
long long suf[4 * N];
long long sum[4 * N];
long long segtree[4 * N];
vector<int> nodes;
vector<int> pref_nodes;
vector<int> suf_nodes;
vector<int> sum_nodes;
vector<int> segtree_nodes;

void get_nodes(int l, int r, int lq, int rq, int node) {
    if (lq <= l && rq >= r) {
        nodes.push_back(node);
        return;
    }

    if (l > rq || r < lq) {
        return;
    }

    int mid = (l + r) / 2;
    get_nodes(l, mid, lq, rq, 2 * node + 1);
    get_nodes(mid + 1, r, lq, rq, 2 * node + 2);
    return;
}

void update(int l, int r, int ind, int val, int node) {
    if (l == r) {
        pref[node] = val;
        suf[node] = val;
        segtree[node] = val;
        sum[node] = val;
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2);
    }
    sum[node] = sum[2 * node + 1] + sum[2 * node + 2];
    pref[node] = max(pref[2 * node + 1], sum[2 * node + 1] + pref[2 * node + 2]);
    suf[node] = max(suf[2 * node + 2], sum[2 * node + 2] + suf[2 * node + 1]);

    segtree[node] = max({segtree[2 * node + 1], segtree[2 * node + 2], pref[node], suf[node], suf[2 * node + 1] + pref[2 * node + 2]});
}


void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        pref[node] = a[l];
        suf[node] = a[l];
        segtree[node] = a[l];
        sum[node] = a[l];
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    sum[node] = sum[2 * node + 1] + sum[2 * node + 2];
    pref[node] = max(pref[2 * node + 1], sum[2 * node + 1] + pref[2 * node + 2]);
    suf[node] = max(suf[2 * node + 2], sum[2 * node + 2] + suf[2 * node + 1]);

    segtree[node] = max({segtree[2 * node + 1], segtree[2 * node + 2], pref[node], suf[node], suf[2 * node + 1] + pref[2 * node + 2]});
}

void build_ans(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        pref_nodes[node] = pref[nodes[l]];
        suf_nodes[node] = suf[nodes[l]];
        segtree_nodes[node] = segtree[nodes[l]];
        sum_nodes[node] = sum[nodes[l]];
        return;
    }

    int mid = (l + r) / 2;
    build_ans(l, mid, 2 * node + 1);
    build_ans(mid + 1, r, 2 * node + 2);
    sum_nodes[node] = sum_nodes[2 * node + 1] + sum_nodes[2 * node + 2];
    pref_nodes[node] = max(pref_nodes[2 * node + 1], sum_nodes[2 * node + 1] + pref_nodes[2 * node + 2]);
    suf_nodes[node] = max(suf_nodes[2 * node + 2], sum_nodes[2 * node + 2] + suf_nodes[2 * node + 1]);

    segtree_nodes[node] = max({segtree_nodes[2 * node + 1], segtree_nodes[2 * node + 2], pref_nodes[node], suf_nodes[node], suf_nodes[2 * node + 1] + pref_nodes[2 * node + 2]});

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
            int j, val;
            cin >> j >> val;
            j--;
            update(0, n - 1, j, val, 0);
        } else {
            int l, r;
            cin >> l >> r;
            l--, r--;
            get_nodes(0, n - 1, l, r, 0);
            int m = nodes.size();
            pref_nodes.resize(4 * m);
            suf_nodes.resize(4 * m);
            sum_nodes.resize(4 * m);
            segtree_nodes.resize(4 * m);
            build_ans(0, m - 1, 0);
            cout << segtree_nodes[0] << endl;
            nodes.clear();
            pref_nodes.clear();
            suf_nodes.clear();
            sum_nodes.clear();
            segtree_nodes.clear();
        }
    }

    return 0;
}
