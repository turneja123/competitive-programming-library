//https://codeforces.com/contest/2138/problem/B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const int INF = 1e9;

vector<int> upd[N];
vector<pair<int, int>> queries[N];

int lf[N], rt[N];
int segtree[4 * N];
int a[N];
int ans[N];

int rmq(int l, int r, int lq, int rq, int node) {
    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    if (l > rq || r < lq) {
        return INF;
    }

    int mid = (l + r) / 2;
    return min(rmq(l, mid, lq, rq, 2 * node + 1),
               rmq(mid + 1, r, lq, rq, 2 * node + 2));
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
    segtree[node] = min(segtree[2 * node + 1], segtree[2 * node + 2]);
}


void build(int l, int r, int node) {
    if (l > r) {
        return;
    }
    if (l == r) {
        segtree[node] = rt[l];
        return;
    }

    int mid = (l + r) / 2;
    build(l, mid, 2 * node + 1);
    build(mid + 1, r, 2 * node + 2);
    segtree[node] = min(segtree[2 * node + 1], segtree[2 * node + 2]);
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        stack<int> st;
        for (int i = 0; i < n; i++) {
            while (st.size() && a[st.top()] < a[i]) {
                st.pop();
            }
            if (st.size()) {
                lf[i] = st.top();
            } else {
                lf[i] = -1;
            }
            st.push(i);
        }
        while (st.size()) {
            st.pop();
        }
        for (int i = n - 1; i >= 0; i--) {
            while (st.size() && a[st.top()] > a[i]) {
                st.pop();
            }
            if (st.size()) {
                rt[i] = st.top();
            } else {
                rt[i] = n;
            }
            st.push(i);
        }
        for (int i = 0; i < n; i++) {
            upd[lf[i] + 1].push_back(i);
        }
        for (int i = 0; i < q; i++) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            queries[l].push_back({r, i});
        }
        build(0, n - 1, 0);
        for (int i = 0; i < n; i++) {
            for (int j : upd[i]) {
                update(0, n - 1, j, INF, 0);
            }
            for (auto [r, j] : queries[i]) {
                int m = rmq(0, n - 1, i, r, 0);
                if (m <= r) {
                    ans[j] = 0;
                } else {
                    ans[j] = 1;
                }
            }
        }
        for (int i = 0; i < q; i++) {
            if (ans[i]) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
        for (int i = 0; i <= n; i++) {
            upd[i].clear();
            queries[i].clear();
        }
    }

    return 0;
}
