//https://judge.yosupo.jp/problem/point_add_rectangle_sum
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

template<class T, int SZ> struct OffBIT2D {
    bool mode = 0;
    vector<pair<int, int>> todo;
    int cnt[SZ], st[SZ];
    vector<int> val; vector<T> bit;
    void init() {
        mode = 1;
        int lst[SZ];
        for (int i = 0; i < SZ; i++) {
            lst[i] = cnt[i] = 0;
        }
        sort(todo.begin(), todo.end(),
            [](const pair<int, int>& a, const pair<int, int>& b) {
                return a.second < b.second;
            });
        for (auto t : todo) {
            for (int x = t.first; x < SZ; x += x & -x) {
                if (lst[x] != t.second) {
                    lst[x] = t.second, cnt[x]++;
                }
            }
        }
        int sum = 0;
        for (int i = 0; i < SZ; i++) {
            lst[i] = 0, st[i] = (sum += cnt[i]);
        }
        val.resize(sum); bit.resize(sum); reverse(todo.begin(), todo.end());
        for (auto t : todo) {
            for (int x = t.first; x < SZ; x += x & -x) {
                if (lst[x] != t.second) {
                    lst[x] = t.second, val[--st[x]] = t.second;
                }
            }
        }
    }
    int rank(int y, int l, int r) {
        return upper_bound(val.begin() + l, val.begin() + r, y) - val.begin() - l;
    }
    void UPD(int x, int y, T t) {
        for (y = rank(y, st[x], st[x] + cnt[x]); y <= cnt[x]; y += y & -y) {
            bit[st[x] + y - 1] += t;
        }
    }
    void upd(int x, int y, T t) {
        if (!mode) {
            todo.push_back({x, y});
        } else {
            for (; x < SZ; x += x & -x) {
                UPD(x, y, t);
            }
        }
    }
    T QUERY(int x, int y) {
        T res = 0;
        for (y = rank(y, st[x], st[x] + cnt[x]); y; y -= y & -y) {
            res += bit[st[x] + y - 1];
        }
        return res;
    }
    T query(int x, int y) {
        T res = 0;
        for (; x; x -= x & -x) {
            res += QUERY(x, y);
        }
        return res;
    }
    T query(int xl, int yl, int xr, int yr) {
        return query(xr, yr) - query(xl - 1, yr) - query(xr ,yl - 1) + query(xl - 1, yl - 1);
    }
};

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    vector<tuple<int, int, int>> points;
    vector<tuple<int, int, int, int, int>> queries;
    vector<pair<int, int>> upd;
    set<int> st;
    for (int i = 0; i < n; i++) {
        int x, y, w;
        cin >> x >> y >> w;
        x++, y++;
        points.push_back(make_tuple(x, y, w));
        upd.push_back({x, y});
        st.insert(x);
    }
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 0) {
            int x, y, w;
            cin >> x >> y >> w;
            x++, y++;
            queries.push_back(make_tuple(0, x, y, w, -1));
            upd.push_back({x, y});
            st.insert(x);
        } else {
            int l, d, r, u;
            cin >> l >> d >> r >> u;
            l++, d++, r++, u++;
            queries.push_back(make_tuple(1, l, d, r, u));
        }
    }
    map<int, int> compr;
    int m = 0;
    for (int x : st) {
        compr[x] = m++;
    }
    OffBIT2D<long long, N> bit;
    for (int i = 0; i < upd.size(); i++) {
        upd[i].first = compr[upd[i].first] + 1;
        bit.upd(upd[i].first, upd[i].second, 0);
    }
    bit.init();
    for (int i = 0; i < n; i++) {
        auto [x, y, w] = points[i];
        bit.upd(compr[x] + 1, y, w);
    }
    for (int i = 0; i < q; i++) {
        auto [t, x, y, w, d] = queries[i];
        if (t == 0) {
            bit.upd(compr[x] + 1, y, w);
        } else {
            auto l = st.lower_bound(x), r = st.lower_bound(w);
            if (l == st.end() || r == st.begin()) {
                cout << 0 << endl;
                continue;
            }
            r--;
            x = compr[*l] + 1;
            w = compr[*r] + 1;
            cout << bit.query(x, y, w, d - 1) << endl;
        }
    }
    return 0;
}
