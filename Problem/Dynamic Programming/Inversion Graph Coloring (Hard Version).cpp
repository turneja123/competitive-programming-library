//https://codeforces.com/contest/2143/problem/D2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2005;
const ll M = 1e9 + 7;

int a[N];
ll dp[N][N];
ll add[N][N];

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
            t[i] %= M;
        }
    }
    long long query(int i) {
        long long ans = 0;
        for (; i >= 1; i -= (i & -i)) {
            ans += t[i];
        }
        return ans % M;
    }
    long long query(int l, int r) {
        return (query(r) - query(l - 1) + M) % M;
    }
};

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        vector<BIT> bitr, bitc;
        for (int i = 0; i <= n + 1; i++) {
            BIT bit(n + 2);
            bitr.push_back(bit);
            bitc.push_back(bit);
        }
        dp[a[0]][0]++;
        bitr[0].upd(a[0] + 1, 1);
        bitc[a[0]].upd(1, 1);
        for (int i = 1; i < n; i++) {
            /*for (int j = n; j >= 0; j--) {
                for (int k = n - 1; k >= 0; k--) {
                    if (k > a[i]) {
                        continue;
                    }
                    if (a[i] >= j) {
                        dp[a[i]][k] = (dp[a[i]][k] + dp[j][k]) % M;
                    } else if (a[i] >= k) {
                        dp[j][a[i]] = (dp[j][a[i]] + dp[j][k]) % M;
                    }
                }
            }
            dp[a[i]][0]++;*/
            for (int k = 0; k <= a[i]; k++) {
                add[a[i]][k] = (add[a[i]][k] + bitr[k].query(1, a[i] + 1)) % M;
            }
            for (int j = a[i] + 1; j <= n; j++) {
                add[j][a[i]] = (add[j][a[i]] + bitc[j].query(1, a[i] + 1)) % M;
            }
            add[a[i]][0] = (add[a[i]][0] + 1) % M;

            for (int k = 0; k <= a[i]; k++) {
                dp[a[i]][k] = (dp[a[i]][k] + add[a[i]][k]) % M;
                bitr[k].upd(a[i] + 1, add[a[i]][k]);
                bitc[a[i]].upd(k + 1, add[a[i]][k]);
                add[a[i]][k] = 0;
            }
            for (int j = a[i] + 1; j <= n; j++) {
                dp[j][a[i]] = (dp[j][a[i]] + add[j][a[i]]) % M;
                bitc[j].upd(a[i] + 1, add[j][a[i]]);
                bitr[a[i]].upd(j + 1, add[j][a[i]]);
                add[j][a[i]] = 0;

            }
        }
        ll ans = 0;
        for (int j = 0; j <= n; j++) {
            for (int k = 0; k <= n; k++) {
                ans = (ans + dp[j][k]) % M;
                dp[j][k] = 0;
            }
        }
        cout << (ans + 1) % M << endl;
    }

    return 0;
}
