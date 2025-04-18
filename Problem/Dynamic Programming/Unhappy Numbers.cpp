//https://www.spoj.com/problems/UNHAPPY/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int D = 2000;

int f[D];
bool seen[D];
long long dp[20][D][3];

vector<int> q;

int dfs(int d) {
    if (d == 1) {
        return true;
    }
    if (seen[d]) {
        return false;
    }
    seen[d] = true;
    q.push_back(d);
    int nx = 0, t = d;
    while (t > 0) {
        nx += (t % 10) * (t % 10);
        t /= 10;
    }
    return dfs(nx);
}

long long calc(long long n) {
    if (n == 0) {
        return 0;
    }
    vector<int> b;
    while (n > 0) {
        b.push_back(n % 10);
        n /= 10;
    }
    reverse(b.begin(), b.end());
    for (int d = 1; d < 10; d++) {
        if (d < b[0]) {
            dp[0][d * d][0]++;
        } else if (d == b[0]) {
            dp[0][d * d][2]++;
        } else {
            dp[0][d * d][1]++;
        }
    }
    int m = b.size();
    for (int i = 1; i < m; i++) {
        for (int s = 1; s < D; s++) {
            for (int d = 0; d < 10; d++) {
                if (s + d * d >= D) {
                    continue;
                }
                if (d < b[i]) {
                    dp[i][s + d * d][0] += dp[i - 1][s][0] + dp[i - 1][s][2];
                    dp[i][s + d * d][1] += dp[i - 1][s][1];
                } else if (d == b[i]) {
                    dp[i][s + d * d][0] += dp[i - 1][s][0];
                    dp[i][s + d * d][1] += dp[i - 1][s][1];
                    dp[i][s + d * d][2] += dp[i - 1][s][2];
                } else {
                    dp[i][s + d * d][0] += dp[i - 1][s][0];
                    dp[i][s + d * d][1] += dp[i - 1][s][1] + dp[i - 1][s][2];
                }
            }
        }
    }
    long long ans = 0;
    for (int i = 0; i < m; i++) {
        for (int s = 1; s < D; s++) {
            if (!f[s]) {
                ans += dp[i][s][0] + dp[i][s][2];
                if (i != m - 1) {
                    ans += dp[i][s][1];
                }
            }
            dp[i][s][0] = 0;
            dp[i][s][1] = 0;
            dp[i][s][2] = 0;
        }
    }
    return ans;
}

int main() {
    IOS;
    for (int i = 1; i < D; i++) {
        f[i] = dfs(i);
        for (int x : q) {
            seen[x] = false;
        }
        q.clear();
    }
    long long l, r;
    cin >> l >> r;
    while (r != 0) {
        long long ans = calc(r) - calc(l - 1);
        cout << ans << endl;
        cin >> l >> r;
    }

    return 0;
}
