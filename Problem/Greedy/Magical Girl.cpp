//https://tlx.toki.id/contests/troc-39/problems/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;
    int a = 0, b = 0, ans = 0;
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '0') {
            a++;
        } else {
            b++;
        }
        if (a > n) {
            a = 1;
            b = 0;
            ans++;
        }
        if (b > m) {
            b = 1;
            a = 0;
            ans++;
        }
    }
    cout << ans;


    return 0;
}
