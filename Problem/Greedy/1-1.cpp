//https://codeforces.com/contest/2207/problem/A
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
        string s;
        cin >> s;
        int r = 0, l = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '1') {
                r++;
            } else if (s[i] == '0' && i != 0 && s[i - 1] == '1' && i != n - 1 && s[i + 1] == '1') {
                s[i] = '1';
                r++;
            }
        }
        int ct = 0;
        for (int i = 0; i < n; i++) {
            if (s[i] == '0') {
                l += (ct == 0 ? 0 : (ct + 2) / 2);
                ct = 0;
            } else {
                ct++;
            }
        }
        l += (ct == 0 ? 0 : (ct + 2) / 2);
        cout << l << " " << r << endl;
    }


    return 0;
}
