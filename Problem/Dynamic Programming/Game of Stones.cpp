//https://www.spoj.com/problems/TAP2013J/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

typedef long long ll;

const int N = 1005;
const long long M = 1e9 + 7;

long long dp[N][N][2];

int main(){
	IOS;
    for (int i = 0; i < N; i++) {
        dp[1][i][0] = 1;
    }
    for (int i = 2; i < N; i++) {
        for (int add = 0; add * i < N; add++) {
            for (int j = add * i; j < N; j++) {
                if (i % 2 == 1 || add % 2 == 0) {
                    dp[i][j][0] = (dp[i][j][0] + dp[i - 1][j - add * i][0]) % M;
                    dp[i][j][1] = (dp[i][j][1] + dp[i - 1][j - add * i][1]) % M;
                } else {
                    dp[i][j][1] = (dp[i][j][1] + dp[i - 1][j - add * i][0]) % M;
                    dp[i][j][0] = (dp[i][j][0] + dp[i - 1][j - add * i][1]) % M;
                }
            }
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        long long ans = 0;
        cout << dp[n][n][1] << endl;
    }
	return 0;
}
