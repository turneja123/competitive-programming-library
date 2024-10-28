//https://codeforces.com/contest/2033/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 1e5 + 5;

int a[N];
int dp[N];
map<long long, int> mp;

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            dp[i] = 0;
        }
        long long sum = 0;
        mp[0] = -1;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            sum += a[i];
            auto it = mp.find(sum);
            if (it != mp.end()) {
                if (it->second == -1) {
                    dp[i] = 1;
                } else {
                    dp[i] = dp[it->second] + 1;
                }
                ans = max(ans, dp[i]);
            }
            if (i != 0) {
                dp[i] = max(dp[i], dp[i - 1]);
            }
            mp[sum] = i;
        }
        cout << ans << endl;
        mp.clear();
    }

    return 0;
}
