//https://codeforces.com/contest/2062/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

long long a[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        long long ans = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            ans += a[i];
        }
        int m = n;
        for (int j = 0; j < m - 1; j++) {
            if (a[0] > a[n - 1]) {
                reverse(a, a + n);
            }
            long long cur = 0;
            for (int i = 0; i < n - 1; i++) {
                a[i] = a[i + 1] - a[i];
                cur += a[i];
            }
            ans = max(ans, cur);
            n--;
        }
        cout << ans << endl;
    }

    return 0;
}
