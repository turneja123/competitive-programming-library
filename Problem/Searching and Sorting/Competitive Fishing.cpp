//https://codeforces.com/contest/2042/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

long long a[N];
long long pref[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        string s;
        cin >> s;
        long long sum = 0;
        for (int i = 0; i < n; i++) {
            sum += (s[i] == '1' ? 1 : -1);
            a[i] = sum;
        }
        sort(a, a + n - 1);
        for (int i = 0; i < n - 1; i++) {
            pref[i] = (i == 0 ? a[i] : pref[i - 1] + a[i]);
        }
        int ans = -1;
        for (int i = n; i > 0; i--) {
            long long cur = sum * (i - 1) - (i == 1 ? 0 : pref[i - 2]);
            if (cur >= k) {
                ans = i;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
