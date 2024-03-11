//https://cses.fi/problemset/task/1653/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int K = 22;
const int N = 1 << K;

long long a[K];
pair<int, long long> dp[N];

int main() {
    IOS;
    int n, x;
    cin >> n >> x;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int k = 1 << n;
    for (int i = 0; i < k; i++) {
        dp[i] = make_pair(K, x);
    }
    dp[0] = make_pair(1, 0);
    for (int i = 1; i < k; i++) {
        for (int j = 0; j < n; j++) {
            int bit = 1 << j;
            int c = i & bit;
            if (c != 0) {
                int ct; long long wt;
                if (a[j] + dp[i ^ bit].second > x) {
                    ct = dp[i ^ bit].first + 1;
                    wt = a[j];
                } else {
                    ct = dp[i ^ bit].first;
                    wt = a[j] + dp[i ^ bit].second;
                }
                dp[i] = min(dp[i], make_pair(ct, wt));
            }
        }
    }
    cout << dp[k - 1].first << endl;

    return 0;
}
