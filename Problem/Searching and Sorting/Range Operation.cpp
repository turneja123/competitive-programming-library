//https://codeforces.com/contest/2169/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const ll INF = 1e18;

int a[N];
ll pref[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        ll best = -INF, ans = -INF;
        for (int i = 1; i <= n; i++) {
            best = max(best, (ll)-i * i + i + pref[i - 1]);
            cin >> a[i];
            pref[i] = pref[i - 1] + a[i];
            ans = max(ans, best + (ll)i * i + i - pref[i]);
        }
        cout << ans + pref[n] << endl;
    }


    return 0;
}
