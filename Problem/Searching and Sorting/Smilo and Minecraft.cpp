//https://codeforces.com/contest/2113/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;

int a[N][N];
int pref[N][N];
string s[N];

void preprocess(int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            pref[i][j] = a[i][j] + (i > 0 ? pref[i - 1][j] : 0) + (j > 0 ? pref[i][j - 1] : 0) - (i > 0 && j > 0 ? pref[i - 1][j - 1] : 0);
        }
    }
    return;
}

int query(int x1, int y1, int x2, int y2) {
    int ans = pref[x2][y2] - (x1 > 0 ? pref[x1 - 1][y2] : 0) - (y1 > 0 ? pref[x2][y1 - 1] : 0) + (x1 > 0 && y1 > 0 ? pref[x1 - 1][y1 - 1] : 0);
    return ans;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        int ct = 0;
        for (int i = 0; i < n; i++) {
            cin >> s[i];
            for (int j = 0; j < m; j++) {
                if (s[i][j] == 'g') {
                    a[i][j] = 1;
                    ct++;
                } else {
                    a[i][j] = 0;
                }
            }
        }
        preprocess(n, m);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                if (s[i][j] == '.') {
                    ans = max(ans, ct - query(max(0, i - k + 1), max(0, j - k + 1), min(n - 1, i + k - 1), min(m - 1, j + k - 1)));
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
