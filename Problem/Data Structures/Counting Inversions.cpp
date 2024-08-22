//https://www.spoj.com/problems/SWAPS/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const int MAX = 50001;
const int SQ = 500;

int a[N];
int segtree[4 * MAX];
vector<int> v[SQ + 5];

int query(int l, int r, int lq, int rq, int node) {
    if (lq <= l && rq >= r) {
        return segtree[node];
    }

    if (l > rq || r < lq) {
        return 0;
    }

    int mid = (l + r) / 2;
    return query(l, mid, lq, rq, 2 * node + 1) +
               query(mid + 1, r, lq, rq, 2 * node + 2);
}

void update(int l, int r, int ind, int node) {
    if (l == r) {
        segtree[node]++;
        return;
    }

    int mid = (l + r) / 2;
    if (ind >= l && ind <= mid) {
        update(l, mid, ind, 2 * node + 1);
    } else {
        update(mid + 1, r, ind, 2 * node + 2);
    }
    segtree[node] = segtree[2 * node + 1] + segtree[2 * node + 2];
}

int leftinv(int i, int x, int n) {
    int j = 0, ans = 0;
    while ((j + 1) * SQ - 1 < i) {
        int ct = upper_bound(v[j].begin(), v[j].end(), x) - v[j].begin();
        ans += SQ - ct;
        j++;
    }
    for (int k = j * SQ; k < i; k++) {
        if (a[k] > x) {
            ans++;
        }
    }
    return ans;
}

int rightinv(int i, int x, int n) {
    int j = n / SQ, ans = 0;
    while (j * SQ > i) {
        int ct = lower_bound(v[j].begin(), v[j].end(), x) - v[j].begin();
        ans += ct;
        j--;
    }
    for (int k = min((j + 1) * SQ - 1, n - 1); k > i; k--) {
        if (a[k] < x) {
            ans++;
        }
    }
    return ans;
}

int main() {
    IOS;
    int n, q;
    cin >> n;
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        ans += query(0, MAX - 1, a[i] + 1, MAX - 1, 0);
        update(0, MAX - 1, a[i], 0);
        v[i / SQ].push_back(a[i]);
    }
    for (int i = 0; i <= n / SQ; i++) {
        sort(v[i].begin(), v[i].end());
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        int j, x;
        cin >> j >> x;
        j--;
        ans -= leftinv(j, a[j], n);
        ans -= rightinv(j, a[j], n);
        int b = j / SQ;
        int pos = lower_bound(v[b].begin(), v[b].end(), a[j]) - v[b].begin();
        v[b][pos] = x;
        a[j] = x;
        sort(v[b].begin(), v[b].end());
        ans += leftinv(j, a[j], n);
        ans += rightinv(j, a[j], n);
        cout << ans << endl;

    }

    return 0;
}
