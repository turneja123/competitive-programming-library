//https://www.spoj.com/problems/AVOIDSOS/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int M = 1e9 + 7;

int a[8][8];
int dp[1 << 16];
int dp_nx[1 << 16];

int seen[1 << 16];

int masks[1 << 16];
int masks_nx[1 << 16];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            for (int j = 0; j < m; j++) {
                if (s[j] == 'O') {
                    a[i][j] = 0;
                } else if (s[j] == 'S') {
                    a[i][j] = 1;
                } else {
                    a[i][j] = 2;
                }
            }
        }
        int b = 2 * n;
        dp[0] = 1;

        int ptr = 0;
        masks[ptr++] = 0;

        for (int k = 1; k <= n * m; k++) {
            int i = (k - 1) % n;
            int j = (k - 1) / n;
            int ptr_nx = 0;
            for (int x = 0; x < ptr; x++) {
                int t = masks[x];
                int mask = t << 1, L = 0;
                if (mask >= 1 << b) {
                    mask -= 1 << b;
                    L = 1;
                }
                if (a[i][j] == 2 || a[i][j] == 0) {
                    dp_nx[mask] += dp[t];
                    if (dp_nx[mask] >= M) {
                        dp_nx[mask] -= M;
                    }
                    if (!seen[mask]) {
                        seen[mask] = 1;
                        masks_nx[ptr_nx++] = mask;
                    }
                }
                if (a[i][j] == 2 || a[i][j] == 1) {
                    int ok = 1;
                    if (i >= 2) {
                        int l = mask & 4, r = mask & 2;
                        if (l && !r) {
                            ok = 0;
                        }
                    }
                    int l = L;
                    int r = mask & (1 << n);
                    if (l && !r) {
                        ok = 0;
                    }
                    if (ok) {
                        dp_nx[mask + 1] += dp[t];
                        if (dp_nx[mask + 1] >= M) {
                            dp_nx[mask + 1] -= M;
                        }
                        if (!seen[mask + 1]) {
                            seen[mask + 1] = 1;
                            masks_nx[ptr_nx++] = mask + 1;
                        }
                    }
                }
            }
            for (int x = 0; x < ptr; x++) {
                int t = masks[x];
                dp[t] = 0;
            }
            for (int x = 0; x < ptr_nx; x++) {
                int t = masks_nx[x];
                masks[x] = masks_nx[x];
                dp[t] = dp_nx[t];
                dp_nx[t] = 0;
                seen[t] = 0;
            }
            ptr = ptr_nx;
        }
        int ans = 0;
        for (int x = 0; x < ptr; x++) {
            int t = masks[x];
            ans += dp[t];
            if (ans >= M) {
                ans -= M;
            }
            dp[t] = 0;
        }
        cout << ans << endl;

    }
    return 0;
}
