//https://codeforces.com/contest/2043/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 1e5 + 5;
const int K = 65;
const long long M = 998244353;

int a[N];
int freq[N][K];
pair<int, int> dp[K][K];

pair<int, int> chmin(pair<int, int> x, pair<int, int> y, int f) {
    if (y.first + f < x.first) {
        return make_pair(y.first + f, y.second);
    }
    if (y.first + f == x.first) {
        return make_pair(x.first, (x.second + y.second) % M);
    }
    return x;
}

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        freq[i][a[i]]++;
        if (i != 0) {
            for (int j = 0; j < K; j++) {
                freq[i][j] += freq[i - 1][j];
            }
        }
    }
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        int y = freq[r][0] - (l == 0 ? 0 : freq[l - 1][0]);
        if (y > 0) {
            cout << r - l << " " << y << endl;
            continue;
        }
        bool can = false;
        long long ans = 0;
        for (int j = 1; j < K; j++) {
            int y = freq[r][j] - (l == 0 ? 0 : freq[l - 1][j]);
            if (y > 1) {
                can = true;
                ans = (ans + (long long)y * (y - 1) / 2) % M;
            }
        }
        if (can) {
            cout << r - l - 1 << " " << ans << endl;
            continue;
        }
        for (int j = 0; j < K; j++) {
            for (int k = 0; k < K; k++) {
                dp[j][k] = make_pair(K, -1);
            }
        }
        for (int j = 1; j < K; j++) {
            int f = freq[r][j] - (l == 0 ? 0 : freq[l - 1][j]);
            if (f == 1) {
                dp[j][j] = make_pair(1, 1);
            }
            for (int k = 0; k < K; k++) {
                if (dp[j - 1][k].first == K) {
                    continue;
                }
                dp[j][k] = chmin(dp[j][k], dp[j - 1][k], 0);
                if (f == 1) {
                    dp[j][k ^ j] = chmin(dp[j][k ^ j], dp[j - 1][k], 1);
                }
            }
        }
        if (dp[K - 1][0].second == -1) {
            cout << -1 << endl;
        } else {
            cout << r - l + 1 - dp[K - 1][0].first << " " << dp[K - 1][0].second << endl;
        }


    }
    return 0;
}
