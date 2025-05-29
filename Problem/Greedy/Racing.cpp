//https://codeforces.com/contest/2110/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int l[N], r[N];
int ans[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        int cur = 0, can = 1;
        for (int i = 0; i < n; i++) {
            if (a[i] == 1) {
                cur++;
            }
            cin >> l[i] >> r[i];
            r[i] -= cur;
            l[i] -= cur;
            if (r[i] < 0) {
                can = 0;
            }
        }
        for (int i = n - 2; i >= 0; i--) {
            r[i] = min(r[i], r[i + 1]);
        }
        cur = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] == -1) {
                if (cur < r[i]) {
                    cur++;
                    ans[i] = 1;
                } else {
                    ans[i] = 0;
                }
            } else {
                ans[i] = a[i];
            }
            if (cur < l[i]) {
                can = 0;
            }
        }
        if (!can) {
            cout << -1 << endl;
        } else {
            for (int i = 0; i < n; i++) {
                cout << ans[i] << " ";
            }
            cout << endl;
        }
    }

    return 0;
}
