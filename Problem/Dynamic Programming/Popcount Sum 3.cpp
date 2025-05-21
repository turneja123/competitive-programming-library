//https://atcoder.jp/contests/abc406/tasks/abc406_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 65;
const long long M = 998244353;

pair<long long, long long> dp[N][N][3];

pair<long long, long long> add(pair<long long, long long> a, pair<long long, long long> b, int d) {
    pair<long long, long long> ans;
    ans.first = (a.first + b.first) % M;
    ans.second = (a.second + b.second * 2 + b.first * d) % M;
    return ans;
}

long long calc(long long n, int k) {
    vector<int> b;
    while (n > 0) {
        b.push_back(n % 2);
        n /= 2;
    }
    reverse(b.begin(), b.end());
    n = b.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < N; j++) {
            for (int t = 0; t < 3; t++) {
                dp[i][j][t] = make_pair(0, 0);
            }
        }
    }
    dp[0][1][2] = make_pair(1, 1);

    for (int i = 1; i < n; i++) {
        for (int j = 1; j < N; j++) {
            for (int d = 0; d < 2; d++) {
                if (d < b[i]) {
                    dp[i][j][0] = add(dp[i][j][0], dp[i - 1][j - d][0], d);
                    dp[i][j][0] = add(dp[i][j][0], dp[i - 1][j - d][2], d);
                    dp[i][j][1] = add(dp[i][j][1], dp[i - 1][j - d][1], d);
                } else if (d == b[i]) {
                    dp[i][j][0] = add(dp[i][j][0], dp[i - 1][j - d][0], d);
                    dp[i][j][2] = add(dp[i][j][2], dp[i - 1][j - d][2], d);
                    dp[i][j][1] = add(dp[i][j][1], dp[i - 1][j - d][1], d);
                } else {
                    dp[i][j][0] = add(dp[i][j][0], dp[i - 1][j - d][0], d);
                    dp[i][j][1] = add(dp[i][j][1], dp[i - 1][j - d][2], d);
                    dp[i][j][1] = add(dp[i][j][1], dp[i - 1][j - d][1], d);
                }
            }
        }
    }
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans = (ans + dp[i][k][0].second + dp[i][k][2].second) % M;
        if (i != n - 1) {
            ans = (ans + dp[i][k][1].second) % M;
        }
    }
    return ans;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        long long n; int k;
        cin >> n >> k;
        cout << calc(n, k) << endl;
    }
    return 0;
}
