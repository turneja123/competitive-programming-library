//https://cses.fi/problemset/task/1651/
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
};

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    BIT bit(n);
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        bit.upd(i, i, a);
    }
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 2) {
            int k;
            cin >>k;
            cout << bit.query(k) << endl;
        } else {
            int l, r, k;
            cin >> l >> r >> k;
            bit.upd(l, r, k);
        }
    }
    return 0;
}
