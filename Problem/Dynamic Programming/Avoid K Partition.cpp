//https://atcoder.jp/contests/abc370/tasks/abc370_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long M = 998244353;

long long dp[N];
map<long long, long long> mp;

int main() {
    IOS;
    int n; long long k, sum = 0, prev = 0;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        long long a;
        cin >> a;
        sum += a;
        dp[i] = prev;
        auto it = mp.find(sum - k);
        if (it != mp.end()) {
            dp[i] = (dp[i] - it->second);
        }
        if (sum != k) {
            dp[i]++;
        }
        dp[i] = (dp[i] + M) % M;
        mp[sum] = (mp[sum] + dp[i]) % M;
        prev = (prev + dp[i]) % M;
    }
    cout << dp[n - 1];
    return 0;
}
