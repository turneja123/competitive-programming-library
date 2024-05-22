//https://judge.yosupo.jp/problem/static_range_count_distinct
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

int a[N];
pair<pair<int, int>, int> queries[N];

vector<int> pos[N];
gp_hash_table<int, int> mp;

int first[N];
int ind[N];
int ans[N];
int segtree[4 * N];

int query(int l, int r, int lq, int rq, int node) {
    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    if (l > rq || r < lq) {
        return 0;
    }

    int mid = (l + r) / 2;
    return query(l, mid, lq, rq, 2 * node + 1) + query(mid + 1, r, lq, rq, 2 * node + 2);
}

void update(int l, int r, int ind, ll val, int node) {
    if (l == r) {
        segtree[node] = val;
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2);
    }
    segtree[node] = segtree[2 * node + 1] + segtree[2 * node + 2];
}


void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = first[l];
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = segtree[2 * node + 1] + segtree[2 * node + 2];
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    set<int> st;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        st.insert(a[i]);
    }
    int m = st.size(); int j = 0;
    for (auto it = st.begin(); it != st.end(); ++it) {
        mp[*it] = j++;
    }
    for (int i = 0; i < n; i++) {
        int k = mp[a[i]];
        pos[k].push_back(i);
        if (pos[k].size() == 1) {
            first[i] = 1;
        }
    }
    build(0, n - 1, 0);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        r--;
        queries[i] = make_pair(make_pair(l, r), i);
    }
    sort(queries, queries + q);
    j = 0;
    for (int i = 0; i < q; i++) {
        int l = queries[i].first.first, r = queries[i].first.second;
        while (j < l) {
            int k = mp[a[j]];
            first[j] = 0;
            ind[k]++;
            if (ind[k] < pos[k].size()) {
                first[pos[k][ind[k]]] = 1;
                update(0, n - 1, pos[k][ind[k]], 1, 0);
            }
            j++;
        }
        ans[queries[i].second] = query(0, n - 1, l, r, 0);
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }

    return 0;
}
