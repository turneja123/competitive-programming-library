//https://www.spoj.com/problems/CPDUEL5A/
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
        long long n;
        cin >> n;
        string ans = "NO";
        for (long long e = 1; e <= n && ans == "NO"; e++) {
            if (n * e <= e * e * e + e + e * e * 2) {
                break;
            }
            if ((n * e - e * e * e - e - e * e * 2) % (e * 2 + 1 + e * e) == 0) {
                ans = "YES";
            }
        }
        cout << ans << endl;
    }

    return 0;
}
