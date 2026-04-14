//https://codeforces.com/contest/2219/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5005;

char a[N][N], b[N][N], c[N][N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                a[i][j] = (i + j >= n - 1 && (i - j) % 3 != 0) || (i + j == n - 1);
                b[i][j] = 0;
                c[i][j] = 0;
            }
        }
        for (int i = 1; i < n - 1; i++) {
            int j = n - 1 - i;
            if (a[i][j] ^ a[i + 1][j] ^ a[i][j + 1]) {
                if (i < j) {
                    b[i][j + 1] ^= 1;
                } else {
                    c[i + 1][j] ^= 1;
                }
            }
        }
        for (int j = 0; j + 1 < n; j++) {
            for (int i = 0; i < n; i++) {
                if (b[i][j]) {
                    b[i][j + 1] ^= 1;
                    if (i > 0) {
                        b[i - 1][j + 1] ^= 1;
                    }
                }
            }
        }
        for (int i = 0; i + 1 < n; i++) {
            for (int j = 0; j < n; j++) {
                if (c[i][j]) {
                    c[i + 1][j] ^= 1;
                    if (j > 0) {
                        c[i + 1][j - 1] ^= 1;
                    }
                }
            }
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int ans = a[i][j] ^ b[i][j] ^ c[i][j];

                cout << ans << " ";
            }
            cout << endl;
        }
    }
    return 0;
}
