//https://basecamp.eolymp.com/en/problems/12229
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5005;
const int M = 315;

int pw[N];
int dp[N][M];
tuple<int, int, int> go[N][M];

bool calc(int i, int m, int n, string &s) {
    if (i == n) {
        return m == 0;
    }
    if (dp[i][m] != -1) {
        return dp[i][m];
    }
    dp[i][m] = 0;
    if (s[i] == '?') {
        for (int d = 0; d < 10; d++) {
            if (i == 0 && d == 0) {
                continue;
            }
            if (calc(i + 1, (m + pw[n - i - 1] * d) % M, n, s)) {
                go[i][m] = {i + 1, (m + pw[n - i - 1] * d) % M, d};
                dp[i][m] = 1;
                break;
            }
        }
    } else {
        int d = s[i] - '0';
        if (calc(i + 1, (m + pw[n - i - 1] * d) % M, n, s)) {
            go[i][m] = {i + 1, (m + pw[n - i - 1] * d) % M, d};
            dp[i][m] = 1;
        }
    }
    return dp[i][m];
}

int main() {
    IOS;
    pw[0] = 1;
    for (int i = 1; i < N; i++) {
        pw[i] = pw[i - 1] * 10 % M;
    }
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int n = s.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < M; j++) {
                dp[i][j] = -1;
            }
        }
        if (calc(0, 0, n, s) == 0) {
            cout << -1 << endl;
        } else {
            int i = 0, m = 0;
            while (i < n) {
                auto [ni, nm, d] = go[i][m];
                cout << d;
                i = ni;
                m = nm;
            }
            cout << endl;
        }
    }

    return 0;
}
