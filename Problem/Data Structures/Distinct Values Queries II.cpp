//https://cses.fi/problemset/task/3356
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;

int a[N];
int last[N];

set<int> pos[N];
int segtree[4 * N];

int rmq(int l, int r, int lq, int rq, int node) {
    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    if (l > rq || r < lq) {
        return -1;
    }

    int mid = (l + r) / 2;
    return max(rmq(l, mid, lq, rq, 2 * node + 1), rmq(mid + 1, r, lq, rq, 2 * node + 2));
}

void update(int l, int r, int ind, int val, int node) {
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
    segtree[node] = max(segtree[2 * node + 1], segtree[2 * node + 2]);
}


void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = last[l];
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = max(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    map<int, int> mp;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (mp.find(a[i]) == mp.end()) {
            mp[a[i]] = mp.size();
        }
        a[i] = mp[a[i]];
        auto it = pos[a[i]].insert(i).first;
        if (it != pos[a[i]].begin()) {
            it--;
            last[i] = *it;
        } else {
            last[i] = -1;
        }
    }
    build(0, n - 1, 0);
    for (int i = 0; i < q; i++) {
        int t, l, r;
        cin >> t >> l >> r;
        if (t == 1) {
            l--;
            auto it = pos[a[l]].find(l);
            int lf = -1;
            if (it != pos[a[l]].begin()) {
                it--;
                lf = *it;
                it++;
            }
            it++;
            if (it != pos[a[l]].end()) {
                last[*it] = lf;
                update(0, n - 1, *it, lf, 0);
            }
            pos[a[l]].erase(l);

            if (mp.find(r) == mp.end()) {
                mp[r] = mp.size();
            }
            r = mp[r];
            a[l] = r;
            auto it2 = pos[a[l]].insert(l).first;
            if (it2 != pos[a[l]].begin()) {
                it2--;
                last[l] = *it2;
                update(0, n - 1, l, *it2, 0);
                it2++;
            } else {
                update(0, n - 1, l, -1, 0);
            }
            it2++;
            if (it2 != pos[a[l]].end()) {
                last[*it2] = l;
                update(0, n - 1, *it2, l, 0);
            }
        } else {
            l--, r--;
            int mx = rmq(0, n - 1, l, r, 0);
            if (mx < l) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
    }

    return 0;
}
