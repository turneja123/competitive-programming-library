//https://atcoder.jp/contests/arc194/tasks/arc194_a
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long INF = 1e18;

int a[N];
long long dp[N];
long long best[2];


int main() {
    IOS;
    long long sum = 0;
    best[0] = -INF, best[1] = 0;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum += a[i];
        dp[i] = max(sum, best[(i + 1) % 2] + a[i]);
        best[i % 2] = max(best[i % 2], dp[i]);
    }
    cout << best[(n + 1) % 2];

    return 0;
}
