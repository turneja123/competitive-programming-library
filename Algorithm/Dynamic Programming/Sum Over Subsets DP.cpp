//https://cses.fi/problemset/task/1654
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int K = 20;
const int N = 2e5 + 5;

int a[N];
int ct[1 << K];
long long dp[1 << K];
long long dp_super[1 << K];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        ct[a[i]]++;
    }
    int bits = 1 << K;
    for (int j = 0; j < bits; j++) {
        dp[j] = ct[j];
        dp_super[j] = ct[j];
    }
    for (int k = 0; k < K; k++) {
        for (int j = 0; j < bits; j++) {
            if (j & (1 << k)) {
                dp[j] += dp[j ^ (1 << k)];
            }
            if (!(j & (1 << k))) {
                dp_super[j] += dp_super[j | (1 << k)];
            }
        }
    }
    long long sum = 0;
    for (int i = 0; i < n; i++) {
        sum += dp[a[i]];
    }
    for (int i = 0; i < n; i++) {
        int j = a[i];
        int complement = (bits - 1) ^ j;
        cout << dp[j] << " " << dp_super[j] << " " << dp[bits - 1] - dp[complement] << endl;
    }

    return 0;
}
