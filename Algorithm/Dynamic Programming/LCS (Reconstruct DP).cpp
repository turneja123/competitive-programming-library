//https://atcoder.jp/contests/dp/tasks/dp_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3005;

string a, b;

int dp[N][N];
pair<int, int> go[N][N];

int calc(int i, int j, int n, int m) {
    if (i == n || j == m) {
        return 0;
    }
    if (dp[i][j] != -1) {
        return dp[i][j];
    }
    if (a[i] == b[j]) {
        go[i][j] = make_pair(i + 1, j + 1);
        return dp[i][j] = calc(i + 1, j + 1, n, m) + 1;
    }
    int l = calc(i + 1, j, n, m), r = calc(i, j + 1, n, m);
    if (l > r) {
        go[i][j] = make_pair(i + 1, j);
        return dp[i][j] = l;
    }
    go[i][j] = make_pair(i, j + 1);
    return dp[i][j] = r;

}

int main() {
    IOS;
    cin >> a >> b;
    int n = a.size(), m = b.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            dp[i][j] = -1;
        }
    }
    calc(0, 0, n, m);
    string ans = "";
    int i = 0, j = 0;
    while (i < n && j < m) {
        auto [x, y] = go[i][j];
        if (x == i + 1 && y == j + 1) {
            ans += a[i];
        }
        i = x, j = y;
    }
    cout << ans;
    return 0;
}
