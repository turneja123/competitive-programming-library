//https://codeforces.com/contest/2162/problem/G
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        if (n == 2) {
            cout << -1 << endl;
        } else if (n == 3) {
            cout << "1 3" << endl << "2 3" << endl;
        } else if (n == 4) {
            cout << "1 2" << endl << "1 3" << endl << "1 4" << endl;
        } else if (n == 5) {
            cout << "3 1" << endl << "3 2" << endl << "3 4" << endl << "3 5" << endl;
        } else {
            ll d = (ll)n * (n + 1) / 2 - 1;
            int a = -1, b = -1;
            for (int i = 2; i <= n && a == -1; i++) {
                for (int j = 2; j <= n; j++) {
                    if (i == j) {
                        continue;
                    }
                    ll x = d - j + (ll)i * j;
                    ll s = sqrtl(x);
                    if (s * s == x) {
                        a = i, b = j;
                        break;
                    }
                }
            }
            cout << a << " " << b << endl;
            for (int i = 2; i <= n; i++) {
                if (i != b) {
                    cout << 1 << " " << i << endl;
                }
            }
        }
    }


    return 0;
}
