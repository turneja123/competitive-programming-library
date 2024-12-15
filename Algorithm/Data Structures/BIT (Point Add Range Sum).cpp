//https://judge.yosupo.jp/problem/point_add_range_sum
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

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
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    BIT t = BIT(n, a);
    for (int i = 0; i < q; i++) {
        int c;
        cin >> c;
        if (c == 0) {
            int j, x;
            cin >> j >> x;
            j++;
            t.upd(j, x);

        } else {
            int l, r;
            cin >> l >> r;
            l++;
            cout << t.query(l, r) << endl;
        }
    }

    return 0;
}
