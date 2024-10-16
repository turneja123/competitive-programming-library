//https://codeforces.com/contest/2021/problem/B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int x[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a, a + n);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] > ans) {
                while (ans < a[i]) {
                    if (x[ans % k] == 0) {
                        break;
                    } else {
                        x[ans % k]--;
                        ans++;
                    }
                }
                if (ans < a[i]) {
                    break;
                }
                ans++;
            } else if (a[i] == ans) {
                ans++;
            } else {
                if (k <= n) {
                    x[a[i] % k]++;
                }
            }
        }
        while (x[ans % k] > 0) {
            x[ans % k]--;
            ans++;
        }
        cout << ans << endl;
        for (int i = 0; i <= n; i++) {
            x[i] = 0;
        }

    }

    return 0;
}
