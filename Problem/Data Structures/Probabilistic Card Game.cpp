//https://codeforces.com/contest/2203/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll M = 998244353;
const ll INF = 1e18;

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
    int lb(ll x) {
        if (x <= 0) {
            return 1;
        }
        int j = 0, p = 1; ll s = 0;
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

ll modPow(ll a, ll y) {
    ll res = 1;
    while (y > 0) {
        if (y % 2 != 0) {
            res = res * a % M;
        }
        y /= 2;
        a = a * a % M;
    }
    return res;
}

int main() {
    IOS;
    int n;
    cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<ll> compr = a;

    sort(compr.begin(), compr.end());
    auto get = [&](ll a) -> int {
        return lower_bound(compr.begin(), compr.end(), a) - compr.begin() + 1;
    };
    vector<int> seen(n + 1, 0);
    BIT bit_sum(n + 1), bit_cnt(n + 1);
    for (int i = 0; i < n; i++) {
        int j = get(a[i]);
        bit_cnt.upd(j, 1);
        bit_sum.upd(j, a[i]);
        seen[j] = 1;
        if (i < 2) {
            continue;
        }

        auto calc = [&](int mid) -> ll {
            int j = bit_cnt.lb(mid);
            ll mx = -INF;

            ll ct = mid;
            int r = bit_cnt.lb(ct + 1);
            if (r <= n) {
                mx = max(mx, bit_sum.query(r, n) - bit_cnt.query(r, n) * compr[r - 1]);
            }

            if (ct > 1) {
                int l = bit_cnt.lb(ct - 1);
                mx = max(mx, bit_cnt.query(l) * compr[l - 1] - bit_sum.query(l));
            }
            return mx;
        };


        int l = 1, r = i, spl = i + 1;
        while (l <= r) {
            int mid = (l + r) / 2;

            if (calc(mid) >= calc(mid + 1)) {
                l = mid + 1;
            } else {
                spl = mid;
                r = mid - 1;
            }

        }
        ll ans = calc(spl);
        cout << ans % M * modPow(i - 1, M - 2) % M << endl;
    }

    return 0;
}
