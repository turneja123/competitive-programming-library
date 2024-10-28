//https://codeforces.com/contest/2035/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

bool b[N];

void solve(int n) {
    int x = 31 - __builtin_clz(n), ct = (1 << (x + 1)) - 1;
    int need = ct ^ n;
    int y = (1 << x) - 1;
    if (y == need) {
        solve(n - 2);
        cout << n - 1 << " " << n << " ";
        return;
    }
    b[need] = true, b[n] = true, b[y] = true;
    for (int i = 1; i <= n; i++) {
        if (!b[i]) {
            cout << i << " ";
        }
    }
    cout << y << " " << need << " " << n << " ";
    b[need] = false, b[n] = false, b[y] = false;
    return;
}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        if (n == 5) {
            cout << 5 << endl;
            cout << "2 1 3 4 5" << endl;
            continue;
        }
        if (n % 2 == 0) {
            int x = 31 - __builtin_clz(n), ct = (1 << (x + 1)) - 1;
            cout << ct << endl;
            solve(n);
            cout << endl;
        } else {
            cout << n << endl;
            solve(n - 1);
            cout << n << endl;
        }
    }
    return 0;
}

