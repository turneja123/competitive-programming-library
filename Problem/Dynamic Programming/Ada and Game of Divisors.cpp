//https://www.spoj.com/problems/ADAGAME4/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e7 + 1;

int spf[N];
int dp[2][N];
int d[N];
bool is_prime[N];

typedef long long ll;

void sieve(int n){
    dp[0][0] = 1, dp[1][0] = 0;
    for (int i = 1; i < n; i++) {
        spf[i] = i;
        is_prime[i] = true;
        d[i] = 1;
    }
    is_prime[1] = false;
    for (int i = 2; i < n; i++) {
        if (is_prime[i]) {
            d[i] = 2;
            for (int j = 2 * i; j < n; j += i) {
                is_prime[j] = false;
                spf[j] = min(spf[j], i);
                int t = j, e = 1;
                while (t % i == 0) {
                    t /= i;
                    e++;
                }
                d[j] *= e;
            }
        }
    }
}

int main() {
    IOS;
    sieve(N);
    int last0 = 0, last1 = 0;
    for (int n = 1; n < N; n++) {
        /*int mx = 0, mn = 1;
        for (int i = n - 1; i >= n - d[n]; i--) {
            mx = max(mx, dp[0][i]);
            mn = min(mn, dp[1][i]);
        }
        dp[0][n] = mn;
        dp[1][n] = mx;*/
        int l = last0, r = last1;
        if (last1 >= n - d[n]) {
            dp[1][n] = 1;
        } else {
            dp[1][n] = 0;
            l = n;
        }
        if (last0 >= n - d[n]) {
            dp[0][n] = 0;
        } else {
            dp[0][n] = 1;
            r = n;
        }
        last0 = l, last1 = r;
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int ans = dp[1][n];
        if (ans == 1) {
            cout << "Ada" << endl;
        } else {
            cout << "Vinit" << endl;
        }
    }
    return 0;
}
