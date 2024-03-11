//solution for https://www.hackerearth.com/challenges/competitive/april-circuits-21/algorithm/place-sign-3bb0be4c/
#pragma GCC target ("avx2")
#pragma GCC optimization ("Ofast")
#pragma GCC optimization ("unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e3 + 5;
const ll M = 1e9 + 7;

ll dp[N][N];
ll pref[N];

int main() {
    IOS;
    int n; string s;
    cin >> n >> s;
    for (int i = 0; i < n; i++) {
        dp[0][i] = 1;
    }
    pref[0] = dp[0][0];
    for (int i = 1; i < n; i++) {
        pref[i] = dp[0][i] + pref[i - 1];
    }
    for (int i = 1; i < n; i++) {
        if (s[i - 1] == '<') {
            for (int j = 0; j < n; j++) {
                if (j == 0) {
                    dp[i][j] = 0;
                } else {
                    dp[i][j] = pref[j - 1] % M;
                }
            }
        }
        if (s[i - 1] == '>') {
            for (int j = 0; j < n; j++) {
                dp[i][j] = (pref[n - 1] - pref[j]) % M;
            }
        }
        if (s[i - 1] == '=') {
            for (int j = 0; j < n; j++) {
                dp[i][j] = dp[i - 1][j];
            }
        }
        pref[0] = dp[i][0];
        for (int j = 1; j < n; j++) {
            pref[j] = dp[i][j] + pref[j - 1];
        }
    }
    cout << pref[n - 1] % M << endl;
    return 0;
}
