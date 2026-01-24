//https://dmoj.ca/problem/cco13p6
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e4 + 5;
ll M;


int dp[N][N];
int pref[N][N];


int main() {
    IOS;
    string s;
    cin >> s >> M;
    int n = s.size(), ans = 0;
    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j >= i; j--) {
            if (s[i] == s[j]) {
                dp[i][j] = 1 + (i + 1 == n || j + 1 == n ? 0 : pref[i + 1][j + 1]);
                while (dp[i][j] >= M) {
                    dp[i][j] -= M;
                }
            }
            ans = (ans + dp[i][j]) % M;
            pref[i][j] = dp[i][j] + (i + 1 == n ? 0 : pref[i + 1][j]) + (j + 1 == n ? 0 : pref[i][j + 1]) - (i + 1 == n || j + 1 == n ? 0 : pref[i + 1][j + 1]);
            while (pref[i][j] >= M) {
                pref[i][j] -= M;
            }
            while (pref[i][j] < 0) {
                pref[i][j] += M;
            }
            if (i != j) {
                dp[j][i] = dp[i][j];
                ans = (ans + dp[j][i]) % M;
                pref[j][i] = pref[i][j];
            }
            while (ans >= M) {
                ans -= M;
            }
        }
    }
    cout << (ans + 1) % M;

    return 0;
}
