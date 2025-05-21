//https://codeforces.com/contest/2067/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


int main() {
    IOS;
    vector<long long> v{9ll, 99ll, 999ll, 9999ll, 99999ll, 999999ll, 9999999ll, 99999999ll, 999999999ll, 9999999999ll};
    int t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;
        int ans = 8;
        for (int i = 0; i < v.size() - 1; i++) {
            for (int j = 0; j <= ans; j++) {
                for (int k = 0; k + j <= ans; k++) {
                    long long x = n + v[i] * j + v[i + 1] * k;
                    int yes = 0;
                    while (x > 0) {
                        if (x % 10 == 7) {
                            yes = 1;
                        }
                        x /= 10;
                    }
                    if (yes) {
                        ans = j + k;
                    }
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
