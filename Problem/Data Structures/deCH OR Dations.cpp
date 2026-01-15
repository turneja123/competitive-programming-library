//https://codeforces.com/contest/2178/problem/G
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

mt19937_64 gene(chrono::steady_clock::now().time_since_epoch().count());

struct BIT {
    int n;
    vector<__int128> t;
    BIT(int _n) {
        n = _n;
        t.assign(n + 1, 0);
    }
    void upd(int i, __int128 val) {
        if (i <= 0) {
            return;
        }
        for (; i <= n; i += (i & -i)) {
            t[i] ^= val;
        }
    }
    void upd(int l, int r, __int128 val) {
        upd(l, val);
        upd(r + 1, val);
    }
    __int128 query(int i) {
        __int128 ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans ^= t[i];
        }
        return ans;
    }
    __int128 query(int l, int r) {
        return query(r) ^ query(l - 1);
    }
};

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        BIT bit(2 * n), bit_e(2 * n);
        __int128 tot = 0;
        for (int i = 0; i < n; i++) {
            __int128 h = (__int128)gene() ^ ((__int128)gene() << 64);
            int a, b;
            cin >> a >> b;
            int e = !bit_e.query(a + 1, b - 1);
            __int128 s = bit.query(a + 1, b - 1) ^ (e ? h : 0);
            tot ^= s;
            bit.upd(a, s);
            bit.upd(b, s);
            bit_e.upd(a, e);
            bit_e.upd(b, e);

            if (e || tot) {
                cout << 0;
            } else {
                cout << 1;
            }
        }
        cout << endl;
    }
    return 0;
}
