//https://atcoder.jp/contests/abc389/tasks/abc389_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

long long a[N];

int main() {
    IOS;
    int n; long long m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    long long l = 1, r = 1e18;
    long long x, y, z;
    while (l <= r) {
        long long mid = (l + r) / 2;
        long long ct = 0, sum = 0;
        for (int i = 0; i < n && sum <= m; i++) {
            long long cur = (mid / a[i] + 1) / 2;
            ct += cur;
            __int128 add = (__int128)cur * cur * a[i];
            if (add > m) {
                sum = m + 1;
            } else {
                sum += add;
            }
        }
        if (sum <= m) {
            x = ct;
            y = mid;
            z = sum;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    m -= z;
    for (int i = 0; i < n; i++) {
        long long cur = (y / a[i] + 1) / 2;
        long long j = a[i] * (2 * cur + 1);
        if (j == y + 1 && m >= j) {
            x++;
            m -= y + 1;
        }
    }
    cout << x;

    return 0;
}
