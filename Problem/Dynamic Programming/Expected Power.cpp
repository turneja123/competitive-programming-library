//https://codeforces.com/contest/2020/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int MAX = 1024;
const int N = 2e5 + 5;
const long long M = 1e9 + 7;

int a[N];
int p[N];
long long dp[MAX];
long long dp_next[MAX];

int INV;

long long modPow(long long a, long long y) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
}

int main() {
    IOS;
    INV = modPow(10000, M - 2);
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
        }
        for (int i = 1; i <= n; i++) {
            cin >> p[i];
        }
        for (int j = 0; j < MAX; j++) {
            dp[j] = 0;
        }
        dp[0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < MAX; j++) {
                dp_next[j ^ a[i]] += INV * dp[j] % M * p[i];
                dp_next[j] += INV * dp[j] % M * (10000 - p[i]);
            }
            for (int j = 0; j < MAX; j++) {
                dp[j] = dp_next[j] % M;
                dp_next[j] = 0;
            }
        }
        long long ans = 0;
        for (int j = 0; j < MAX; j++) {
            ans += dp[j] * j % M * j;
        }
        cout << ans % M << endl;
    }

    return 0;
}
