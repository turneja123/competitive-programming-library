//https://codeforces.com/contest/2055/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;

long long a[N][N];
long long row[N], col[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        string s;
        cin >> s;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> a[i][j];
                row[i] += a[i][j];
                col[j] += a[i][j];
            }
        }
        long long x = 0;
        int i = 0, j = 0;
        for (int k = 0; k < s.size(); k++) {
            if (s[k] == 'D') {
                i++;
            } else {
                j++;
            }
            if (i == n - 1) {
                a[n - 1][m - 1] = -col[m - 1];
                col[m - 1] = 0;
                row[n - 1] += a[n - 1][m - 1];
                break;
            }
            if (j == m - 1) {
                a[n - 1][m - 1] = -row[n - 1];
                row[n - 1] = 0;
                col[m - 1] += a[n - 1][m - 1];
                break;
            }
        }
        i = 0, j = 0;
        for (int k = 0; k < s.size(); k++) {
            if (s[k] == 'D') {
                a[i][j] = x - row[i];
                col[j] += a[i][j];
                i++;

            } else {
                a[i][j] = x - col[j];
                row[i] += a[i][j];
                j++;
            }
        }
        for (int i = 0; i < n; i++) {
            row[i] = 0;
            for (int j = 0; j < m; j++) {
                cout << a[i][j] << " ";
                col[j] = 0;
            }
            cout << endl;
        }
    }
    return 0;

}
