//https://www.spoj.com/problems/KNMD/
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int K = 205;
const int N = 1e6 + 5;

long long a[N];
long long dp[K];
long long dp_next[K];
int mods[N];

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mods[i] = a[i] % k;
    }
    for (int j = 0; j < k; j++) {
        dp[j] = -1;
        dp_next[j] = -1;
    }
    dp[a[0] % k] = a[0];
    for (int i = 1; i < n; i++) {
        dp_next[mods[i]] = a[i];
        int ind = mods[i];
        for (int j = 0; j < k; j++) {
            if (dp[j] != -1) {
                dp_next[ind] = max(dp_next[ind], dp[j] + a[i]);
                dp_next[j] = max(dp_next[j], dp[j]);
            }
            ind++;
            if (ind >= k) {
                ind = 0;
            }
        }
        for (int j = 0; j < k; j++) {
            dp[j] = dp_next[j];
            dp_next[j] = -1;
        }
    }
    for (int i = 0; i < k; i++) {
        cout << ((dp[i] > 0) ? dp[i] : -1) << " ";
    }
    return 0;
}
