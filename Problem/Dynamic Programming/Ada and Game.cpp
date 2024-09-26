//https://www.spoj.com/problems/ADAGAME/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 30000;
const int M = 105;

string dp[N][M][2];

char inc(char c) {
    if (c == '9') {
        return '0';
    }
    return c + 1;
}

char dec(char c) {
    if (c == '0') {
        return '9';
    }
    return c - 1;
}

string calc(string s, int m, int flag) {
    if (m == 0) {
        return s;
    }
    int ind = (s[0] - '0' + 1) * 1000 + (s[1] - '0' + 1) * 100 + (s[2] - '0' + 1) * 10 + (s[3] - '0' + 1);
    if (dp[ind][m][flag] != "-1") {
        return dp[ind][m][flag];
    }
    if (flag == 1) {
        string ans = "0000";
        for (int i = 0; i < 4; i++) {
            s[i] = inc(s[i]);
            ans = max(ans, calc(s, m - 1, 0));
            s[i] = dec(s[i]);
        }
        return dp[ind][m][flag] = ans;
    } else {
        string ans = "9999";
        for (int i = 0; i < 4; i++) {
            s[i] = inc(s[i]);
            ans = min(ans, calc(s, m - 1, 1));
            s[i] = dec(s[i]);
        }
        return dp[ind][m][flag] = ans;
    }
}

int main() {
    IOS;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            dp[i][j][0] = "-1";
            dp[i][j][1] = "-1";
        }
    }
    int t;
    cin >> t;
    while (t--) {
        string a; int m;
        cin >> a >> m;
        string ans = calc(a, m, 1);
        if (ans > a) {
            cout << "Ada" << endl;
        } else {
            cout << "Vinit" << endl;
        }
    }
    return 0;
}
