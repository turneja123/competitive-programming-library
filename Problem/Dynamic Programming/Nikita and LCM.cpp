//https://codeforces.com/contest/1977/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2005;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};


int a[N];

gp_hash_table<int, int, custom_hash> dp[N];

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
        sort(a, a + n);
        long long g = a[0];
        for (int i = 1; i < n; i++) {
            g = g * a[i] / __gcd(g, (long long)a[i]);
            if (g > a[n - 1]) {
                break;
            }
        }
        if (g != a[n - 1]) {
            cout << n << endl;
            continue;
        }
        dp[0][a[0]] = 1;
        for (int i = 1; i < n; i++) {
            for (auto it = dp[i - 1].begin(); it != dp[i - 1].end(); ++it) {
                dp[i][it->first] = max(dp[i][it->first], it->second);
                long long g = (long long)it->first * a[i] / __gcd(it->first, a[i]);
                dp[i][g] = max(dp[i][g], it->second + 1);
            }
            dp[i][a[i]] = max(dp[i][a[i]], 1);
            dp[i - 1].clear();
        }
        int ans = 0;
        for (auto it = dp[n - 1].begin(); it != dp[n - 1].end(); ++it) {
            if (!binary_search(a, a + n, it->first)) {
                ans = max(ans, it->second);
            }
        }
        dp[n - 1].clear();
        cout << ans << endl;
    }

    return 0;
}
