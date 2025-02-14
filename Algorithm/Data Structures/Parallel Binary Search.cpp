//https://www.spoj.com/problems/METEORS/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

struct BIT {
    int n;
    vector<unsigned long long> t;
    BIT(int _n) {
        n = _n;
        t.assign(n + 1, 0);
    }
    void upd(int i, long long val) {
        if (i <= 0) {
            return;
        }
        for (; i <= n; i += (i & -i)) {
            t[i] += val;
        }
    }
    void upd(int l, int r, long long val) {
        upd(l, val);
        upd(r + 1, -val);
    }
    unsigned long long query(int i) {
        long long ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans += t[i];
        }
        return ans;
    }
};

vector<int> pos[N];
vector<tuple<int, int, int>> events;
long long need[N];
int ans[N];

void calc(int l, int r, int n, vector<int> a, BIT &bit) {
    if (a.empty()) {
        return;
    }
    int mid = (l + r) / 2;
    for (int i = l; i <= mid; i++) {
        auto [lq, rq, wt] = events[i];
        if (lq <= rq) {
            bit.upd(lq + 1, rq + 1, wt);
        } else {
            bit.upd(lq + 1, n, wt);
            bit.upd(1, rq + 1, wt);
        }
    }
    vector<int> lf, rt;
    for (int i = 0; i < a.size(); i++) {
        unsigned long long cur = 0;
        for (int j : pos[a[i]]) {
            cur += bit.query(j + 1);
        }
        if (cur >= need[a[i]]) {
            ans[a[i]] = mid;
            lf.push_back(a[i]);
        } else {
            need[a[i]] -= cur;
            rt.push_back(a[i]);
        }
    }
    for (int i = l; i <= mid; i++) {
        auto [lq, rq, wt] = events[i];
        if (lq <= rq) {
            bit.upd(lq + 1, rq + 1, -wt);
        } else {
            bit.upd(lq + 1, n, -wt);
            bit.upd(1, rq + 1, -wt);
        }
    }
    if (l <= mid - 1) {
        calc(l, mid - 1, n, lf, bit);
    }
    if (mid + 1 <= r) {
        calc(mid + 1, r, n, rt, bit);
    }
    return;
}

int main() {
    IOS;
    int n, m, q;
    cin >> m >> n;
    BIT bit(n);
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        a--;
        pos[a].push_back(i);
    }
    vector<int> a;
    for (int i = 0; i < m; i++) {
        ans[i] = -1;
        a.push_back(i);
        cin >> need[i];
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r, w;
        cin >> l >> r >> w;
        l--, r--;
        events.push_back(make_tuple(l, r, w));
    }
    calc(0, q - 1, n, a, bit);
    for (int i = 0; i < m; i++) {
        if (ans[i] == -1) {
            cout << "NIE" << endl;
        } else {
            cout << ans[i] + 1 << endl;
        }
    }
    return 0;
}
