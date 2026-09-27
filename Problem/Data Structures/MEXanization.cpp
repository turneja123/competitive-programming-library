//https://codeforces.com/contest/1870/problem/G
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

struct BIT {
    int n = 0, pw = 1;
    vector<int> x, t;
    void init() {
        n = x.size();
        t.assign(n + 1, 0);
        while ((pw << 1) <= n) {
            pw <<= 1;
        }
    }
    void upd(int val) {
        int i = lower_bound(x.begin(), x.end(), val) - x.begin() + 1;
        for (; i <= n; i += i & -i) {
            t[i]++;
        }
    }
    int query(int val) {
        int i = upper_bound(x.begin(), x.end(), val) - x.begin();
        int ans = 0;
        for (; i > 0; i -= i & -i) {
            ans += t[i];
        }
        return ans;
    }
    int missing(int r) {
        int k = r - 1 - query(r);
        if (k == 0) {
            return 1;
        }
        int p = 0, sum = 0;
        for (int j = pw; j > 0; j >>= 1) {
            int q = p + j;
            if (q <= n && x[q - 1] - 1 - sum - t[q] < k) {
                p = q;
                sum += t[q];
            }
        }
        return k + sum + 1;
    }
};

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n), ct(n + 1, 0), tot(n + 1, 0);
        int first = 1;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (i == 0) {
                first = max(1, a[i]);
            }
            a[i] = min(a[i], n);
            tot[a[i]]++;
        }
        int b = 1;
        for (int i = 2; i < n; i++) {
            b = max(b, tot[i]);
        }
        vector<BIT> bit(b + 1);
        for (int i = 2; i < n; i++) {
            for (int j = 1; j <= tot[i]; j++) {
                bit[j].x.push_back(i);
            }
        }
        for (int j = 1; j <= b; j++) {
            bit[j].init();
        }
        auto cost = [&](int k) -> int {
            if (k > n) {
                return n + 1;
            }
            ll ans = k;
            int need = 1, p = k - 1;
            while (p >= 2) {
                if (ct[p] >= need) {
                    p = bit[need].missing(p);
                    if (p < 2) {
                        break;
                    }
                }
                int add = need - ct[p];
                ans += (ll)(p - 1) * add;
                if (ans > n) {
                    return n + 1;
                }
                need += add;
                p--;
            }
            return ans;
        };
        int r = 1, c = 2;
        for (int i = 0; i < n; i++) {
            int x = a[i];
            ct[x]++;
            if (x >= 2 && x < n) {
                bit[ct[x]].upd(x);
            }
            if (x >= 2 && x <= r) {
                c = cost(r + 1);
            }
            while (c <= i + 1) {
                r++;
                c = cost(r + 1);
            }
            cout << (i == 0 ? first : r) << " ";
        }
        cout << endl;
    }
    return 0;
}
