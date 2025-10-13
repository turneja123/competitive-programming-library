//https://atcoder.jp/contests/arc208/tasks/arc208_b
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
        int n, k;
        cin >> n >> k;
        int st;
        if (n < 31) {
            int p = 1;
            for (int i = 1; i < n; i++) {
                p *= 2;
            }
            st = min(k, p - 1);
        } else {
            st = k;
        }
        ll last = (k + st - 1) / st + 1;
        cout << last << " ";
        for (int i = 1; i < n; i++) {
            ll cur = last + min((ll)k, last - 1);
            cout << cur << " ";
            k -= cur - last;
            last = cur;
        }
        cout << endl;
    }


    return 0;
}
