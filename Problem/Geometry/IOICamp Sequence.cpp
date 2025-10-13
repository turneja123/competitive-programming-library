//https://www.spoj.com/problems/ICAMPSEQ/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const double INF = 1e12;

double a[4];
double mx[16];
double mn[16];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int j = 0; j < 16; j++) {
        mx[j] = -INF;
        mn[j] = INF;
    }
    double ans = 0;
    for (int t = 0; t < n; t++) {
        for (int i = 0; i < 4; i++) {
            cin >> a[i];
        }
        for (int j = 0; j < 16; j++) {
            double cur = 0;
            for (int i = 0; i < 4; i++) {
                int c = j & (1 << i);
                if (c == 0) {
                    cur -= a[i];
                } else {
                    cur += a[i];
                }
            }
            mx[j] = max(mx[j], cur);
            mn[j] = min(mn[j], cur);
        }
    }
    for (int j = 0; j < 16; j++) {
        ans = max(ans, mx[j] - mn[j]);
    }
    cout << fixed;
    cout << setprecision(3);
    cout << ans;
    return 0;
}
