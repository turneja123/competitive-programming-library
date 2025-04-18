//https://dmoj.ca/problem/rccc1s4
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5005;
const int INF = 1e9;

int dp[N][N];
int suf[N][N];

int a[N], b[N], c[N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
    }
    for (int j = 0; j < N; j++) {
        if (j * a[0] < c[0]) {
            dp[0][j] = INF;
        } else {
            dp[0][j] = j;
        }
    }
    suf[0][N - 1] = dp[0][N - 1];
    for (int j = N - 2; j >= 0; j--) {
        suf[0][j] = min(suf[0][j + 1], dp[0][j]);
    }

    for (int i = 1; i < n; i++) {
        int r = N - 1;
        for (int j = 0; j < N; j++) {
            while (r >= 0 && a[i] * j + b[i - 1] * r >= c[i]) {
                r--;
            }
            dp[i][j] = suf[i - 1][r + 1] + j;
        }
        suf[i][N - 1] = dp[i][N - 1];
        for (int j = N - 2; j >= 0; j--) {
            suf[i][j] = min(suf[i][j + 1], dp[i][j]);
        }
    }
    cout << suf[n - 1][0];

    return 0;
}
