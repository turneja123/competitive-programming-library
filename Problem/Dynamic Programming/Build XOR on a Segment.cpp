//https://codeforces.com/contest/2170/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const int K = 12;

int dp[K + 1][1 << K];
int dp_nx[K + 1][1 << K];
int a[N];
int ans[N];
vector<tuple<int, int, int>> queries[N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int l, r, x;
        cin >> l >> r >> x;
        queries[r].push_back(make_tuple(l, x, i));
    }
    for (int i = 1; i <= n; i++) {
        dp[0][0] = i;
        dp[1][a[i]] = i;
        for (int d = K; d > 0; d--) {
            for (int j = 0; j < 1 << K; j++) {
                dp[d][j] = max(dp[d][j], dp[d - 1][j ^ a[i]]);
            }
        }
        for (auto [l, x, j] : queries[i]) {
            ans[j] = 0;
            for (int d = 1; d <= K; d++) {
                if (dp[d][x] >= l) {
                    ans[j] = d;
                    break;
                }
            }
        }
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << " ";
    }




    return 0;
}
