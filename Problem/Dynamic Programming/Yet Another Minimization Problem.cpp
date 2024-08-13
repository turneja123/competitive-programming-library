//https://codeforces.com/contest/868/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int K = 21;
const long long INF = 1e18;

long long a[N];
long long dp[N][K];

int ct[N];

long long cost = 0;

void calc(int l, int r, int optl, int optr, int j) {
    int mid = (l + r) / 2;
    long long best = INF; int opt = -1;
    for (int i = optl; i <= min(mid, optr); i++) {
        long long cur = ((i == 0) ? 0 : dp[i - 1][j - 1]) + cost;
        if (best > cur) {
            best = cur;
            opt = i;
        }
        ct[a[i]]--;
        cost -= ct[a[i]];
    }
    dp[mid][j] = best;
    for (int i = optl; i <= min(mid, optr); i++) {
        cost += ct[a[i]];
        ct[a[i]]++;
    }
    int ln = (l + mid - 1) / 2, rn = (mid + 1 + r) / 2;
    if (l <= mid - 1) {
        for (int i = max(ln + 1, optl); i <= mid; i++) {
            ct[a[i]]--;
            cost -= ct[a[i]];
        }
        calc(l, mid - 1, optl, opt, j);
        for (int i = max(ln + 1, optl); i <= mid; i++) {
            cost += ct[a[i]];
            ct[a[i]]++;
        }
    }
    if (mid + 1 <= r) {
        for (int i = optl; i < opt; i++) {
            ct[a[i]]--;
            cost -= ct[a[i]];
        }
        for (int i = mid + 1; i <= rn; i++) {
            cost += ct[a[i]];
            ct[a[i]]++;
        }
        calc(mid + 1, r, opt, optr, j);
        for (int i = optl; i < opt; i++) {
            cost += ct[a[i]];
            ct[a[i]]++;
        }
        for (int i = mid + 1; i <= rn; i++) {
            ct[a[i]]--;
            cost -= ct[a[i]];
        }
    }
}

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cost += ct[a[i]];
        dp[i][0] = cost;
        ct[a[i]]++;
    }
    for (int j = 1; j < k; j++) {
        for (int i = 0; i < n; i++) {
            ct[a[i]] = 0;
        }
        cost = 0;
        for (int i = 0; i <= (n - 1) / 2; i++) {
            cost += ct[a[i]];
            ct[a[i]]++;
        }
        calc(0, n - 1, 0, n - 1, j);
    }
    cout << dp[n - 1][k - 1];
    return 0;
}
