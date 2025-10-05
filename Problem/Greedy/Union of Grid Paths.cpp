//https://atcoder.jp/contests/arc197/tasks/arc197_a
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
        int n, m;
        cin >> n >> m;
        string s;
        cin >> s;
        ll ans = 1;
        int l = 0, r = 0, sufn = 0, sufm = 0;
        for (int i = 0; i < n + m - 2; i++) {
            if (s[i] == 'D') {
                sufn++;
            }
            if (s[i] == 'R') {
                sufm++;
            }
        }
        for (int i = 0; i < n + m - 2; i++) {
            if (s[i] == 'D') {
                l++;
                r++;
                sufn--;
            }
            if (s[i] == 'R') {
                sufm--;
            }
            if (s[i] == '?') {
                r++;
            }
            //r + sufn <= n - 1;
            int R = min(r, n - 1 - sufn);
            // i + 1 - l + sufm <= m - 1
            int L = max(l, sufm + i + 1 - m + 1);
            ans += R - L + 1;
        }
        cout << ans << endl;
    }
    return 0;
}
