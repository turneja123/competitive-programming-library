//https://atcoder.jp/contests/abc374/tasks/abc374_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 105;

long long a[N], p[N], b[N], q[N];

int main() {
    IOS;
    int n; long long x;
    cin >> n >> x;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> p[i] >> b[i] >> q[i];
    }
    long long l = 0, r = 1e10, ans = 0;
    while (l <= r) {
        long long mid = (l + r) / 2;
        long long cost = 0;
        for (int i = 0; i < n; i++) {
            long long cur = 1e15;
            if (a[i] >= mid) {
                cur = min({cur, p[i], (mid / b[i]) * q[i] + ((mid % b[i]) ? q[i] : 0)});
            } else if (b[i] >= mid) {
                cur = min({cur, q[i], (mid / a[i]) * p[i] + ((mid % a[i]) ? p[i] : 0)});
            } else {
                cur = min({cur, (mid / a[i]) * p[i] + ((mid % a[i]) ? p[i] : 0), (mid / b[i]) * q[i] + ((mid % b[i]) ? q[i] : 0)});
                long long tmp = mid;
                for (int j = 0; j < 20000; j++) {
                    long long lf = mid % a[i];
                    cur = min({cur, (mid / a[i]) * p[i] + (lf / b[i]) * q[i] + ((lf % b[i]) ? q[i] : 0) + p[i] * j});
                    mid -= a[i];
                    if (mid <= 0) {
                        break;
                    }
                }
                mid = tmp;
                for (int j = 0; j < 20000; j++) {
                    long long lf = mid % a[i];
                    cur = min({cur, (mid / a[i]) * p[i] + (lf / b[i]) * q[i] + ((lf % b[i]) ? q[i] : 0) + q[i] * j});
                    mid -= b[i];
                    if (mid <= 0) {
                        break;
                    }
                }
                mid = tmp;
                for (int j = 0; j < 20000; j++) {
                    long long rt = mid % b[i];
                    cur = min({cur, (mid / b[i]) * q[i] + (rt / a[i]) * p[i] + ((rt % a[i]) ? p[i] : 0) + p[i] * j});
                    mid -= a[i];
                    if (mid <= 0) {
                        break;
                    }
                }
                mid = tmp;
                for (int j = 0; j < 20000; j++) {
                    long long rt = mid % b[i];
                    cur = min({cur, (mid / b[i]) * q[i] + (rt / a[i]) * p[i] + ((rt % a[i]) ? p[i] : 0) + q[i] * j});
                    mid -= b[i];
                    if (mid <= 0) {
                        break;
                    }
                }
                mid = tmp;
            }
            cost += cur;
            if (cost > x) {
                break;
            }
        }
        if (cost <= x) {
            ans = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << ans;
    return 0;

}
