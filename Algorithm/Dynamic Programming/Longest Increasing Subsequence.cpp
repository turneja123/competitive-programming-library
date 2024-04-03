//https://cses.fi/problemset/task/1145/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int INF = 1e9;

int a[N];
int dp[N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        dp[i + 1] = INF;
    }
    int ans = 1;
    dp[1] = a[0];
    for (int i = 1; i < n; i++) {
        int l = 1, r = n, mx = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (dp[mid] < a[i]) {
                l = mid + 1;
                mx = mid;
            } else {
                r = mid - 1;
            }
        }
        dp[mx + 1] = min(dp[mx + 1], a[i]);
        ans = max(ans, mx + 1);
    }
    cout << ans;
    return 0;
}
