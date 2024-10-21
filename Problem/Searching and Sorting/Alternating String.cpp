//https://codeforces.com/contest/2008/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int pref[2][26][N];
int suf[2][26][N];

int ct[2][26];
int mx[2];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        string s;
        cin >> s;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < 26; j++) {
                pref[0][j][i] = ((i == 0) ? 0 : pref[0][j][i - 1]);
                pref[1][j][i] = ((i == 0) ? 0 : pref[1][j][i - 1]);
            }
            pref[i % 2][s[i] - 'a'][i]++;
        }
        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j < 26; j++) {
                suf[0][j][i] = ((i == n - 1) ? 0 : suf[0][j][i + 1]);
                suf[1][j][i] = ((i == n - 1) ? 0 : suf[1][j][i + 1]);
            }
            suf[i % 2][s[i] - 'a'][i]++;
        }
        int ans = n;
        if (n % 2 == 0) {
            mx[0] = 0, mx[1] = 0;
            for (int j = 0; j < 26; j++) {
                mx[0] = max(mx[0], pref[0][j][n - 1]);
                mx[1] = max(mx[1], pref[1][j][n - 1]);
            }
            ans = n / 2 - mx[0] + n / 2 - mx[1];
            cout << ans << endl;
        } else {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < 26; j++) {
                    ct[0][j] = (((i == 0) ? 0 : pref[0][j][i - 1]) + ((i == n - 1) ? 0 : suf[1][j][i + 1]));
                    ct[1][j] = (((i == 0) ? 0 : pref[1][j][i - 1]) + ((i == n - 1) ? 0 : suf[0][j][i + 1]));
                }
                mx[0] = 0, mx[1] = 0;
                for (int j = 0; j < 26; j++) {
                    mx[0] = max(mx[0], ct[0][j]);
                    mx[1] = max(mx[1], ct[1][j]);
                }
                ans = min(ans, n / 2 - mx[0] + n / 2 - mx[1] + 1);
            }
            cout << ans << endl;
        }
    }
    return 0;
}
