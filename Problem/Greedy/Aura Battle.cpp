//https://codeforces.com/contest/2273/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

//#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 10000;

int main() {
    IOS;
    int best = N;
    int L, R;
    for (int l = 5; l <= N; l++) {
        break;
        for (int r = l + 5; r <= N; r++) {
            int cur = 0;
            int lf = 1, rt = N;

            while (lf <= rt) {
                int k = (lf + rt) / 2;
                vector<int> x{l - k, l + k, r - k, r + k};
                vector<int> ok{x[0] > 0, x[1] <= x[2], x[1] <= x[2], x[3] <= N};
                int s = accumulate(ok.begin(), ok.end(), 0);
                if (s <= 3) {
                    rt = k - 1;
                    continue;
                }
                int ans = 2 * k;
                cur = max(cur, ans);
                lf = k + 1;
            }
            lf = 1, rt = N;
            while (lf <= rt) {
                int k = (lf + rt) / 2;
                vector<int> x{l - k, l + k, r - k, r + k};
                vector<int> ok{x[0] > 0, x[1] <= x[2], x[1] <= x[2], x[3] <= N};
                int s = accumulate(ok.begin(), ok.end(), 0);
                if (s == 4) {
                    lf = k + 1;
                    continue;
                }
                if (s <= 2) {
                    rt = k - 1;
                    continue;
                }
                int ans = k + (x[2] - x[1]) / 2;
                cur = max(cur, ans);
                lf = k + 1;
            }


            lf = 1, rt = N;
            while (lf <= rt) {
                int k = (lf + rt) / 2;
                vector<int> x{l - k, l + k, r - k, r + k};
                vector<int> ok{x[0] > 0, x[1] <= x[2], x[1] <= x[2], x[3] <= N};
                int s = accumulate(ok.begin(), ok.end(), 0);
                if (s > 2) {
                    lf = k + 1;
                    continue;
                }
                if (s == 0) {
                    rt = k - 1;
                    continue;
                }
                int ans = k;
                cur = max(cur, ans);
                lf = k + 1;
            }
            if (cur < best) {
                best = cur;
                L = l, R = r;
            }
        }
        cout << l << " " << L << " " << R << " " << best << endl;
    }
    L = 1428, R = 7143;
    int LF = L, RT = R;
    int t;
    cin >> t;
    while (t--) {
        L = LF, R = RT;
        cout << L << " " << R << endl;
        int k;
        cin >> k;
        vector<int> x{L - k, L + k, R - k, R + k};
        vector<int> ok{x[0] > 0, x[1] <= x[2], x[1] <= x[2], x[3] <= N};
        int s = accumulate(ok.begin(), ok.end(), 0);
        if (s == 4) {
            cout << L + 1 << " " << R - 2 << endl;
            int k2;
            cin >> k2;
            if (k2 == k + 1) {
                L = L - k;
            } else if (k2 == k - 1) {
                L = L + k;
            } else if (k2 == k + 2) {
                R = R + k;
            } else {
                R = R - k;
            }
            for (int i = 0; i < 8; i++) {
                cout << L << " " << R << endl;
                cin >> k;
            }
        } else if (s == 3) {
            if (!ok[0]) {
                L = (x[1] + x[2]) / 2 - 1;
                R = x[3];
                cout << L  << " " << R << endl;
                int k2;
                cin >> k2;
                if (k2 == abs(x[1] - L)) {
                    L = x[1];
                } else {
                    L = x[2];
                }
                for (int i = 0; i < 8; i++) {
                    cout << L << " " << R << endl;
                    cin >> k;
                }
            } else {
                L = x[0];
                R = (x[1] + x[2]) / 2 + 1;
                cout << L  << " " << R << endl;
                int k2;
                cin >> k2;
                if (k2 == abs(x[2] - R)) {
                    R = x[2];
                } else {
                    R = x[1];
                }
                for (int i = 0; i < 8; i++) {
                    cout << L << " " << R << endl;
                    cin >> k;
                }
            }
        } else {
            L = -1, R = -1;
            for (int i = 0; i < 4; i++) {
                if (ok[i]) {
                    if (L == -1) {
                        L = x[i];
                    } else {
                        R = x[i];
                    }
                }
            }
            if (R == -1) {
                R = L;
            }
            for (int i = 0; i < 9; i++) {
                cout << L << " " << R << endl;
                cin >> k;
            }
        }
    }

    return 0;
}
