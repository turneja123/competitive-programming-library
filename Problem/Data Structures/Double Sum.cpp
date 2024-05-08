//https://atcoder.jp/contests/abc351/tasks/abc351_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;

int a[N];

set<int> st;
map<int, int> pos;

vector<long long> vals(N, 0);
vector<long long> inds(N, 0);

vector<long long> segsum(4 * N, 0);
vector<long long> seg(4 * N, 0);

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

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        st.insert(a[i]);
    }
    int m = st.size(), j = 0;
    for (auto it = st.begin(); it != st.end(); ++it) {
        pos[*it] = j++;
    }
    for (int i = 0; i < n; i++) {
        int ind = pos[a[i]];
        vals[ind] += a[i];
        inds[ind]++;
    }
    build(0, m - 1, 0, vals, segsum);
    build(0, m - 1, 0, inds, seg);
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        int ind = pos[a[i]];
        vals[ind] -= a[i];
        inds[ind]--;
        update(0, m - 1, ind, vals[ind], 0, segsum);
        update(0, m - 1, ind, inds[ind], 0, seg);
        ans -= (long long)a[i] * query(0, m - 1, ind + 1, m - 1, 0, seg);
        ans += query(0, m - 1, ind + 1, m - 1, 0, segsum);
    }
    cout << ans;

    return 0;
}
