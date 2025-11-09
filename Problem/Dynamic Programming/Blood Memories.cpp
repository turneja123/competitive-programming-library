//https://qoj.ac/contest/2567/problem/14707
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 6;
const ll INF = 1e18;

int A[N];
int B[N];

ll tmp[1<<N][1<<N];
ll ans[1<<N][1<<N];
ll dp[1<<N][1<<N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m, k, r;
        cin >> n >> m >> k >> r;
        for (int i = 0; i < n; i++) {
            cin >> A[i] >> B[i];
        }
        for (int i = 0; i < 1 << n; i++) {
            for (int j = 0; j < 1 << n; j++) {
                tmp[i][j] = -INF;
                if (i == j) {
                    ans[i][j] = 0;
                } else {
                    ans[i][j] = -INF;
                }
                int cost = 0, gain = 0;
                for (int b = 0; b < n; b++) {
                    int ci = i & (1 << b), cj = j & (1 << b);
                    if (cj) {
                        gain += A[b];
                        cost += B[b];
                        if (ci) {
                            cost += k;
                        }
                    }
                }
                if (cost <= m) {
                    dp[i][j] = gain;
                } else {
                    dp[i][j] = -INF;
                }
            }
        }
        for (int e = 0; e < 30; e++) {
            int bt = 1 << e;
            if (bt > r) {
                break;
            }
            int c = r & (1 << e);
            if (c) {
                for (int i = 0; i < 1 << n; i++) {
                    for (int j = 0; j < 1 << n; j++) {
                        for (int k = 0; k < 1 << n; k++) {
                            tmp[i][j] = max(tmp[i][j], ans[i][k] + dp[k][j]);
                        }
                    }
                }
                for (int i = 0; i < 1 << n; i++) {
                    for (int j = 0; j < 1 << n; j++) {
                        ans[i][j] = tmp[i][j];
                        tmp[i][j] = -INF;
                    }
                }
            }
            for (int i = 0; i < 1 << n; i++) {
                for (int j = 0; j < 1 << n; j++) {
                    for (int k = 0; k < 1 << n; k++) {
                        tmp[i][j] = max(tmp[i][j], dp[i][k] + dp[k][j]);
                    }
                }
            }
            for (int i = 0; i < 1 << n; i++) {
                for (int j = 0; j < 1 << n; j++) {
                    dp[i][j] = tmp[i][j];
                    tmp[i][j] = -INF;
                }
            }
        }
        ll best = -INF;
        for (int i = 0; i < 1 << n; i++) {
            best = max(best, ans[0][i]);
        }
        cout << best << endl;


    }
    return 0;
}
