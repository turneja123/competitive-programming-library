//https://atcoder.jp/contests/abc363/tasks/abc363_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const __int128 R = 1e18;

long long dp[50][3][3];

void print(__int128 x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

void add(int i, int xn, int yn, int ck, int d) {
    if (ck > d) {
        dp[i][xn][0] += dp[i - 1][yn][0] + dp[i - 1][yn][2] + dp[i - 1][yn][1];
    } else if (ck == d) {
        dp[i][xn][0] += dp[i - 1][yn][0];
        dp[i][xn][1] += dp[i - 1][yn][1];
        dp[i][xn][2] += dp[i - 1][yn][2];
    } else {
        dp[i][xn][1] += dp[i - 1][yn][1] + dp[i - 1][yn][2] + dp[i - 1][yn][0];
    }
    return;
}

long long calc(__int128 n) {
    vector<int> v;
    while (n > 0) {
        v.push_back(n % 10);
        n /= 10;
    }
    reverse(v.begin(), v.end());
    int m = v.size();
    for (int dx = 0; dx < 3; dx++) {
        for (int dy = 0; dy < 3; dy++) {
            dp[0][dx][dy] = 0;
        }
    }
    for (int d = 1; d < 10; d++) {
        int cn = v[0], ck = v[m - 1];
        if (cn > d && ck > d) {
            dp[0][0][0] += 1;
        } else if (cn > d && ck == d) {
            dp[0][0][2] += 1;
        } else if (cn > d && ck < d) {
            dp[0][0][1] += 1;
        } else if (cn == d && ck > d) {
            dp[0][2][0] += 1;
        } else if (cn == d && ck == d) {
            dp[0][2][2] += 1;
        } else if (cn == d && ck < d) {
            dp[0][2][1] += 1;
        } else if (cn < d && ck > d) {
            dp[0][1][0] += 1;
        } else if (cn < d && ck == d) {
            dp[0][1][2] += 1;
        } else if (cn < d && ck < d) {
            dp[0][1][1] += 1;
        }
    }
    for (int i = 1; i < m / 2 + m % 2; i++) {
        for (int dx = 0; dx < 3; dx++) {
            for (int dy = 0; dy < 3; dy++) {
                dp[i][dx][dy] = 0;
            }
        }
        int cn = v[i], ck = v[m - 1 - i];
        for (int d = 0; d < 10; d++) {
            if (cn > d) {
                add(i, 0, 0, ck, d);
                add(i, 0, 2, ck, d);
                add(i, 1, 1, ck, d);
            } else if (cn == d) {
                add(i, 0, 0, ck, d);
                add(i, 1, 1, ck, d);
                add(i, 2, 2, ck, d);
            } else {
                add(i, 0, 0, ck, d);
                add(i, 1, 1, ck, d);
                add(i, 1, 2, ck, d);
            }
        }
    }
    long long ans = dp[m / 2 + m % 2 - 1][0][0] + dp[m / 2 + m % 2 - 1][0][1] + dp[m / 2 + m % 2 - 1][0][2] + dp[m / 2 + m % 2 - 1][2][0] + dp[m / 2 + m % 2 - 1][2][2];
    return ans;
}

long long solve(__int128 n) {
    if (n < 10) {
        return n + 1;
    }
    long long ans = 10, cur = 9, j = 1; __int128 prod = 100;
    while (prod < n) {
        if (j % 2 == 0) {
            cur *= 10;
        }
        ans += cur;
        prod *= 10;
        j++;
    }
    ans += calc(n);
    return ans;
}


int main() {
    IOS;
    long long n;
    cin >> n;
    __int128 l = 0, r = R * R, ans = R * R;
    while (l <= r) {
        __int128 mid = (l + r) / 2;
        long long ct = solve(mid);
        if (ct >= n) {
            r = mid - 1;
            ans = min(ans, mid);
        } else {
            l = mid + 1;
        }
    }
    print(ans);
    return 0;
}
