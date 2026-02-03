//https://atcoder.jp/contests/arc213/tasks/arc213_b
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

ll dp[62][2][3];
ll ans[2];

pair<ll, ll> calc(ll n) {
    if (n == -1) {
        return {0, 0};
    }
    if (n == 0) {
        return {1, 0};
    }
    vector<int> d;
    while (n > 0) {
        d.push_back(n % 2);
        n /= 2;
    }
    reverse(d.begin(), d.end());
    int m = d.size();
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < 2; j++) {
            for (int f = 0; f < 3; f++) {
                dp[i][j][f] = 0;

            }
        }
    }

    dp[0][1][2] = 1;

    for (int i = 1; i < m; i++) {
        for (int j = 0; j < 2; j++) {
            for (int f = 0; f < 3; f++) {
                for (int add = 0; add < 2; add++) {
                    int nx_f = f;
                    if (f == 2 && add < d[i]) {
                        nx_f = 0;
                    } else if (f == 2 && add > d[i]) {
                        nx_f = 1;
                    }
                    dp[i][(j + add) % 2][nx_f] += dp[i - 1][j][f];
                }
            }
        }
    }
    ans[0] = 1, ans[1] = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < 2; j++) {
            for (int f = 0; f < 3; f++) {
                if (i < m - 1 || f != 1) {
                    ans[j] += dp[i][j][f];
                }
            }
        }
    }
    return {ans[0], ans[1]};
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int f; ll l, r;
        cin >> f >> l >> r;
        if (l == r) {
            cout << 1 << endl;
            continue;
        }
        int p;
        for (int i = 0; i < 61; i++) {
            ll ca = (1ll << i) & l, cb = (1ll << i) & r;
            if (ca != cb) {
                p = i;
            }
        }
        ll spl = l - 1;
        if ((r - l) < (1ll << p)) {
            ll lf = l, rt = r;
            while (lf <= rt) {
                ll mid = (lf + rt) / 2;
                ll c = (1ll << p) & mid;
                if (c) {
                    spl = mid - 1;
                    rt = mid - 1;
                } else {
                    lf = mid + 1;
                }
            }
        }
        if (f == 0) {
            ll ans = 0;
            if (spl >= l) {
                auto R = calc(spl), L = calc(l - 1);
                R.first -= L.first;
                R.second -= L.second;
                ans += max(R.first, R.second);
            }
            auto R = calc(r), L = calc(spl);
            R.first -= L.first;
            R.second -= L.second;
            ans += max(R.first, R.second);
            cout << ans << endl;
        } else {
            vector<int> a(r - l + 1, 0);
            if (spl >= l) {
                int ct[2];
                ct[0] = 0, ct[1] = 0;
                for (ll i = l; i <= spl; i++) {
                    ct[__builtin_popcountll(i) % 2]++;
                }
                for (ll i = l; i <= spl; i++) {
                    int pc = __builtin_popcountll(i);
                    if (pc % 2 == 0 && ct[0] > ct[1]) {
                        a[i - l] = 1;
                    } else if (pc % 2 == 1 && ct[1] >= ct[0]) {
                        a[i - l] = 1;
                    }
                }
            }
            int ct[2];
            ct[0] = 0, ct[1] = 0;
            for (ll i = spl + 1; i <= r; i++) {
                ct[__builtin_popcountll(i) % 2]++;
            }
            for (ll i = spl + 1; i <= r; i++) {
                int pc = __builtin_popcountll(i);
                if (pc % 2 == 0 && ct[0] > ct[1]) {
                    a[i - l] = 1;
                } else if (pc % 2 == 1 && ct[1] >= ct[0]) {
                    a[i - l] = 1;
                }
            }
            for (ll i = l; i <= r; i++) {
                cout << a[i - l];
            }
            cout << endl;

        }


    }

    return 0;
}
