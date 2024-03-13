//https://codeforces.com/contest/628/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2005;
const int D = 2005;
const long long M = 1e9 + 7;

long long dp[N][D][2];
int d, k;

long long calc(string s) {
    int n = s.size();

    for (int i = 0; i < d; i++) {
        dp[n - 1][i][0] = 0;
        dp[n - 1][i][1] = 0;
    }
    long long ans = 0;
    for (int i = 0; i <= 9; i++) {
        int c = s[n - 1] - '0';
        if (i == k && n % 2 == 1) {
            continue;
        }
        if (i != k && n % 2 == 0) {
            continue;
        }
        if (i <= c) {
            dp[n - 1][i % d][0]++;
            if (i % d == 0 && i != 0) {
                ans++;
            }
        } else {
            dp[n - 1][i % d][1]++;
            if (s.size() > 1 && i % d == 0 && i != 0) {
                ans++;
            }
        }
    }
    int j = 1;
    long long ex = 1;
    for (int i = n - 2; i >= 0; i--, j++) {
        int c = s[i] - '0';
        ex = (ex * 10) % d;
        for (int m = 0; m < d; m++) {
            dp[i][m][0] = 0;
            dp[i][m][1] = 0;
            for (int cif = 0; cif <= 9; cif++) {
                if (cif == k && (i + 1) % 2 == 1) {
                    continue;
                }
                if (cif != k && (i + 1) % 2 == 0) {
                    continue;
                }
                if (cif < c) {
                    dp[i][m][0] = (dp[i][m][0] + dp[i + 1][(((m - ex * cif) % d) + d) % d][0]) % M;
                    dp[i][m][0] = (dp[i][m][0] + dp[i + 1][(((m - ex * cif) % d) + d) % d][1]) % M;
                    if (m == 0 && cif > 0) {
                        ans = (ans + dp[i + 1][(((m - ex * cif) % d) + d) % d][0]) % M;
                        ans = (ans + dp[i + 1][(((m - ex * cif) % d) + d) % d][1]) % M;
                    }
                } else if (cif > c) {
                    dp[i][m][1] = (dp[i][m][1] + dp[i + 1][(((m - ex * cif) % d) + d) % d][0]) % M;
                    dp[i][m][1] = (dp[i][m][1] + dp[i + 1][(((m - ex * cif) % d) + d) % d][1]) % M;
                    if (m == 0 && i > 0 && cif > 0) {
                        ans = (ans + dp[i + 1][(((m - ex * cif) % d) + d) % d][0]) % M;
                        ans = (ans + dp[i + 1][(((m - ex * cif) % d) + d) % d][1]) % M;
                    }
                } else {
                    dp[i][m][0] = (dp[i][m][0] + dp[i + 1][(((m - ex * cif) % d) + d) % d][0]) % M;
                    dp[i][m][1] = (dp[i][m][1] + dp[i + 1][(((m - ex * cif) % d) + d) % d][1]) % M;
                    if (m == 0 && cif > 0) {
                        ans = (ans + dp[i + 1][(((m - ex * cif) % d) + d) % d][0]) % M;
                        if (i > 0) {
                            ans = (ans + dp[i + 1][(((m - ex * cif) % d) + d) % d][1]) % M;
                        }
                    }
                }
            }
        }
    }
    return ans;
}

int check(string a) {
    long long m = 0;
    for (int i = 0; i < a.size(); i++) {
        long long c = a[i] - '0';
        m = (m * 10 + c) % d;
        if ((i + 1) % 2 == 1 && c == k) {
            return 0;
        }
        if ((i + 1) % 2 == 0 && c != k) {
            return 0;
        }
    }
    if (m != 0) {
        return 0;
    }
    return 1;

}

int main() {
    IOS;
    cin >> d >> k;
    string a, b;
    cin >> a >> b;
    cout << (calc(b) - calc(a) + check(a) + M) % M << endl;

    return 0;
}
