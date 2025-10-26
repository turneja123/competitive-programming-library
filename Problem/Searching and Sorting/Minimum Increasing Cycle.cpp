//https://eolymp.com/en/problems/12253
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const int INF = 1e9 + 1;

int a[N];
int dp[N];
int suf[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            dp[i + 1] = INF;
        }
        suf[n - 1] = 0;
        for (int i = n - 2; i >= 0; i--) {
            suf[i] = suf[i + 1] + (a[i] > a[i + 1]);
        }
        int ans = 0;
        dp[0] = 0;
        if (a[0] < k || suf[0] == 0) {
            dp[1] = a[0];
            ans = 1;
        }
        for (int i = 1; i < n; i++) {
            if (!(a[i] < k || suf[i] == 0)) {
                continue;
            }
            int l = 1, r = n, mx = 0;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (dp[mid] <= a[i]) {
                    l = mid + 1;
                    mx = mid;
                } else {
                    r = mid - 1;
                }
            }
            dp[mx + 1] = min(dp[mx + 1], a[i]);
            ans = max(ans, mx + 1);
        }
        cout << n - ans << endl;
    }
    return 0;
}
