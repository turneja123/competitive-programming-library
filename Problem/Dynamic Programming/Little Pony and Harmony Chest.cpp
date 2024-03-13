//https://codeforces.com/contest/454/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 101;
const int M = 60;
const int K = 1 << 17;
const int INF = 1e9;

vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59};
int ct = primes.size();

int a[N];
int b[N];
int prv[N][K];
int best[N][K];
int dp[N][K];

int calcmask(int x) {
    int mask = 0;
    for (int i = 0; i < primes.size(); i++) {
        if (x % primes[i] == 0) {
            mask += 1 << i;
        }
    }
    return mask;
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        for (int j = 0; j < (1 << ct); j++) {
            dp[i][j] = INF;
        }
    }
    if (n == 1) {
        cout << a[0];
        return 0;
    }
    for (int j = 1; j < M; j++) {
        int mask = calcmask(j);
        if (dp[0][mask] > abs(j - a[0])) {
            dp[0][mask] = abs(j - a[0]);
            best[0][mask] = j;
        }
    }
    int ans = INF, last = -1;
    for (int i = 1; i < n; i++) {
        ans = INF;
        for (int j = 1; j < M; j++) {
            int mask = calcmask(j);
            for (int k = 0; k < (1 << ct); k++) {
                int c = mask & k;
                if (dp[i - 1][k] == INF || c > 0) {
                    continue;
                }
                int newmask = mask | k;
                if (dp[i - 1][k] + abs(j - a[i]) < dp[i][newmask]) {
                    dp[i][newmask] = dp[i - 1][k] + abs(j - a[i]);
                    best[i][newmask] = j;
                    prv[i][newmask] = k;
                    if (dp[i][newmask] < ans) {
                        ans = dp[i][newmask];
                        last = newmask;
                    }
                }
            }
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        b[i] = best[i][last];
        last = prv[i][last];
    }
    for (int i = 0; i < n; i++) {
        cout << b[i] << " ";
    }

    return 0;
}
