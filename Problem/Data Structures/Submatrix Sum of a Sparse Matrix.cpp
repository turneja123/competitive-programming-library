//https://www.spoj.com/problems/BUZZ95/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

int id(int x, vector<int> &y) {
    return lower_bound(y.begin(), y.end(), x) - y.begin();
}

vector<pair<int, int>> add_point[N];
vector<tuple<int, int, int>> st_query[N], en_query[N];
ll ans[N];

struct BIT {
    int n;
    vector<long long> t;
    BIT(int _n) {
        n = _n;
        t.assign(n + 1, 0);
    }
    BIT(int _n, vector<int> &a) {
        n = _n;
        t.assign(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            t[i] += a[i - 1];
            int j = i + (i & -i);
            if (j <= n) {
                t[j] += t[i];
            }
        }
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
    long long query(int i) {
        long long ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans += t[i];
        }
        return ans;
    }
    long long query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

int main() {
    IOS;
    int n;
    cin >> n >> n >> n;
    vector<tuple<int, int, int>> points;
    vector<tuple<int, int, int, int>> queries;
    vector<int> sortedx, sortedy;
    for (int i = 0; i < n; i++) {
        int x, y, v;
        cin >> x >> y >> v;
        points.push_back(make_tuple(x, y, v));
        sortedx.push_back(x);
        sortedy.push_back(y);
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int x0, y0, x1, y1;
        cin >> x0 >> y0 >> x1 >> y1;
        queries.push_back({x0, y0, x1, y1});
        sortedx.push_back(x0);
        sortedy.push_back(y0);
        sortedx.push_back(x1);
        sortedy.push_back(y1);
    }
    sort(sortedx.begin(), sortedx.end());
    sortedx.erase(unique(sortedx.begin(), sortedx.end()), sortedx.end());
    sort(sortedy.begin(), sortedy.end());
    sortedy.erase(unique(sortedy.begin(), sortedy.end()), sortedy.end());
    for (int i = 0; i < n; i++) {
        auto [x, y, v] = points[i];
        x = id(x, sortedx);
        y = id(y, sortedy);
        add_point[x].push_back({y, v});
    }
    for (int i = 0; i < q; i++) {
        auto [x0, y0, x1, y1] = queries[i];
        x0 = id(x0, sortedx);
        y0 = id(y0, sortedy);
        x1 = id(x1, sortedx);
        y1 = id(y1, sortedy);
        st_query[x0].push_back(make_tuple(y0, y1, i));
        en_query[x1].push_back(make_tuple(y0, y1, i));
    }
    BIT bit(N);
    for (int i = 0; i < N; i++) {
        for (auto [y0, y1, j] : st_query[i]) {
            ans[j] -= bit.query(y0 + 1, y1 + 1);
        }
        for (auto [y, v] : add_point[i]) {
            bit.upd(y + 1, v);
        }
        for (auto [y0, y1, j] : en_query[i]) {
            ans[j] += bit.query(y0 + 1, y1 + 1);
        }
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }

    return 0;
}
