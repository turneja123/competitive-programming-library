//https://qoj.ac/contest/1452/problem/7941
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        n *= 2;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        ll ans = 0;
        for (int i = 0; i < n / 2; i++) {
            ans -= a[i];
        }
        for (int i = n / 2; i < n; i++) {
            ans += a[i];
        }
        cout << ans << endl;
    }

    return 0;
}
