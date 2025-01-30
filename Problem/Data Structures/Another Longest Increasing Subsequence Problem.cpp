//https://www.spoj.com/problems/LIS2/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

struct Data {
    int x, y, i;
    Data() {};
    Data(int x, int y, int i) : x(x), y(y), i(i) {};
};

vector<Data> a;
vector<Data> seg[4 * N];

int segtree[2 * N];
int ans[N];

void update(int pos, int val, int n, int j) {
    pos += n;
    if (j == 0) {
        segtree[pos] = val;
    } else {
        segtree[pos] = max(segtree[pos], val);
    }
    while (pos > 1) {
        pos /= 2;
        segtree[pos] = max(segtree[2 * pos], segtree[2 * pos + 1]);
    }
}

int rmq(int l, int r, int n) {
    l += n;
    r += n;
    int mx = 0;
    while (l < r) {
        if (r % 2 == 1) {
            mx = max(mx, segtree[--r]);
        }
        if (l % 2 == 1) {
            mx = max(mx, segtree[l++]);
        }
        l /= 2;
        r /= 2;
    }
    return mx;
}

void pre(int l, int r, int node) {
    if (l == r) {
        seg[node] = {a[l]};
        return;
    }
    int mid = (l + r) / 2;
    pre(l, mid, 2 * node + 1);
    pre(mid + 1, r, 2 * node + 2);
    int i = 0, j = 0;
    while (i < seg[2 * node + 1].size() && j < seg[2 * node + 2].size()) {
        if (seg[2 * node + 1][i].x < seg[2 * node + 2][j].x) {
            seg[node].push_back(seg[2 * node + 1][i++]);
        } else {
            seg[node].push_back(seg[2 * node + 2][j++]);
        }
    }
    while (i < seg[2 * node + 1].size()) {
        seg[node].push_back(seg[2 * node + 1][i++]);
    }
    while (j < seg[2 * node + 2].size()) {
        seg[node].push_back(seg[2 * node + 2][j++]);
    }
    return;
}

void calc(int l, int r, int node, int m) {
    if (l == r) {
        return;
    }
    int mid = (l + r) / 2;
    calc(l, mid, 2 * node + 1, m);
    int i = 0, j = 0;
    vector<int> upd;
    while (i < seg[2 * node + 1].size() && j < seg[2 * node + 2].size()) {
        if (seg[2 * node + 1][i].x < seg[2 * node + 2][j].x) {
            update(seg[2 * node + 1][i].y, ans[seg[2 * node + 1][i].i], m, 1);
            upd.push_back(seg[2 * node + 1][i].y);
            i++;
        } else {
            ans[seg[2 * node + 2][j].i] = max(ans[seg[2 * node + 2][j].i], rmq(0, seg[2 * node + 2][j].y, m) + 1);
            j++;
        }
    }
    while (j < seg[2 * node + 2].size()) {
        ans[seg[2 * node + 2][j].i] = max(ans[seg[2 * node + 2][j].i], rmq(0, seg[2 * node + 2][j].y, m) + 1);
        j++;
    }
    for (int x : upd) {
        update(x, 0, m, 0);
    }
    calc(mid + 1, r, 2 * node + 2, m);
    return;
}

int main() {
    IOS;
    int n;
    cin >> n;
    a.resize(n);
    set<int> st;
    map<int, int> compr;
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        a[i] = Data(x, y, i);
        st.insert(y);
    }
    int m = 0;
    for (int x : st) {
        compr[x] = m++;
    }
    for (int i = 0; i < n; i++) {
        a[i].y = compr[a[i].y];
        ans[i] = 1;
    }
    pre(0, n - 1, 0);
    calc(0, n - 1, 0, m);
    int best = 1;
    for (int i = 0; i < n; i++) {
        best = max(best, ans[i]);
    }
    cout << best;
    return 0;
}
