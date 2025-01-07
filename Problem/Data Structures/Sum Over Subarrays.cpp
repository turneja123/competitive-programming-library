//https://www.codechef.com/problems/SUMFSUB
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;


struct BIT {
    int n;
    vector<long long> t;
    vector<int> ct;
    BIT(int _n) {
        n = _n;
        t.assign(n + 1, 0);
        ct.assign(n + 1, 0);
    }
    void upd(int i, long long val) {
        if (i <= 0) {
            return;
        }
        for (; i <= n; i += (i & -i)) {
            t[i] += val;
            ct[i] += 1;
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
        return query(r) - query(l - 1);
    }

    int query_ct(int i) {
        int ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans += ct[i];
        }
        return ans;
    }
    int query_ct(int l, int r) {
        return query_ct(r) - query_ct(l - 1);
    }
};

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        string s;
        cin >> n >> s;
        int o = 0, z = 0;
        int mid = n + 2;
        BIT ones(2 * n + 5), zeroes(2 * n + 5);
        ones.upd(mid + 0, 0);
        zeroes.upd(mid + 0, 0);
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '1') {
                o++;
            } else {
                z++;
            }
            int diff = o - z;
            ans += (long long)ones.query_ct(1, mid + diff) * o - ones.query(1, mid + diff);
            ones.upd(mid + diff, o);

            diff = -diff;
            ans += (long long)zeroes.query_ct(1, mid + diff - 1) * z - zeroes.query(1, mid + diff - 1);
            zeroes.upd(mid + diff, z);
        }
        cout << ans << endl;

    }

    return 0;

}
