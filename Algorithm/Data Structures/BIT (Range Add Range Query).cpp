//https://www.spoj.com/problems/HORRIBLE/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

struct BIT {
    int n;
    vector<long long> t1, t2;

    BIT(int _n) {
        n = _n;
        t1.assign(n + 1, 0);
        t2.assign(n + 1, 0);
    }

    void add(vector<long long> &t, int i, long long v) {
        if (i <= 0) {
            return;
        }
        for (; i <= n; i += (i & -i)) {
            t[i] += v;
        }
    }

    long long sum(vector<long long> &t, int i) {
        long long s = 0;
        for (; i >= 1; i -= (i & -i)) {
            s += t[i];
        }
        return s;
    }

    void upd(int l, int r, long long val) {
        if (l > r) {
            return;
        }
        add(t1, l, val);
        add(t1, r + 1, -val);
        add(t2, l, val * (l - 1));
        add(t2, r + 1, -val * r);
    }

    long long query(int i) {
        if (i <= 0) {
            return 0;
        }
        return sum(t1, i) * i - sum(t2, i);
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
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        BIT bit(n);
        for (int i = 0; i < q; i++) {
            int t;
            cin >> t;
            if (t == 0) {
                int l, r;
                cin >> l >> r;
                ll u;
                cin >> u;
                bit.upd(l, r, u);
            }
            else{
                int l, r;
                cin >> l >> r;
                cout << bit.query(l, r) << endl;
            }
        }
    }
    return 0;
}
