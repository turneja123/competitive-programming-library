//https://codeforces.com/contest/2152/problem/B
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
        int n, rk, ck, rd, cd;
        cin >> n >> rk >> ck >> rd >> cd;
        if (rk > rd) {
            rk = n - rk; rd = n - rd;
        }
        if (ck > cd) {
            ck = n - ck; cd = n - cd;
        }
        int ans;
        if (rk == rd) {
            ans = cd;
        } else if (ck == cd) {
            ans = rd;
        } else {
            ans = max(rd, cd);
        }
        cout << ans << endl;
    }
    return 0;
}
}
