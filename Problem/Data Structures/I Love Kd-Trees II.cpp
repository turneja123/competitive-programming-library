//https://www.spoj.com/problems/ILKQUERY2/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

int a[N];
int f[N];
vector<int> pos[N];
vector<int> seg[N];
gp_hash_table<int, int> mp;

int query(int l, int r, int lq, int rq, int node, vector<int> &segtree) {
    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    if (l > rq || r < lq) {
        return 0;
    }

    int mid = (l + r) / 2;
    return query(l, mid, lq, rq, 2 * node + 1, segtree)
               + query(mid + 1, r, lq, rq, 2 * node + 2, segtree);
}

void update(int l, int r, int ind, int val, int node, vector<int> &segtree) {
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

void build(int l, int r, int node, vector<int> &segtree) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = 1;
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1, segtree);
    build(mid + 1, r, 2 * node + 2, segtree);
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
        f[i] = 1;
    }
    int j = 0, m = st.size();
    for (auto it = st.begin(); it != st.end(); ++it) {
        mp[*it] = j++;
    }
    for (int i = 0; i < n; i++) {
        pos[mp[a[i]]].push_back(i);
    }
    for (int i = 0; i < m; i++) {
        int sz = pos[i].size();
        seg[i].resize(4 * sz);
        build(0, sz - 1, 0, seg[i]);
    }
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            int l, r, k, ans;
            cin >> l >> r >> k;
            auto it = mp.find(k);
            if (it == mp.end()) {
                cout << 0 << endl;
                continue;
            }
            k = it->second; int m = pos[k].size();
            int lq = lower_bound(pos[k].begin(), pos[k].end(), l) - pos[k].begin();
            int rq = upper_bound(pos[k].begin(), pos[k].end(), r) - pos[k].begin();
            rq--;
            if (lq == m || lq > rq) {
                ans = 0;
            } else {
                ans = query(0, m - 1, lq, rq, 0, seg[k]);
            }
            cout << ans << endl;
        } else {
            int j;
            cin >> j;
            f[j] ^= 1;
            int k = mp[a[j]], m = pos[k].size();
            int lq = lower_bound(pos[k].begin(), pos[k].end(), j) - pos[k].begin();
            update(0, m - 1, lq, f[j], 0, seg[k]);
        }
    }

    return 0;
}
