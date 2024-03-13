//https://usaco.org/index.php?page=viewproblem2&cpid=1114
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 305;
const int INF = 1e9;

int a[N];
int dp[N][N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j + i < n; j++) {
            if (i == 0) {
                dp[j][j] = 1;
                continue;
            }
            dp[j][j + i] = INF;
            for (int k = j; k < j + i; k++) {
                int add = (a[j] == a[k + 1]) ? 1 : 0;
                dp[j][j + i] = min(dp[j][j + i], dp[j][k] + dp[k + 1][j + i] - add);
            }
        }
    }
    cout << dp[0][n - 1] << endl;


    return 0;
}
