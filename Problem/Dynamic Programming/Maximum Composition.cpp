//https://atcoder.jp/contests/abc366/tasks/abc366_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 15;

pair<int, int> a[N];
long long dp[N][K];

bool comp(pair<int, int> a, pair<int, int> b) {
    int x = (a.first + a.second) * b.first + b.second;
    int y = (b.first + b.second) * a.first + a.second;
    return x > y;
}

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i].first >> a[i].second;
    }
    sort(a, a + n, comp);
    dp[0][0] = 1;
    dp[0][1] = a[0].first + a[0].second;
    for (int i = 1; i < n; i++) {
        dp[i][0] = 1;
        for (int j = 1; j <= k; j++) {
            dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - 1] * a[i].first + a[i].second);
        }
    }
    cout << dp[n - 1][k];
    return 0;
}
