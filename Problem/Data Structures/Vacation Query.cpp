//https://atcoder.jp/contests/abc322/tasks/abc322_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const int INF = 1e6;

int lazy[4 * N];
int a[2][N];
long long pref[2][4 * N];
long long suf[2][4 * N];
long long sum[2][4 * N];
long long segtree[2][4 * N];

vector<int> nodes;
vector<long long> pref_nodes;
vector<long long> suf_nodes;
vector<long long> sum_nodes;
vector<long long> segtree_nodes;

void compose(int parent, int child) {
    lazy[child] += lazy[parent];
}

void apply(int node, int l, int r) {
    if (lazy[node] % 2 == 0) {
        return;
    }
    swap(segtree[0][node], segtree[1][node]);
    swap(sum[0][node], sum[1][node]);
    swap(pref[0][node], pref[1][node]);
    swap(suf[0][node], suf[1][node]);

    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    lazy[node] = 0;
}


void get_nodes(int l, int r, int lq, int rq, int node) {
    if (l > rq || r < lq) {
        return;
    }
    apply(node, l, r);
    if (lq <= l && rq >= r) {
        nodes.push_back(node);
        return;
    }

    int mid = (l + r) / 2;
    get_nodes(l, mid, lq, rq, 2 * node + 1);
    get_nodes(mid + 1, r, lq, rq, 2 * node + 2);
    return;
}

void incUpdate(int node, int l, int r, int lq, int rq) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        lazy[node]++;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    incUpdate(node * 2 + 1, l, mid, lq, rq);
    incUpdate(node * 2 + 2, mid + 1, r, lq, rq);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);

    for (int i = 0; i < 2; i++) {
        sum[i][node] = sum[i][2 * node + 1] + sum[i][2 * node + 2];
        pref[i][node] = max(pref[i][2 * node + 1], sum[i][2 * node + 1] + pref[i][2 * node + 2]);
        suf[i][node] = max(suf[i][2 * node + 2], sum[i][2 * node + 2] + suf[i][2 * node + 1]);

        segtree[i][node] = max({segtree[i][2 * node + 1], segtree[i][2 * node + 2], pref[i][node], suf[i][node], suf[i][2 * node + 1] + pref[i][2 * node + 2]});
    }
}

void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        for (int i = 0; i < 2; i++) {
            pref[i][node] = a[i][l];
            suf[i][node] = a[i][l];
            segtree[i][node] = a[i][l];
            sum[i][node] = a[i][l];
        }
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    for (int i = 0; i < 2; i++) {
        sum[i][node] = sum[i][2 * node + 1] + sum[i][2 * node + 2];
        pref[i][node] = max(pref[i][2 * node + 1], sum[i][2 * node + 1] + pref[i][2 * node + 2]);
        suf[i][node] = max(suf[i][2 * node + 2], sum[i][2 * node + 2] + suf[i][2 * node + 1]);

        segtree[i][node] = max({segtree[i][2 * node + 1], segtree[i][2 * node + 2], pref[i][node], suf[i][node], suf[i][2 * node + 1] + pref[i][2 * node + 2]});
    }
}

void build_ans(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        pref_nodes[node] = pref[0][nodes[l]];
        suf_nodes[node] = suf[0][nodes[l]];
        segtree_nodes[node] = segtree[0][nodes[l]];
        sum_nodes[node] = sum[0][nodes[l]];
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
    cin >> n >> q;
    string s;
    cin >> s;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            a[0][i] = 1;
            a[1][i] = -INF;
        } else {
            a[0][i] = -INF;
            a[1][i] = 1;
        }
     }
    build(0, n - 1, 0);
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            incUpdate(0, 0, n - 1, l, r);
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
            cout << max(0ll, segtree_nodes[0]) << endl;
            nodes.clear();
            pref_nodes.clear();
            suf_nodes.clear();
            sum_nodes.clear();
            segtree_nodes.clear();
        }
    }

    return 0;
}
