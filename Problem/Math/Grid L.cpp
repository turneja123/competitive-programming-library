//https://codeforces.com/contest/2219/problem/A
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
        int p, q;
        cin >> p >> q;
        int n = -1, m = -1, ct = 2 * (p + 2 * q) + 1;


        for (int i = 3; i <= sqrt(ct); i += 2) {
            if (ct % i == 0) {
                int j = ct / i;
                if (j % 2 == 1 && j / 2 > 0 && abs(j / 2 - i / 2) - p <= 0) {
                    n = i / 2;
                    m = j / 2;
                    break;
                }
            }
        }
        cout << n << " ";
        if (m != -1) {
            cout << m << " ";
        }
        cout << endl;
    }
    return 0;
}
