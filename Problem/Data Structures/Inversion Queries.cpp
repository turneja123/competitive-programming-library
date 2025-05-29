//https://www.codechef.com/START188A/problems/INVQUER
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
long long big[N];
long long small[N];

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
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        BIT bita(n + 2), bitb(n + 2);
        for (int i = 0; i < n; i++) {
            if (a[i] != n) {
                big[a[i]] += bita.query(a[i] + 1, n);
            }
            bita.upd(a[i], 1);
        }
        for (int i = n - 1; i >= 0; i--) {
            if (a[i] != 1) {
                small[a[i]] += bitb.query(1, a[i] - 1);
            }
            bitb.upd(a[i], 1);
        }
        for (int i = 1; i <= n; i++) {
            small[i] += small[i - 1];
        }
        for (int i = n; i > 0; i--) {
            big[i] += big[i + 1];
        }
        long long inv = small[n];
        for (int i = 0; i < q; i++) {
            int l, r;
            cin >> l >> r;
            if (l == r) {
                cout << 0 << endl;
            } else {
                cout << inv - small[l] - big[r] << endl;

            }
        }
        for (int i = 0; i <= n; i++) {
            big[i] = 0;
            small[i] = 0;
        }
    }
	return 0;
}
