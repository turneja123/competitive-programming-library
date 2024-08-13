//https://www.spoj.com/problems/LARMY/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5005;
const long long INF = 1e18;

long long a[N];
long long val[N];
long long dp[N][N];
long long cost[N][N];

void calc(int l, int r, int optl, int optr, int j) {
    if (l > r) {
        return;
    }
    int mid = (l + r) / 2;
    long long best = INF; int opt = -1;
    for (int i = optl; i <= min(mid, optr); i++) {
        long long cur = ((i == 0) ? 0 : dp[i - 1][j - 1]) + cost[i][mid];
        if (best > cur) {
            best = cur;
            opt = i;
        }
    }
    dp[mid][j] = best;
    calc(l, mid - 1, optl, opt, j);
    calc(mid + 1, r, opt, optr, j);
}

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] > a[j]) {
                val[j]++;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        long long sum = 0;
        for (int j = i; j < n; j++) {
            sum += val[j];
            cost[i][j] = sum;
        }
        for (int j = i + 1; j < n; j++) {
            if (a[i] > a[j]) {
                val[j]--;
            }
        }
        dp[i][0] = cost[0][i];
    }
    for (int j = 1; j < k; j++) {
        calc(0, n - 1, 0, n - 1, j);
    }
    cout << dp[n - 1][k - 1];
    return 0;
}
