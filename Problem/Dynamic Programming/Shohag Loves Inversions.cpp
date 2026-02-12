//https://codeforces.com/contest/2039/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const ll M = 998244353;

ll dp[N];
ll s[N];

int main() {
    IOS;
    ll add = 0;
    dp[2] = M - 1;
    dp[3] = 0;
    for (int i = 4; i < N - 1; i++) {
        dp[i] = ((i - 1) * dp[i - 1] + add + i - 2) % M;
        s[i] = (s[i - 1] + dp[i - 1] + 1) % M;
        add = (add + (i - 1) * dp[i - 1] + i - 2) % M;
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << (dp[n] + s[n] + 2) % M << endl;
    }

    return 0;
}
