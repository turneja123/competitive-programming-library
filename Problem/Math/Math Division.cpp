//https://codeforces.com/contest/2081/problem/A
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll M = 1e9 + 7;

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        ll p = 0, pw = (M + 1) / 2;
        for (int i = 1; i < n; i++) {
            if (s[i] == '1') {
                p = (p + pw) % M;
            }
            pw = pw * (M + 1) / 2 % M;
        }
        ll ans = (n * p + (n - 1) * (1 - p + M)) % M;
        cout << ans << endl;
    }
    return 0;
}
