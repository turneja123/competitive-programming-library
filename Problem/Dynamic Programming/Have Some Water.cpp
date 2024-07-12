//https://toph.co/arena?practice=668ee600a4f184cd2ac3fb1f#!/p/65b13addfb1dbd27709c36a2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const long long INF = 1e18;

int a[N];
long long dp[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n;
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            dp[i] = INF;
            sum += a[i];
        }
        map<long long, int> last;
        last[a[0]] = 0;
        dp[0] = a[0];
        for (int i = 1; i < n; i++) {
            map<long long, int> mp;
            mp[a[i]] = i;
            dp[i] = dp[i - 1] + a[i];
            for (auto it = last.begin(); it != last.end(); ++it) {
                long long x = it->first * (long long)a[i] / __gcd(it->first, (long long)a[i]);
                if (x > sum) {
                    continue;
                }
                auto itt = mp.find(x);
                if (itt == mp.end()) {
                    mp[x] = it->second;
                } else {
                    mp[x] = min(mp[x], it->second);
                }

                dp[i] = min(dp[i], x + ((it->second == 0) ? 0 : dp[it->second - 1]));
            }
            last = mp;
        }
        cout << min(sum, dp[n - 1]) << endl;
    }


    return 0;
}
