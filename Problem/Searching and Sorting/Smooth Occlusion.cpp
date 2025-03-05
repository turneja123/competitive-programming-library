//https://atcoder.jp/contests/abc395/tasks/abc395_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long INF = 1e18;

pair<long long, long long> a[N];

int main() {
    IOS;
    int n, x;
    cin >> n >> x;
    long long l = 0, r = INF, best = 0;
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
        r = min(r, a[i].first + a[i].second);
        ans += a[i].first + a[i].second;
    }
    while (l <= r) {
        long long mid = (l + r) / 2;
        long long lf = max(0LL, mid - a[0].second), rt = a[0].first;
        for (int i = 1; i < n; i++) {
            if (lf > rt) {
                break;
            }
            long long L = max(0LL, mid - a[i].second), R = a[i].first;
            lf -= x, rt += x;
            long long curl = max(L, lf), curr = min(R, rt);
            lf = curl, rt = curr;
        }
        if (lf <= rt) {
            best = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    cout << ans - best * n;


    return 0;
}
