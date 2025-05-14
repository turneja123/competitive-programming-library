//https://cses.fi/problemset/task/3307/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e6 + 10;

struct BIT {
    int n;
    vector<int> t;
    BIT(int _n) {
        n = _n;
        t.assign(n + 1, 0);
    }
    void upd(int i, int val) {
        if (i <= 0) {
            return;
        }
        for (; i <= n; i += (i & -i)) {
            t[i] += val;
        }
    }
    int query(int i) {
        int ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans += t[i];
        }
        return ans;
    }
    int query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        x++, y++;
        a[i] = make_pair(x - y, x + y);
    }
    sort(a.begin(), a.end());
    vector<tuple<int, int, int, int, int, int>> queries(m);
    vector<int> inds;
    vector<int> ans(m, N - 1);

    for (int i = 0; i < m; i++) {
        int x, y, k;
        cin >> x >> y; k = 1;
        x++, y++;
        queries[i] = make_tuple(x - y, x + y, 0, N - 1, i, k);
        inds.push_back(i);
    }

    while (true) {
        if (inds.empty()) {
            break;
        }
        vector<int> ct(m, 0);
        vector<tuple<int, int, int, int>> events;
        for (int j : inds) {
            auto [x, y, l, r, i, k] = queries[j];
            int mid = (l + r) / 2;
            events.push_back(make_tuple(x - mid - 1, max(1, y - mid), min(N - 1, y + mid), ~i));
            events.push_back(make_tuple(x + mid, max(1, y - mid), min(N - 1, y + mid), i));
        }
        sort(events.begin(), events.end());
        int ptr = 0;
        BIT bit(N);
        for (auto [x, yl, yr, i] : events) {
            while (ptr < n && a[ptr].first <= x) {
                bit.upd(a[ptr].second, 1);
                ptr++;
            }
            if (i < 0) {
                i = ~i;
                ct[i] -= bit.query(yl, yr);
            } else {
                ct[i] += bit.query(yl, yr);
            }
        }

        vector<int> nx;
        for (int j : inds) {
            auto [x, y, l, r, i, k] = queries[j];
            int mid = (l + r) / 2;
            if (ct[i] >= k) {
                ans[i] = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
            queries[j] = make_tuple(x, y, l, r, i, k);
            if (l <= r) {
                nx.push_back(i);
            }
        }
        inds = nx;
    }
    for (int i = 0; i < m; i++) {
        cout << ans[i] << " ";
    }
    return 0;
}
