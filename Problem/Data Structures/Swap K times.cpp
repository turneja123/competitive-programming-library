//https://atcoder.jp/contests/arc214/tasks/arc214_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const ll INF = 1e18;

vector<int> ids[N];
vector<tuple<int, int, int, int>> ask[N];

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
};

ll cost(ll s, ll k) {
    if (k % 2 == 0 && s % 2 == 1) {
        return INF;
    }
    ll c = (s + k - 1) / k;
    if (s % 2 != (c * k) % 2) {
        c++;
    }
    return c;

}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            a[i]--;
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
            b[i]--;
            ids[b[i]].push_back(i);
        }
        vector<int> ptr(n, 0), last(n, -1);
        vector<tuple<int, int, int, int>> queries;
        ll s = 0;
        BIT bit_inv(n);
        for (int i = 0; i < n; i++) {
            if (last[a[i]] != -1) {
                queries.push_back({last[a[i]], i, ids[a[i]][ptr[a[i]] - 1] + 1, ids[a[i]][ptr[a[i]]] - 1});
            }
            last[a[i]] = i;
            a[i] = ids[a[i]][ptr[a[i]]++];
            s += bit_inv.query(a[i] + 2, n);
            bit_inv.upd(a[i] + 1, 1);
        }
        ll best = cost(s, k);
        if (!queries.empty()) {
            int q = queries.size();
            vector<ll> ans(q, 0);
            ll mn = INF;
            for (int i = 0; i < q; i++) {
                auto [l, r, lq, rq] = queries[i];
                if (lq > rq) {
                    continue;
                }
                ask[lq].push_back({l, r, i, -1});
                ask[rq + 1].push_back({l, r, i, 1});
            }
            vector<int> ord(n);
            iota(ord.begin(), ord.end(), 0);
            sort(ord.begin(), ord.end(), [&](int x, int y) {return a[x] < a[y];});
            BIT bit(n);
            for (int i = 0; i < n; i++) {
                for (auto [l, r, ind, sgn] : ask[i]) {
                    ans[ind] += bit.query(l + 1, r + 1) * sgn;
                }
                int j = ord[i];
                bit.upd(j + 1, 1);
            }
            for (int i = 0; i < q; i++) {
                mn = min(mn, ans[i]);
            }
            best = min(best, cost(s + 1 + 2 * mn, k));
        }
        if (best == INF) {
            best = -1;
        }
        cout << best << endl;

        for (int i = 0; i < n; i++) {
            ids[i].clear();
            ask[i].clear();
        }
    }

    return 0;
}
