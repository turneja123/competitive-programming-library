//https://www.spoj.com/problems/UCBINTI/
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
    vector<int> a(n);

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int mn = n, ans = 0, take = 0;
    for (int i = 0; i < k; i++) {
        int x = 0, y = 0;
        for (int j = i; j < n; j += k) {
            if (a[j] % 2 == 0) {
                x++;
            } else {
                y++;
            }
        }
        if (x >= y) {
            ans += y;
        } else {
            ans += x;
            take++;
        }
        mn = min(mn, abs(x - y));
    }
    if (take % 2) {
        ans += mn;
    }
    cout << ans;
    return 0;
}
