//https://www.spoj.com/problems/ADACABAA/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

struct Data {
    int x, y, z, w, i;
    Data() {};
    Data(int x, int y, int z, int w, int i) : x(x), y(y), z(z), w(w), i(i) {};

};

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


vector<Data> a;
int ans[N];

vector<Data> calc(int l, int r, OffBIT2D<int, N> &bit) {
    if (l == r) {
        return {a[l]};
    }
    int mid = (l + r) / 2;
    vector<Data> lf = calc(l, mid, bit);
    vector<Data> rt = calc(mid + 1, r, bit);
    vector<Data> v;
    int i = 0, j = 0;
    while (i < lf.size() && j < rt.size()) {
        if (lf[i].y < rt[j].y) {
            bit.upd(lf[i].z, lf[i].w, 1);
            v.push_back(lf[i++]);
        } else {
            ans[rt[j].i] += bit.query(rt[j].z - 1, rt[j].w - 1);
            v.push_back(rt[j++]);
        }
    }
    while (j < rt.size()) {
        ans[rt[j].i] += bit.query(rt[j].z - 1, rt[j].w - 1);
        v.push_back(rt[j++]);
    }
    for (int k = 0; k < i; k++) {
        bit.upd(lf[k].z, lf[k].w, -1);
    }
    while (i < lf.size()) {
        v.push_back(lf[i++]);
    }
    return v;
}

int main() {
    IOS;
    int n;
    cin >> n;
    a.resize(n);
    vector<array<int, 2>> upd;
    OffBIT2D<int, N> bit;
    for (int i = 0; i < n; i++) {
        int x, y, z, w;
        cin >> x >> y >> z >> w;
        a[i] = Data(x, y, z, w, i);
        bit.upd(z, w, 0);
    }
    sort(a.begin(), a.end(),
         [](Data a, Data b) -> bool {
            return a.x < b.x;
            });
    bit.init();
    calc(0, n - 1, bit);
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += ans[i] == 0;
    }
    cout << sum;
    return 0;
}
