//https://codeforces.com/contest/2037/problem/G
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 1e6 + 5;
const long long M = 998244353;

int a[N];
long long ans[N];
long long dp[N];

bool composite[N];
vector<int> divs[N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 2; i < N; i++) {
        if (!composite[i]) {
            divs[i].push_back(i);
            for (int j = 2 * i; j < N; j += i) {
                composite[j] = true;
                divs[j].push_back(i);
            }
        }
    }
    int m = divs[a[0]].size();
    for (int j = 1; j < 1 << m; j++) {
        int prod = 1;
        for (int k = 0; k < m; k++) {
            int c = j & (1 << k);
            if (c) {
                prod *= divs[a[0]][k];
            }
        }
        dp[prod] = 1;
    }
    for (int i = 1; i < n; i++) {
        long long sum = 0;
        int m = divs[a[i]].size();
        for (int j = 1; j < 1 << m; j++) {
            int f = __builtin_popcount(j) % 2;
            if (f == 0) {
                f = -1;
            }
            int prod = 1;
            for (int k = 0; k < m; k++) {
                int c = j & (1 << k);
                if (c) {
                    prod *= divs[a[i]][k];
                }
            }
            sum = (sum + dp[prod] * f + M) % M;
        }
        for (int j = 1; j < 1 << m; j++) {
            int prod = 1;
            for (int k = 0; k < m; k++) {
                int c = j & (1 << k);
                if (c) {
                    prod *= divs[a[i]][k];
                }
            }
            dp[prod] = (dp[prod] + sum) % M;
        }
        ans[i] = sum;
    }

    cout << ans[n - 1];


    return 0;
}
