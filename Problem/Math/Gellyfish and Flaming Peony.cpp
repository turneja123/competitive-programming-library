//https://codeforces.com/contest/2115/problem/A
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5005;

int a[N];
int dp[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int g = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            g = (g == 0 ? a[i] : __gcd(g, a[i]));
        }
        for (int i = 0; i < n; i++) {
            a[i] /= g;
        }
        for (int i = 0; i < N; i++) {
            dp[i] = N;
        }
        int ct = 0, p = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] == 1) {
                ct++;
            }
            for (int j = i + 1; j < n; j++) {
                if (__gcd(a[i], a[j]) == 1) {
                    p = 1;
                }
            }
            dp[a[i]] = 0;
            for (int j = 1; j < N; j++) {
                if (dp[j] != N) {
                    int g = __gcd(a[i], j);
                    dp[g] = min(dp[g], dp[j] + 1);
                }
            }
        }
        if (ct > 0) {
            cout << n - ct << endl;
        } else if (p == 1) {
            cout << n << endl;
        } else {
            cout << n + dp[1] - 1 << endl;
        }
    }

    return 0;
}
