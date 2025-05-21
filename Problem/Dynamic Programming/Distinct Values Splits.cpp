//https://cses.fi/problemset/task/3190/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long M = 1e9 + 7;

int a[N];
long long dp[N];

int main() {
    IOS;
    int n;
    cin >> n;
    int l = 0;
    dp[0] = 1; long long pref = 1;
    map<int, int> last;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        auto it = last.find(a[i]);
        if (it != last.end()) {
            while (l < it->second) {
                pref = (pref - dp[l] + M) % M;
                l++;
            }
        }
        last[a[i]] = i;
        dp[i] = pref;
        pref = (pref + dp[i]) % M;
    }
    cout << dp[n];
    return 0;
}
