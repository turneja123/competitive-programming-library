//https://codeforces.com/contest/1991/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 100;

int a[N];
int pref[N];
int suf[N];

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    vector<int> x(n);
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        int m = r - l + 1;
        if (m > 90) {
            cout << "YES" << endl;
            continue;
        }
        for (int j = l; j <= r; j++) {
            a[j - l] = x[j];
        }
        sort(a, a + m);
        for (int i = 2; i < m; i++) {
            if (a[i - 2] + a[i - 1] > a[i]) {
                pref[i] = 1;
            }
            pref[i] |= pref[i - 1];
        }
        for (int i = m - 3; i >= 0; i--) {
            if (a[i] + a[i + 1] > a[i + 2]) {
                suf[i] = 1;
            }
            suf[i] |= suf[i + 1];
        }
        string ans = "NO";
        for (int i = 2; i < m; i++) {
            if (a[i - 2] + a[i - 1] > a[i]) {
                int ok = (i == 2 ? 0 : pref[i - 3]) || (i == m - 1 ? 0 : suf[i + 1]);
                if (i - 3 >= 0 && i + 2 < m && a[i - 3] + a[i + 1] > a[i + 2]) {
                    ok = 1;
                }
                if (i - 4 >= 0 && i + 1 < m && a[i - 4] + a[i - 3] > a[i + 1]) {
                    ok = 1;
                }
                if (ok) {
                    ans = "YES";
                }
            }
        }
        for (int i = 5; i < m; i++) {
            if (a[i - 5] + a[i - 4] > a[i - 2] && a[i - 3] + a[i - 1] > a[i]) {
                ans = "YES";
            }
            if (a[i - 5] + a[i - 4] > a[i - 1] && a[i - 3] + a[i - 2] > a[i]) {
                ans = "YES";
            }
            if (a[i - 5] + a[i - 3] > a[i - 2] && a[i - 4] + a[i - 1] > a[i]) {
                ans = "YES";
            }
            if (a[i - 5] + a[i - 3] > a[i - 1] && a[i - 4] + a[i - 2] > a[i]) {
                ans = "YES";
            }
            if (a[i - 5] + a[i - 3] > a[i] && a[i - 4] + a[i - 2] > a[i - 1]) {
                ans = "YES";
            }
            if (a[i - 5] + a[i - 2] > a[i - 1] && a[i - 4] + a[i - 3] > a[i]) {
                ans = "YES";
            }
            if (a[i - 5] + a[i - 2] > a[i] && a[i - 4] + a[i - 3] > a[i - 1]) {
                ans = "YES";
            }
        }
        for (int i = 0; i < m; i++) {
            pref[i] = 0;
            suf[i] = 0;
        }
        cout << ans << endl;
    }
    return 0;
}
