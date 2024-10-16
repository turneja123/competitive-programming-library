//https://codeforces.com/contest/1966/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a, a + n);
        int last = 0, turn = 0, i = 0;
        while (i < n) {
            if (a[i] == last) {
                i++;
                continue;
            }
            if (a[i] - last > 1) {
                break;
            }
            last = a[i];
            i++;
            turn ^= 1;
        }
        if (i == n) {
            turn ^= 1;
        }
        if (turn == 0) {
            cout << "Alice" << endl;
        } else {
            cout << "Bob" << endl;
        }
    }
    return 0;
}
