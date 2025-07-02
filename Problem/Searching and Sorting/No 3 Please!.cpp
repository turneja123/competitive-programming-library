//https://www.codechef.com/problems/NO3P
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int pref[N][3];
int suf[N][3];

int sufval[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int sum = 0;
        for (int j = 0; j < 3; j++) {
            pref[0][j] = 0;
            suf[n - 1][j] = 0;
        }
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (i != 0) {
                for (int j = 0; j < 3; j++) {
                    pref[i][j] = pref[i - 1][j];
                }
            }
            sum = (sum + a[i]) % 3;
            pref[i][sum]++;
        }
        sum = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (i != n - 1) {
                for (int j = 0; j < 3; j++) {
                    suf[i][j] = suf[i + 1][j];
                }
            }
            sum = (sum + a[i]) % 3;
            sufval[i] = sum;
            suf[i][sum]++;
        }
        if (pref[n - 1][0] == 0) {
            cout << "Yes" << endl;
            continue;
        }
        string ans = "No";
        for (int i = 0; i < n; i++) {
            int x = pref[n - 1][0] - pref[i][0];
            int rem = (i == n - 1 ? 0 : sufval[i + 1]);
            int y = suf[0][rem] - (i == n - 1 ? 0 : suf[i + 1][rem]);
            if (x == 0 && y == 0) {
                ans = "Yes";
            }
        }
        cout << ans << endl;
    }
    return 0;
}
