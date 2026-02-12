//https://tlx.toki.id/contests/troc-43/problems/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    string a;
    cin >> a;
    ll ans = 0;
    int s = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == '0') {
            s++;
        } else {
            s--;
        }
        if (s != 0) {
            ans += k;
        }
    }
    if (s == 0) {
        cout << ans;
        return 0;
    }
    if (s > 0) {
        for (int i = 0; i < n; i++) {
            if (a[i] == '0') {
                a[i] = '1';
            } else {
                a[i] = '0';
            }
        }
        s *= -1;
    }
    ans = 0;
    int cur = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == '0') {
            cur++;
        } else {
            cur--;
        }
        if (cur > 0) {
            int l = 1, r = k, spl = 1;
            while (l <= r) {
                int mid = (l + r) / 2;
                ll ct = cur + (ll)(mid - 1) * s;
                if (ct > 0) {
                    spl = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            ans += spl;
        }
        if (cur < 0) {
            int rem = s - cur;
            if (rem > 0) {
                int l = 1, r = k, spl = k;
                while (l <= r) {
                    int mid = (l + r) / 2;
                    ll ct = rem + (ll)(k - mid) * s;
                    if (ct > 0) {
                        spl = mid;
                        r = mid - 1;
                    } else {
                        l = mid + 1;
                    }
                }
                ans += k - spl + 1;
            }
        }
    }
    cout << ans;

    return 0;
}
