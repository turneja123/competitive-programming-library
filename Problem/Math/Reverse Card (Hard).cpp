//https://codeforces.com/contest/1972/problem/D2
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
        int a, b;
        cin >> a >> b;
        int ans = 0;
        for (int g = 1; g <= b; g++) {
            for (int i = g + 1; i <= b; i++) {
                long long l = (long long)i * g / __gcd(i, g);
                if (l > b) {
                    break;
                }
                for (int j = l; j <= b && (long long)(i - g) * j / g <= a; j += l) {
                    if (__gcd(i - g, g) == 1) {
                        ans++;
                    }
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
