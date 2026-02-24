#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2005;

bitset<N> b[N];
ll row[N];
ll col[N];
ll row_sum_of_col[N][N];
ll col_sum_of_row[N][N];

void print(__int128 x) {
    if (x < 0) {
        putchar('-');
        x = -x;
    }
    if (x > 9) print(x / 10);
    putchar(x % 10 + '0');
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < m; j++) {
            if (s[j] == '1') {
                b[i][j] = 1;
                row[i]++;
                col[j]++;
            }
        }
    }
    __int128 ans = 0;
    for (int i = 0; i < n; i++) {
        ll s = 0;
        for (int j = 0; j < m; j++) {
            if (b[i][j]) {
                s += col[j] - 1;
            }
        }
        for (int j = 0; j < m; j++) {
            if (b[i][j]) {
                row_sum_of_col[i][j] = s - (col[j] - 1);
            }
        }
    }
    for (int j = 0; j < m; j++) {
        ll s = 0;
        for (int i = 0; i < n; i++) {
            if (b[i][j]) {
                s += row[i] - 1;
            }
        }
        for (int i = 0; i < n; i++) {
            if (b[i][j]) {
                col_sum_of_row[i][j] = s - (row[i] - 1);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            ans += row_sum_of_col[i][j] * col_sum_of_row[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int c = (b[i] & b[j]).count();
            ans -= (ll)c * (c - 1) / 2 * 4;
        }
    }
    ans *= 2;
    print(ans);

    return 0;
}
