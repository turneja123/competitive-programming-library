//https://cses.fi/problemset/task/3413
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3005;

int a[N][N];
int sz_row[N][N];
int sz_col[N][N];
int last[26];
ll ans[26];

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < n; j++) {
            a[i][j] = s[j] - 'A';
        }
        int last = 0;
        for (int j = 1; j < n; j++) {
            if (a[i][j] != a[i][last]) {
                for (int l = last; l < j; l++) {
                    sz_row[i][l] = l - last + 1;
                }
                last = j;
            }
        }
        for (int l = last; l < n; l++) {
            sz_row[i][l] = l - last + 1;
        }
    }
    for (int j = 0; j < n; j++) {
        int last = 0;
        for (int i = 0; i < n; i++) {
            if (a[i][j] != a[last][j]) {
                for (int l = last; l < i; l++) {
                    sz_col[l][j] = l - last + 1;
                }
                last = i;
            }
        }
        for (int l = last; l < n; l++) {
            sz_col[l][j] = l - last + 1;
        }
    }
    vector<pair<int, int>> diag;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == 0 || j == 0) {
                diag.push_back({i, j});
            }
        }
    }
    for (auto [x, y] : diag) {
        for (int t = 0; t < k; t++) {
            last[t] = -1;
        }
        for (int i = 0; x + i < n && y + i < n; i++) {
            int c = a[x + i][y + i];
            if (i == 0 || a[x + i - 1][y + i - 1] != c) {
                last[c] = i;
            } else {
                last[c] = max(last[c], i - min(sz_col[x + i][y + i], sz_row[x + i][y + i]) + 1);
            }
            ans[c] += i - last[c] + 1;
        }
    }
    for (int i = 0; i < k; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}
