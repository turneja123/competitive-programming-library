//https://codeforces.com/contest/2056/problem/C
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
        int n;
        cin >> n;
        if (n == 6) {
            cout << "1 1 2 3 1 2" << endl;
            continue;
        }
        int x = (n - 2) / 2;
        int j = 3;
        if (n % 2 == 1) {
            j++;
        }
        for (int i = 0; i < x; i++) {
            cout << j + i << " ";
        }
        cout << "1 2" << " ";
        if (n % 2 == 1) {
            cout << 3 << " ";
        }
        for (int i = 0; i < x; i++) {
            cout << j + i << " ";
        }
        cout << endl;
    }
    return 0;
}
