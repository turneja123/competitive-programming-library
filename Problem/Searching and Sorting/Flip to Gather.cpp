//https://atcoder.jp/contests/abc408/tasks/abc408_d
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
        int ct = 0, sum = 0, ans = 0;
        for (int i = 0; i < n; i++) {
            if (sum < 0) {
                sum = (s[i] == '1') ? 1 : -1;
            } else {
                sum += (s[i] == '1') ? 1 : -1;
            }
            ct += s[i] == '1';
            ans = max(ans, sum);
        }
        cout << ct - ans << endl;
    }
    return 0;
}
