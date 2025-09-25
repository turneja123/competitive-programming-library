//https://codeforces.com/contest/1260/problem/C
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
        int a, b, k;
        cin >> a >> b >> k;
        int g = __gcd(a, b);
        a /= g, b /= g;
        if (a > b) {
            swap(a, b);
        }
        int need = (b - 1) / a + 1;
        if ((b - 1) % a == 0) {
            need--;
        }
        if (k > need) {
            cout << "OBEY" << endl;
        } else {
            cout << "REBEL" << endl;
        }
    }


    return 0;
}
