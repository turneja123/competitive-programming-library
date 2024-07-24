//https://www.spoj.com/problems/BABY/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int K = 16;
const int N = 1 << K;

int a[K];
int b[K];

int dp[N];

int main() {
    IOS;
    int k;
    cin >> k;
    while (k != 0) {
        for (int i = 0; i < k; i++) {
            cin >> a[i];
            a[i]--;
        }
        for (int j = 0; j < k; j++) {
            cin >> b[j];
            b[j]--;
        }
        int n = 1 << k;
        for (int mask = 0; mask < n; mask++) {
            dp[mask] = N;
        }
        dp[0] = 0;

        for (int i = 0; i < k; i++) {
            for (int mask = 0; mask < n; mask++) {
                if (__builtin_popcount(mask) != i + 1) {
                    continue;
                }
                for (int j = 0; j < k; j++) {
                    int c = mask & (1 << j);
                    if (c) {
                        dp[mask] = min(dp[mask], dp[mask ^ (1 << j)] + abs(i - j) + abs(a[i] - b[j]));
                    }
                }
            }
        }
        cout << dp[n - 1] << endl;

        cin >> k;
    }
    return 0;
}
