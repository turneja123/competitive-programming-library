//https://codeforces.com/contest/1497/problem/C2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

void solve_3(int n) {
    if (n % 2 == 1) {
        cout << n / 2 << " " << n / 2 << " " << 1 << endl;
    } else {
        int x = n / 2;
        if (x % 2 == 1) {
            x--;
            cout << x << " " << x << " " << 2 << endl;
        } else {
            cout << x << " " << x / 2 << " " << x / 2 << endl;
        }
    }

}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        while (k > 3) {
            cout << 1 << " ";
            n--, k--;
        }
        solve_3(n);
    }

    return 0;
}
