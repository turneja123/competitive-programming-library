//https://www.codechef.com/problems/MEANDIFF2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ld = long double;

struct BIT {
    int n;
    vector<ll> t;
    BIT(int _n) {
        n = _n;
        t.assign(n + 1, 0);
    }
    void upd(int i, ll val) {
        if (i <= 0) {
            return;
        }
        for (; i <= n; i += (i & -i)) {
            t[i] += val;
        }
    }
    ll query(int i) {
        ll ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans += t[i];
        }
        return ans;
    }
    ll query(int l, int r) {
        return query(r) - query(l - 1);
    }
    int lb(int x) {
        if (x <= 0) {
            return 1;
        }
        int j = 0, s = 0, p = 1;
        while ((p << 1) <= n) {
            p <<= 1;
        }
        for (int k = p; k; k >>= 1) {
            if (j + k <= n && s + t[j + k] < x) {
                s += t[j + k];
                j = j + k;
            }
        }
        return j + 1;
    }
};

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<ll> a(n);
        vector<int> idl(n), idr(n);
        vector<pair<int, int>> ord;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            ord.push_back({a[i], i});
        }
        sort(ord.begin(), ord.end());
        for (int i = 0; i < n; i++) {
            idl[ord[i].second] = i;
            idr[ord[i].second] = n - 1 - i;
        }
        BIT bitl_ct(n), bitl_sum(n), bitr_ct(n), bitr_sum(n);
        ll ans = 0;
        auto f = [&](int x, int k, int z) -> ld {
            if (z == 0) {
                int j = bitl_ct.lb(k);
                ld ans = (ld)x - (ld)(x + bitl_sum.query(j)) / (ld)(k + 1);
                return ans;
            } else {
                int j = bitr_ct.lb(k);
                ld ans = (ld)(x + bitr_sum.query(j)) / (ld)(k + 1) - (ld)x;
                return ans;
            }
        };
        auto calc = [&](int i, int R, int flag) -> void {
            bitl_ct.upd(idl[i] + 1, -1);
            bitl_sum.upd(idl[i] + 1, -a[i]);
            bitr_ct.upd(idr[i] + 1, -1);
            bitr_sum.upd(idr[i] + 1, -a[i]);
            int x = a[i];
            int l = 1, r = R;
            if (flag == 1) {
                while (r - l >= 3) {
                    int m1 = l + (r - l) / 3;
                    int m2 = r - (r - l) / 3;

                    ld f1 = f(x, m1, 0);
                    ld f2 = f(x, m2, 0);

                    if (f1 < f2) {
                        l = m1 + 1;
                    } else {
                        r = m2 - 1;
                    }
                }
                for (; l <= r; l++) {
                    int j = bitl_ct.lb(l);
                    ans = max(ans, x - (x + bitl_sum.query(j)) / (l + 1));
                }
            }

            l = 1, r = R;
            if (flag == 0) {
                while (r - l >= 3) {
                    int m1 = l + (r - l) / 3;
                    int m2 = r - (r - l) / 3;

                    ld f1 = f(x, m1, 1);
                    ld f2 = f(x, m2, 1);

                    if (f1 < f2) {
                        l = m1 + 1;
                    } else {
                        r = m2 - 1;
                    }
                }
                for (; l <= r; l++) {
                    int j = bitr_ct.lb(l);
                    ans = max(ans, (x + bitr_sum.query(j)) / (l + 1) - x);
                }
            }

            bitl_ct.upd(idl[i] + 1, 1);
            bitl_sum.upd(idl[i] + 1, a[i]);
            bitr_ct.upd(idr[i] + 1, 1);
            bitr_sum.upd(idr[i] + 1, a[i]);
        };
        set<pair<int, int>> st;
        for (int i = 0; i < n; i++) {
            st.insert({a[i], i});
            bitl_ct.upd(idl[i] + 1, 1);
            bitl_sum.upd(idl[i] + 1, a[i]);
            bitr_ct.upd(idr[i] + 1, 1);
            bitr_sum.upd(idr[i] + 1, a[i]);
            if (i != 0) {
                calc(st.begin()->second, i, 0);
                calc(st.rbegin()->second, i, 1);
            }
            cout << ans << " ";
        }
        cout << endl;
    }
    return 0;
}
