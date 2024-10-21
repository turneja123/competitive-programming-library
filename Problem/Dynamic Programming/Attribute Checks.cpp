//https://codeforces.com/contest/2025/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e6 + 5;
const int M = 5005;

int a[N];
int dp[M][M];
int freq[2][N];
int pref[2][N];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    a[n] = 0;
    n++;
    int i = 0;
    while (i < n && a[i] != 0) {
        i++;
    }
    i++;
    int j = 1, ans = 0;
    for (; i < n; i++) {
        if (a[i] > 0) {
            if (a[i] <= j) {
                freq[0][a[i]]++;
            }
        } else if (a[i] < 0) {
            a[i] = abs(a[i]);
            if (a[i] <= j) {
                freq[1][a[i]]++;
            }

        } else {
            for (int k = 0; k <= j; k++) {
                pref[0][k] = ((k == 0) ? freq[0][k] : pref[0][k - 1] + freq[0][k]);
                pref[1][k] = ((k == 0) ? freq[1][k] : pref[1][k - 1] + freq[1][k]);
            }
            for (int k = 0; k <= j; k++) {
                int Str = k, Int = j - k;
                dp[j][k] = max(dp[j][k], dp[j - 1][k] + pref[0][Str] + pref[1][Int]);
                dp[j][k + 1] = max(dp[j][k + 1], dp[j - 1][k] + pref[0][Str] + pref[1][Int]);
                ans = max(ans, dp[j - 1][k] + pref[0][Str] + pref[1][Int]);
            }
            for (int k = 0; k <= j; k++) {
                freq[0][k] = 0;
                freq[1][k] = 0;
                pref[0][k] = 0;
                pref[1][k] = 0;
            }
            j++;
        }
    }
    cout << ans;

    return 0;
}
