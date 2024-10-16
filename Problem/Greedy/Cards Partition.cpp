//https://codeforces.com/contest/2019/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

long long a[N], pref[N];

int main() {
    IOS;
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        int n; long long k;
        cin >> n >> k;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a, a + n);
        for (int i = 0; i < n; i++) {
            pref[i] = ((i == 0) ? a[i] : pref[i - 1] + a[i]);
        }
        int ans = 1;
        long long sum = pref[n - 1];
        for (int i = 2; i <= n; i++) {
            long long need = (i - sum % i) % i;
            if (need > k) {
                continue;
            }
            long long goal = sum + need + ((k - need) / i) * i;
            long long max_uses = goal / i;
            if (max_uses >= a[n - 1]) {
                ans = i;
            }
        }
        cout << ans << endl;
    }

    return 0;
}
