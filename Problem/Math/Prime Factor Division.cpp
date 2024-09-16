//https://www.codechef.com/problems/PRIMEFACDIV
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        long long a, b;
        cin >> a >> b;
        a %= b; long long tmp = a;
        for (int i = 0; i < 60; i++) {
            a = ((__int128)a * tmp) % b;
        }
        if (a == 0) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }

    }

    return 0;
}
