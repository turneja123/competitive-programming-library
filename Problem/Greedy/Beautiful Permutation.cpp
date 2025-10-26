//https://codeforces.com/contest/2162/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

//#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int s1, s2;
        cout << "1 " << 1 << " " << n << endl;
        cin >> s1;
        cout << "2 " << 1 << " " << n << endl;
        cin >> s2;
        int d = s2 - s1;
        int l = 1, r = n, st = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            cout << "1 " << 1 << " " << mid << endl;
            cin >> s1;
            cout << "2 " << 1 << " " << mid << endl;
            cin >> s2;
            if (s1 != s2) {
                r = mid - 1;
            } else {
                st = mid;
                l = mid + 1;
            }
        }
        st++;
        cout << "! " << st << " " << st + d - 1 << endl;
    }

  return 0;
}
