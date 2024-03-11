//https://dmoj.ca/problem/lkp18c2p5
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const long long M = 1e9 + 1;

long long a[N];
vector<long long> vals(2 * N, 0);
vector<long long> inds(2 * N, 0);

pair<long long, int> queries[N];
tree<pair<long long, int>, null_type, less<pair<long long, int>>, rb_tree_tag, tree_order_statistics_node_update> compress;
//map<pair<long long, int>, int> mp;

vector<long long> segsum(8 * N, 0);
vector<long long> seg(8 * N, 0);

struct chash {
    long long operator()(pair<long long, long long> x) const { return x.second * M + x.first; }
};
gp_hash_table<pair<long long, long long>, int, chash> mp;

long long query(int l, int r, int lq, int rq, int node, vector<long long> &segtree) {
    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    if (l > rq || r < lq || l > r) {
        return 0;
    }

    int mid = (l + r) / 2;
    return query(l, mid, lq, rq, 2 * node + 1, segtree) + query(mid + 1, r, lq, rq, 2 * node + 2, segtree);
}

void update(int l, int r, int ind, ll val, int node, vector<long long> &segtree) {
    if (l == r) {
        segtree[node] = val;
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, val, 2 * node + 1, segtree);
    } else {
        update(mid + 1, r, ind, val, 2 * node + 2, segtree);
    }
    segtree[node] = segtree[2 * node + 1] + segtree[2 * node + 2];
}


void build(int l, int r, int node, vector<long long> &v, vector<long long> &segtree) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = v[l];
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1, v, segtree);
    build(mid + 1, r, 2 * node + 2, v, segtree);
    segtree[node] = segtree[2 * node + 1] + segtree[2 * node + 2];
}

int bin(long long sum, int n, int m) {
    int l = 0, r = m - 1, ans = n;
    while (l <= r) {
        int mid = (l + r) / 2;
        long long cur = query(0, m - 1, mid, m - 1, 0, segsum);
        if (cur >= sum) {
            ans = min(ans, (int)query(0, m - 1, mid, m - 1, 0, seg));
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return ans;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
        compress.insert(make_pair(a[i], i));
    }
    for (int i = 0; i < q; i++) {
        cin >> queries[i].second >> queries[i].first;
        queries[i].second--;
        compress.insert(queries[i]);
    }
    int m = 0;
    for (auto it = compress.begin(); it != compress.end(); ++it) {
        mp[*it] = m++;
    }
    for (int i = 0; i < n; i++) {
        int ind = mp[make_pair(a[i], i)];
        vals[ind] = a[i];
        inds[ind] = 1;
    }
    build(0, m - 1, 0, vals, segsum);
    build(0, m - 1, 0, inds, seg);
    for (int i = 0; i < q; i++) {
        cout << bin(sum / 2ll + 1, n, m) << endl;
        int j = queries[i].second;
        long long val = queries[i].first;
        int ind_old = mp[make_pair(a[j], j)];
        update(0, m - 1, ind_old, 0, 0, seg);
        update(0, m - 1, ind_old, 0, 0, segsum);
        int ind_new = mp[make_pair(val, j)];
        update(0, m - 1, ind_new, 1, 0, seg);
        update(0, m - 1, ind_new, val, 0, segsum);
        sum += val - a[j];
        a[j] = val;
    }
    cout << bin(sum / 2ll + 1, n, m) << endl;
    return 0;
}
