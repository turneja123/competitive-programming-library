//https://www.codechef.com/START192A/problems/PRIOC
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 20;
const long long M = 998244353;

int a[N];

int table_mn[K][N];
int mn[K][N];
int moved[N];

long long dp[N][2];

void build(int n) {
    for (int i = 1; i <= n; i++) {
        table_mn[0][i] = a[i - 1];
        mn[0][i] = i - 1;
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            if (table_mn[k - 1][i] < table_mn[k - 1][i + (1 << (k - 1))]) {
                table_mn[k][i] = table_mn[k - 1][i];
                mn[k][i] = mn[k - 1][i];
            } else {
                table_mn[k][i] = table_mn[k - 1][i + (1 << (k - 1))];
                mn[k][i] = mn[k - 1][i + (1 << (k - 1))];
            }
        }
    }
    return;
}

int query(int l, int r) {
    l++, r++;
    int k = 31 - __builtin_clz(r - l + 1);
    int b;
    if (table_mn[k][l] < table_mn[k][r - (1 << k) + 1]) {
        b = mn[k][l];
    } else {
        b = mn[k][r - (1 << k) + 1];
    }

    return b;
}

long long calc(int l, int n, int f) {
    if (l == n) {
        return 1;
    }
    if (dp[l][f] != -1) {
        return dp[l][f];
    }
    dp[l][f] = 0;
    int mid = query(l, n - 1);
    if (f == 1) {
        dp[l][f] = (dp[l][f] + calc(mid + 1, n, 1)) % M;
        dp[l][f] = (dp[l][f] + calc(mid + 1, n, 0) * (mid - l + 1)) % M;
    } else {
        dp[l][f] = (dp[l][f] + calc(mid + 1, n, 0) * (1 + (moved[mid] == 0))) % M;
    }
    return dp[l][f];
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            a[i]--;
            dp[i][0] = -1;
            dp[i][1] = -1;
        }
        build(n);
        int mn = n;
        for (int i = n - 1; i >= 0; i--) {
            moved[i] = 0;
            if (mn < a[i]) {
                moved[i] = 1;
            }
            if (i != n - 1 && moved[i + 1]) {
                moved[i] = 1;
            }
            mn = min(mn, a[i]);
        }
        cout << calc(0, n, 1) << endl;

    }
    return 0;
}
