//https://arena.petlja.org/sr-Latn-RS/competition/2024-2025-kv2-testiranje#tab_140266
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 3005;

int a[N];
int dp[N][N];

int calc(int l, int r, int m) {
    if (r - l + 1 < m) {
        return 0;
    }
    if (dp[l][r] != 0) {
        return dp[l][r];
    }
    int ans = 1e9;
    for (int i = 0; i < m; i++) {
        int lf = l + i, rt = r - (m - 1 - i);
        ans = min(ans, max(a[lf] + calc(lf + 1, rt, m), a[rt] + calc(lf, rt - 1, m)));
    }
    return dp[l][r] = ans;
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        int ans = 1e9;
        for (int l = 0; l <= i; l++) {
            int lf = l, rt = n - 1 - (i - l);
            ans = min(ans, max(a[lf] + calc(lf + 1, rt, m), a[rt] + calc(lf, rt - 1, m)));
        }
        cout << ans << " ";
    }

    return 0;
}
