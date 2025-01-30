//https://codeforces.com/contest/1093/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N], b[N];
int x[N], y[N];
int ta[N], tb[N];

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
    OffBIT2D<int, N> bit;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        ta[i] = a[i];
        x[a[i]] = i;
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        tb[i] = b[i];
        y[b[i]] = i;
    }
    for (int i = 1; i <= n; i++) {
        bit.upd(x[i], y[i], 0);
    }
    vector<tuple<int, int, int, int, int>> queries;
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int xl, xr, yl, yr;
            cin >> xl >> xr >> yl >> yr;
            queries.push_back(make_tuple(1, xl, xr, yl, yr));
        } else {
            int l, r;
            cin >> l >> r;
            int p = b[l], q = b[r];
            y[p] = r;
            y[q] = l;
            bit.upd(x[p], y[p], 0);
            bit.upd(x[q], y[q], 0);
            swap(b[l], b[r]);

            queries.push_back(make_tuple(2, l, r, -1, -1));
        }
    }
    bit.init();
    for (int i = 1; i <= n; i++) {
        a[i] = ta[i];
        b[i] = tb[i];
        x[a[i]] = i;
        y[b[i]] = i;
    }
    for (int i = 1; i <= n; i++) {
        bit.upd(x[i], y[i], 1);
    }
    for (int i = 0; i < q; i++) {
        if (get<0>(queries[i]) == 1) {
            auto [t, xl, xr, yl, yr] = queries[i];
            cout << bit.query(xl, yl, xr, yr) << endl;
        } else {
            int l = get<1>(queries[i]), r = get<2>(queries[i]);
            int p = b[l], q = b[r];
            bit.upd(x[p], y[p], -1);
            bit.upd(x[q], y[q], -1);
            y[p] = r;
            y[q] = l;
            bit.upd(x[p], y[p], 1);
            bit.upd(x[q], y[q], 1);
            swap(b[l], b[r]);

        }
    }
    return 0;
}
