//https://www.facebook.com/codingcompetitions/hacker-cup/2024/practice-round/problems/B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    IOS;
    freopen("248.in", "r", stdin);
    freopen("248.out", "w", stdout);
    cout << fixed;
    cout << setprecision(12);

    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        int n; long double p;
        cin >> n >> p;
        p /= 100.0;
        long double s = 1.0;
        for (int i = 0; i < n - 1; i++) {
            s *= p;
        }
        long double l = 0.0, r = 1.0, ans = 1.0;
        for (int k = 0; k < 200; k++) {
            long double mid = (l + r) * 0.5;
            long double cur = 1.0;
            for (int i = 0; i < n; i++) {
                cur *= mid;
            }
            if (cur >= s) {
                r = mid;
                ans = min(ans, mid);
            } else {
                l = mid;
            }
        }
        cout << "Case #" << tt << ": " << (long double)(ans - p) * 100.0 << endl;
    }
    return 0;
}
