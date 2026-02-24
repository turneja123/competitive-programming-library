//https://evaluator.hsin.hr/events/coci26_5/tasks/HONI252655tezina/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    IOS;
    int m, k;
    cin >> m >> k;
    ll ans = 0;
    for (int i = 0; i < m; i++) {
        int n;
        cin >> n;
        for (int l = 1; l <= n;) {
            int q = n / l, r = n / q;
            r = min(r, k);
            ans += min((ll)1e8, (ll)q * (n + 2)) * (r - l + 1);
            l = r + 1;
            if (l > k) {
                break;
            }
        }
    }
    cout << ans;

    return 0;
}
