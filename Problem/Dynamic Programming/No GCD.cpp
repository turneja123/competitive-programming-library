//https://www.spoj.com/problems/NGCD/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 15;

vector<int> p{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47};

int f[1 << N];
int dp[1 << N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            ll a;
            cin >> a;
            int mask = 0;
            for (int j = 0; j < N; j++) {
                if (a % p[j] == 0) {
                    mask |= 1 << j;
                }
            }
            f[mask]++;
        }
        for (int i = 0; i < 1 << N; i++) {
            dp[i] = f[i];
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < 1 << N; j++) {
                int c = (1 << i) & j;
                if (c) {
                    dp[j] += dp[j ^ (1 << i)];
                }
            }
        }
        ll ans = 0;
        for (int i = 0; i < 1 << N; i++) {
            ans += (ll)f[i] * dp[((1 << N) - 1) ^ i];
        }
        for (int b = 0; b < N; b++) {
            for (int i = 0; i < 1 << N; i++) {
                dp[i] = 0;
            }
            for (int i = 0; i < 1 << N; i++) {
                int c = (1 << b) & i;
                if (c) {
                    dp[i ^ (1 << b)] = f[i];
                }
            }
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < 1 << N; j++) {
                    int c = (1 << i) & j;
                    if (c) {
                        dp[j] += dp[j ^ (1 << i)];
                    }
                }
            }
            for (int i = 0; i < 1 << N; i++) {
                int c = (1 << b) & i;
                if (c) {
                    ans += (ll)f[i] * dp[((1 << N) - 1) ^ i];
                }
            }
        }
        cout << ans << endl;
        for (int i = 0; i < 1 << N; i++) {
            f[i] = 0;
        }
    }

    return 0;
}
