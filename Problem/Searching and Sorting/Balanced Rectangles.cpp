//https://atcoder.jp/contests/abc410/tasks/abc410_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

int freq[2 * N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        int _n = n, _m = m;
        int f = 0;
        if (m > n) {
            swap(n, m);
            f = 1;
        }
        vector<vector<int>> a(n, vector<int>(m, 0));
        vector<vector<int>> pref(n, vector<int>(m, 0));
        for (int i = 0; i < _n; i++) {
            string s;
            cin >> s;
            for (int j = 0; j < _m; j++) {
                if (f == 0) {
                    if (s[j] == '#') {
                        a[i][j] = 1;
                    } else {
                        a[i][j] = -1;
                    }
                } else {
                    if (s[j] == '#') {
                        a[j][i] = 1;
                    } else {
                        a[j][i] = -1;
                    }
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                pref[i][j] = (j == 0 ? 0 : pref[i][j - 1]) + a[i][j];
            }
        }
        long long ans = 0;
        for (int j = 0; j < m; j++) {
            for (int k = j; k < m; k++) {
                int s = 0;
                freq[s + N]++;
                for (int i = 0; i < n; i++) {
                    s += pref[i][k] - (j == 0 ? 0 : pref[i][j - 1]);
                    ans += freq[s + N];
                    freq[s + N]++;
                }
                s = 0;
                freq[s + N] = 0;
                for (int i = 0; i < n; i++) {
                    s += pref[i][k] - (j == 0 ? 0 : pref[i][j - 1]);
                    freq[s + N] = 0;
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
