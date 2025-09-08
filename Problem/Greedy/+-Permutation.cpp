//https://basecamp.eolymp.com/en/problems/12211
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int seen[N];

ll s(ll n) {
    if (n < 0) {
        return 0;
    }
    return n * (n + 1) / 2;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m; ll k;
        cin >> n >> m >> k;
        ll mx = s(n) - 2 * s(m);
        ll mn = s(n) - 2 * (s(n) - s(n - m));
        if (k < mn || k > mx) {
            cout << 0 << endl;
            continue;
        }
        if ((s(n) - k) % 2 == 1) {
            cout << 0 << endl;
            continue;
        }
        ll x = (s(n) - k) / 2;
        int last = n;
        vector<int> ans;
        for (int i = 1; i <= m; i++) {
            int l = 1, r = last, spl;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (s(m - i) > x - mid) {
                    r = mid - 1;
                } else {
                    l = mid + 1;
                    spl = mid;
                }
            }
            x-= spl;
            seen[spl] = true;
            last = spl - 1;
            ans.push_back(-spl);
        }
        for (int i = 1; i <= n; i++) {
            if (!seen[i]) {
                ans.push_back(i);
            }
            seen[i] = false;
        }
        for (int i = 0; i < n; i++) {
            cout << ans[i] << " ";
        }
        cout << endl;

    }
    return 0;
}
