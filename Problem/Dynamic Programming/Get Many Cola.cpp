//https://atcoder.jp/contests/abc415/tasks/abc415_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ld = long double;

const int N = 1e6 + 5;

int a[N], b[N];
int A[N], B[N];
int val[N];

ll dp[N];

int main() {
    IOS;
    ll n; int m;
    cin >> n >> m;
    ld best = 0;
    int j = 0;
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i];
        ld cur = (ld)b[i] / (ld)a[i];
        if (cur > best) {
            best = cur;
            j = i;
        }
        val[a[i]] = max(val[a[i]], b[i]);
    }
    long long add = 0;
    if (n > 100000) {
        long long l = 1, r = 1e15, spl;
        while (l <= r) {
            long long mid = (l + r) / 2;
            if (n - mid * (a[j] - b[j]) > 100000) {
                l = mid + 1;
            } else {
                spl = mid;
                r = mid - 1;
            }
        }
        add = spl * a[j];
        n -= spl * (a[j] - b[j]);
    }
    int k = 0;
    for (int i = 1; i <= 300; i++) {
        if (val[i] != 0) {
            A[k] = i;
            B[k] = val[i];
            k++;
        }
    }
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < k; j++) {
            if (i >= A[j]) {
                dp[i] = max(dp[i], B[j] + dp[i - (A[j] - B[j])]);
            }
        }
    }
    cout << add + n + dp[n];
    return 0;
}
