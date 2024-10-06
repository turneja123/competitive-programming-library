//https://atcoder.jp/contests/abc374/tasks/abc374_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 6;

pair<pair<long double, long double>, pair<long double, long double>> a[N];

long double dist(pair<long double, long double> a, pair<long double, long double> b) {
    long double d = sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
    return d;
}

long double calc(int n, int ct, int nx, int flag, vector<bool> &seen, pair<long double, long double> last, long double s, long double t) {
    long double start;
    if (flag == 0) {
        start = dist(last, a[nx].first) / s + dist(a[nx].second, a[nx].first) / t;
        last = a[nx].second;
    } else {
        start = dist(last, a[nx].second) / s + dist(a[nx].second, a[nx].first) / t;
        last = a[nx].first;
    }
    if (ct == n) {
        return start;
    }
    long double ans = 1e18;
    for (int i = 0; i < n; i++) {
        if (!seen[i]) {
            seen[i] = true;
            ans = min({ans, calc(n, ct + 1, i, 0, seen, last, s, t), calc(n, ct + 1, i, 1, seen, last, s, t)});
            seen[i] = false;
        }
    }
    return start + ans;
}

int main() {
    IOS;
    cout << fixed;
    cout << setprecision(12);
    int n; long double t, s;
    cin >> n >> s >> t;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first.first >> a[i].first.second >> a[i].second.first >> a[i].second.second;
    }
    long double ans = 1e18;
    for (int i = 0; i < n; i++) {
        vector<bool> seen(n, false);
        seen[i] = true;
        ans = min({ans, calc(n, 1, i, 0, seen, make_pair(0, 0), s, t), calc(n, 1, i, 1, seen, make_pair(0, 0), s, t)});
        seen[i] = false;
    }
    cout << ans;
    return 0;
}
