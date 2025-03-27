//https://www.spoj.com/problems/BLBONO/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

int dp[512];
int f[3][3];

int calc(int mask) {
    if (dp[mask] != -1) {
        return dp[mask];
    }
    for (int i = 0; i < 9; i++) {
        int c = (1 << i) & mask;
        if (c) {
            f[i / 3][i % 3] = 1;
        } else {
            f[i / 3][i % 3] = 0;
        }
    }
    for (int i = 0; i < 3; i++) {
        if (f[i][0] && f[i][1] && f[i][2]) {
            return dp[mask] = 0;
        }
        if (f[0][i] && f[1][i] && f[2][i]) {
            return dp[mask] = 0;
        }
    }
    if (f[0][0] && f[1][1] && f[2][2]) {
        return dp[mask] = 0;
    }
    if (f[0][2] && f[1][1] && f[2][0]) {
        return dp[mask] = 0;
    }
    set<int> mex;
    for (int i = 0; i < 9; i++) {
        int c = (1 << i) & mask;
        if (!c) {
            mex.insert(calc(mask + (1 << i)));
        }
    }
    int ct = 0;
    for (auto x : mex) {
        if (ct != x) {
            return dp[mask] = ct;
        }
        ct++;
    }
    return dp[mask] = ct;
}

int main() {
    IOS;
    for (int i = 0; i < 512; i++) {
        dp[i] = -1;
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            int mask = 0;
            for (int j = 0; j < 9; j++) {
                if (s[j] == '1') {
                    mask += 1 << j;
                }
            }
            if (dp[mask] == -1) {
                calc(mask);
            }
            ans ^= dp[mask];
        }
        if (ans) {
            cout << "Kang" << endl;
        } else {
            cout << "Kung" << endl;
        }
    }


    return 0;
}
