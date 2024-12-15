//https://atcoder.jp/contests/abc237/tasks/abc237_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1005;
const int K = 10;
const long long M = 998244353;

int pw[K];

map<int, long long> dp[N];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    pw[0] = 1;
    for (int i = 1; i < m; i++) {
        pw[i] = pw[i - 1] * 4;
    }
    int mask = 0;
    for (int i = m - 1; i >= 0; i--) {
        mask += pw[i];
        dp[0][mask] = 1;
    }
    for (int i = 1; i < n; i++) {
        for (auto it = dp[i - 1].begin(); it != dp[i - 1].end(); ++it) {
            int mask = it->first;
            vector<int> d(m, 0);
            for (int j = 0; j < m; j++) {
                d[j] = mask % 4;
                mask /= 4;
            }

            for (int add = 0; add < m; add++) {
                int l = (add == 0 ? 0 : d[add - 1]);
                if (l + 1 > 3) {
                    continue;
                }
                long long cur = 0;
                for (int j = m - 1; j >= add; j--) {
                    cur += pw[j] * max(l + 1, d[j]);
                }
                for (int j = add - 1; j >= 0; j--) {
                    cur += pw[j] * d[j];
                }
                dp[i][cur] = (dp[i][cur] + it->second) % M;
            }
        }
    }
    long long ans = 0;
    for (auto it = dp[n - 1].begin(); it != dp[n - 1].end(); ++it) {
        int mask = it->first;
        int mx = 0;
        for (int j = 0; j < m; j++) {
            mx = max(mx, mask % 4);
            mask /= 4;
        }
        if (mx == 3) {
            ans = (ans + it->second) % M;
        }
    }
    cout << ans;
    return 0;
}

