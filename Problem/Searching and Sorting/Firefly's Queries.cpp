//https://codeforces.com/contest/2009/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;

int a[N];
long long pref[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < 2 * n; i++) {
            pref[i + 1] = pref[i] + a[i % n];
        }
        for (int i = 0; i < q; i++) {
            long long lq, rq;
            cin >> lq >> rq;
            lq--, rq--;
            long long L = lq / n, R = rq / n;
            long long l = lq % n, r = rq % n;
            if (L != R) {
                long long ans = pref[R + r + 1] - pref[R] + pref[L + n] - pref[L + l] + (R - L - 1) * pref[n];
                cout << ans << endl;
            } else {
                long long ans = pref[L + r + 1] - pref[L + l];
                cout << ans << endl;
            }
        }
    }

    return 0;
}
