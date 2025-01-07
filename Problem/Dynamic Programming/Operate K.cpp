//https://atcoder.jp/contests/abc386/tasks/abc386_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 5e5 + 5;

bitset<25> dp[N][45];

string a, b;

int n, m;

void calc(int i, int j, int k) {
    if (abs(i - j) > 20 || k > 20) {
        return;
    }
    if (abs(n - i - (m - j)) + k > 20) {
        return;
    }
    if (dp[i][i - j + 20][k]) {
        return;
    }
    dp[i][i - j + 20][k] = true;
    if (i == n && j == m) {
        return;
    }
    if (i < n && j < m ) {
        calc(i + 1, j + 1, k + (a[i] != b[j]));
    }
    if (j < m) {
        calc(i, j + 1, k + 1);
    }
    if (i < n) {
        calc(i + 1, j, k + 1);
    }
    return;
}

int main() {
    IOS;
    int k;
    cin >> k >> a >> b;
    n = a.size(), m = b.size();
    if (abs(n - m) > k) {
        cout << "No";
        return 0;
    }
    calc(0, 0, 0);
    string ans = "No";
    for (int i = 0; i <= k; i++) {
        if (dp[n][n - m + 20][i]) {
            ans = "Yes";
        }
    }
    cout << ans;
    return 0;
}
