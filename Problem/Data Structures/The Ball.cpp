//https://www.spoj.com/problems/BALL/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

struct Node {
    int val;
    int setVal;
    Node() {
        val = -1;
        setVal = -1;
    }
};

int l[N];
int r[N];
int dp[N];
Node segtree[4 * N];

void compose(int parent, int child) {
    if (segtree[parent].setVal != -1) {
        segtree[child].setVal = segtree[parent].setVal;
    }
}

void apply(int node, int l, int r) {
    if (segtree[node].setVal != -1) {
        segtree[node].val = segtree[node].setVal;
    }
    if (l != r) {
        compose(node, 2 * node + 1);
        compose(node, 2 * node + 2);
    }
    segtree[node].setVal = -1;
}

void setUpdate(int node, int l, int r, int lq, int rq, int val) {
    if (l > rq || lq > r) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[node].setVal = val;
        return;
    }
    apply(node, l, r);
    int mid = (l + r) / 2;
    setUpdate(node * 2 + 1, l, mid, lq, rq, val);
    setUpdate(node * 2 + 2, mid + 1, r, lq, rq, val);
    apply(2 * node + 1, l, mid);
    apply(2 * node + 2, mid + 1, r);
}

int getVal(int l, int r, int ind, int node) {
    apply(node, l, r);
    if (l == r) {
        return segtree[node].val;
    }
    int mid = (l + r) / 2;
    if (ind <= mid) {
        return getVal(l, mid, ind, 2 * node + 1);
    } else {
        return getVal(mid + 1, r, ind, 2 * node + 2);
    }
}

int main() {
    IOS;
    set<int> st;
    int n;
    cin >> n;
    vector<tuple<int, int, int>> a;
    for (int i = 0; i < n; i++) {
        int x1, x2, y;
        cin >> x1 >> x2 >> y;
        a.push_back({y, x1, x2});
        st.insert(x1);
        st.insert(x1 - 1);
        st.insert(x2);
        st.insert(x2 + 1);
    }
    int q;
    cin >> q;
    vector<int> queries;
    for (int i = 0; i < q; i++) {
        int x;
        cin >> x;
        queries.push_back(x);
        st.insert(x);
    }
    map<int, int> mp;
    for (auto x : st) {
        mp[x] = mp.size();
    }
    int m = mp.size();
    sort(a.begin(), a.end());
    int j = 0;
    for (auto [_, l, r] : a) {
        l = mp[l];
        r = mp[r];
        dp[j] = 1;
        int lc = getVal(0, m - 1, l - 1, 0);
        if (lc != -1) {
            dp[j] = max(dp[j], dp[lc] + 1);
        }
        int rc = getVal(0, m - 1, r + 1, 0);
        if (rc != -1) {
            dp[j] = max(dp[j], dp[rc] + 1);
        }
        setUpdate(0, 0, m - 1, l, r, j);
        j++;
    }
    for (int x : queries) {
        x = mp[x];
        int g = getVal(0, m - 1, x, 0);
        if (g == -1) {
            cout << 0 << endl;
        } else {
            cout << dp[g] << endl;
        }
    }
    return 0;
}
