//https://codeforces.com/contest/2135/problem/D2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

//#define endl "\n"
#define ll long long
//#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 10000;
const int W = 100000;

int main() {
    //IOS;
    int B;
    for (int b = 1; b < 150; b++) {
        int ival = 0, k = W / b;
        for (int i = 1; i <= 100000; i++) {
            int lk, rk;
            if (i == 1) {
                if (k < N) {
                    continue;
                }
                lk = N, rk = k;
            } else {
                lk = (N + i - 1) / i, rk = (N - 1) / (i - 1);
                if (lk > max(rk, k)) {
                    continue;
                }
                rk = min(rk, k);
            }

            int l = b * lk, r = b * rk + b - 1;
            r = min(r, W);

            ival = max(ival, 2 * (r - l + 1));
        }
        if (N + max(b * b, ival) < 25000) {
            B = b;
            break;
        }
    }
    int t;
    cin >> t;
    while (t--) {
        cout << "? " << N << " ";
        for (int i = 0; i < N; i++) {
            cout << B << " ";
        }
        cout << endl;
        int d;
        cin >> d;
        if (d == 0) {
            cout << "? " << B * B << " ";
            for (int i = 0; i < B * B; i++) {
                cout << "1 ";
            }
            cout << endl;
            cin >> d;
            int ans = (B * B + d - 1) / d;
            cout << "! " << ans << endl;
        } else {
            int k = W / B;
            int lk, rk;
            if (d == 1) {
                lk = N;
                rk = k;
            } else {
                lk = (N + d - 1) / d;
                rk = (N - 1) / (d - 1);
                rk = min(rk, k);
            }
            int l = B * lk, r = min(W, B * rk + B - 1);
            cout << "? " << 2 * (r - l + 1) << " ";
            for (int i = 1; i <= r - l + 1; i++) {
                cout << l << " " << i << " ";
            }
            cout << endl;
            int x;
            cin >> x;
            cout << "! " << l + 2 * (r - l + 1) - x << endl;
        }
    }

    return 0;
}
