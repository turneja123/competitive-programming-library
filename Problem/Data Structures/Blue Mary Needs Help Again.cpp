//https://www.spoj.com/problems/CASHIER/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int segtree[4 * N];
int ans = -1;

pair<char, int> queries[N];
int compr[N];
map<int, int> pos;
int val[N];

void query(int l, int r, int k, int node) {
    if (l == r) {
        if (k > 0) {
            ans = max(ans, l);
        }
        return;
    }
    int mid = (l + r) / 2;
    if (k > segtree[2 * node + 1]) {
        query(mid + 1, r, k - segtree[2 * node + 1], 2 * node + 2);

    } else {
        query(l, mid, k, 2 * node + 1);
    }
}


void update(int l, int r, int ind, int val, int node) {
    if (l == r) {
        segtree[node] += val;
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
        segtree[node] = 0;
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = 0;
}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, mn, sum = 0, ct = 0, m = 0;
        cin >> n >> mn;
        int tmp = mn;
        for (int i = 0; i < n; i++) {
            char c; int k;
            cin >> c >> k;
            queries[i] = make_pair(c, k);
            if (c == 'A') {
                sum += k, mn -= k;
            } else if (c == 'S') {
                sum -= k, mn += k;
            } else if (c == 'I') {
                if (k - sum < mn) {
                    continue;
                }
                compr[m++] = k - sum;
            }
        }
        sort(compr, compr + m);
        int sz = 0;
        for (int i = 0; i < m; i++) {
            if (i > 0 && compr[i] > compr[i - 1]) {
                sz++;
            }
            pos[compr[i]] = sz;
            val[sz] = compr[i];
        }
        sz++;
        build(0, sz - 1, 0);
        sum = 0, mn = tmp;
        multiset<int> st;
        for (int i = 0; i < n; i++) {
            char c = queries[i].first; int k = queries[i].second;
            if (c == 'A') {
                sum += k, mn -= k;
            } else if (c == 'S') {
                sum -= k, mn += k;
                while (st.size() && val[*st.begin()] < mn) {
                    update(0, sz - 1, *st.begin(), -1, 0);
                    st.erase(st.begin());
                    ct++;
                }
            } else if (c == 'I') {
                if (k - sum < mn) {
                    continue;
                }
                int ind = pos[k - sum];
                st.insert(ind);
                update(0, sz - 1, ind, 1, 0);
            } else {
                if (segtree[0] < k) {
                    cout << -1 << endl;
                } else {
                    ans = -1;
                    query(0, sz - 1, segtree[0] - k + 1, 0);
                    assert(ans >= 0);
                    cout << val[ans] + sum << endl;
                }
            }
            assert(abs(sum) < 1e8);
        }
        pos.clear();
        cout << ct << endl;
    }
    return 0;
}
