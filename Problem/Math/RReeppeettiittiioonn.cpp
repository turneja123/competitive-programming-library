//https://codeforces.com/contest/2215/problem/B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int d[100];

int main() {
    IOS;
    for (int i = 1; i < 100; i++) {
        for (int j = i; j < 100; j += i) {
            d[j]++;
        }
    }
    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        int ans = 0;
        ll s = sqrtl(n);
        for (int i = 2; i <= s; i++) {
            int g = 0, sz = 0, last = -1;
            ll t = n;
            while (t > 0) {
                int cur = t % i;
                if (last != cur) {
                    g = (g == 0 ? sz : __gcd(g, sz));
                    sz = 1;
                    last = cur;
                } else {
                    sz++;
                }
                t /= i;
            }
            g = (g == 0 ? sz : __gcd(g, sz));
            ans += d[g] - 1;
        }
        for (int i = 1; i <= s + 1; i++) {
            if (n % i != 0) {
                continue;
            }
            ll j = n / i;
            if (i < j - 1 && j > s) {
                ans++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
