//https://cses.fi/problemset/task/1748/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long M = 1e9 + 7;

long long a[N];
long long segtree[4 * N];

gp_hash_table<int, int> mp;

long long query(int l, int r, int lq, int rq, int node) {
    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    if (l > rq || r < lq) {
        return 0;
    }

    int mid = (l + r) / 2;
    return (query(l, mid, lq, rq, 2 * node + 1) + query(mid + 1, r, lq, rq, 2 * node + 2)) % M;
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
    segtree[node] = (segtree[2 * node + 1] + segtree[2 * node + 2]) % M;
}

int main() {
    IOS;
    int n;
    cin >> n;
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
        int pos = mp[a[i]];
        long long ct = (query(0, m - 1, 0, pos, 0) + 1) % M;
        update(0, m - 1, pos, ct, 0);
    }
    long long ans = query(0, m - 1, 0, m - 1, 0);
    cout << ans;

    return 0;
}
