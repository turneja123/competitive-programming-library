//https://ocpc2026w.eolymp.space/en/compete/r1t2e978517l1a1e5a39p463hs/problem/4
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

ll a[N];
ll suf[N];
ll ans[N];

struct BIT {
    int n;
    vector<long long> t;
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
    long long query(int i) {
        long long ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans += t[i];
        }
        return ans;
    }
    long long query(int l, int r) {
        if (l > r) {
            return 0;
        }
        return query(r) - query(l - 1);
    }
};

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    vector<ll> compr;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        compr.push_back(a[i]);
    }
    sort(compr.begin(), compr.end());
    compr.erase(unique(compr.begin(), compr.end()), compr.end());
    for (int i = n - 1; i >= 0; i--) {
        suf[i] = max(suf[i + 1], a[i]);
    }
    vector<pair<ll, int>> queries;
    for (int i = 0; i < q; i++) {
        ll x;
        cin >> x;
        queries.push_back({x, i});
    }
    sort(queries.begin(), queries.end());

    int m = compr.size();
    BIT bit_sum(m), bit_ct(m);

    for (int i = 0, l = 0; i < q; i++) {
        auto [x, j] = queries[i];
        while (l < n) {
            int ok = 0;
            ll goal = suf[l] + x;
            int j = upper_bound(compr.begin(), compr.end(), goal) - compr.begin();
            if (j == m) {
                ok = 1;
            } else {
                ll need = bit_sum.query(j + 1, m) - bit_ct.query(j + 1, m) * goal;
                if (need <= x) {
                    ok = 1;
                }
            }
            if (ok) {
                int id = lower_bound(compr.begin(), compr.end(), a[l]) - compr.begin();
                bit_sum.upd(id + 1, a[l]);
                bit_ct.upd(id + 1, 1);
                l++;
            } else {
                break;
            }
        }
        ans[j] = l;
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }



    return 0;
}
