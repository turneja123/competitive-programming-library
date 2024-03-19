//https://atcoder.jp/contests/abc321/tasks/abc321_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long M = 998244353;
const int W = 5005;

vector<long long> dp;

int main() {
    IOS;
    int n; long long w, a; char c;
    cin >> n >> w >> c >> a;
    dp.resize(w + 1, 0);
    dp[0] = 1;
    dp[a] = 1;
    cout << dp[w] << endl;
    for (int i = 1; i < n; i++) {
        cin >> c >> a;
        if (c == '+') {
            for (int j = w; j >= 0; j--) {
                if (j >= a) {
                    dp[j] = (dp[j] + dp[j - a]) % M;
                }
            }
        } else {
            for (int j = 0; j <= w; j++) {
                if (j >= a) {
                    dp[j] = (dp[j] - dp[j - a] + M) % M;
                }
            }
        }
        cout << dp[w] << endl;
    }
    return 0;
}
