//https://codeforces.com/contest/2276/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int INF = 1e9;

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n), vis(n, 0);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            a[i]--;
        }
        int mn = n;
        vector<int> sizes;
        for (int i = 0; i < n; i++) {
            int u = a[i];
            if (!vis[u]) {
                int sz = 0;
                while (1) {
                    vis[u] = 1;
                    sz++;
                    if (u == i) {
                        break;
                    }
                    u = a[u];
                }
                mn = min(sz, mn);
                sizes.push_back(sz);
            }
        }
        if (mn > k) {
            cout << "Bob" << endl;
            continue;
        }
        sort(sizes.begin(), sizes.end());
        reverse(sizes.begin(), sizes.end());
        int m = sizes.size();
        if (k == 1) {
            if (sizes[0] >= 3) {
                cout << "Bob" << endl;
            } else if (sizes[0] == 1 || n % 2 == 1) {
                cout << "Alice" << endl;
            } else {
                cout << "Bob" << endl;
            }
            continue;
        }
        if (sizes[0] > k + 1) {
            cout << "Bob" << endl;
            continue;
        }
        if (sizes[0] == k + 1) {
            if (m > 1 && sizes[1] == k + 1) {
                cout << "Bob" << endl;
                continue;
            }
            int must = 0, ones = 0;
            for (int i = 1; i < m; i++) {
                if (sizes[i] == 1) {
                    ones++;
                } else {
                    must += sizes[i];
                }
            }
            int first = must + ones % (k + 1);
            if (first >= 1 && first <= k) {
                cout << "Alice" << endl;
            } else {
                cout << "Bob" << endl;
            }
            continue;
        }

        vector<vector<vector<int>>> dp(m, vector<vector<int>>(k + 1, vector<int>(k + 1, INF)));

        dp[0][1][0] = sizes[0] - 1;
        if (sizes[0] <= k) {
            dp[0][0][sizes[0]] = 0;
        }
        int ans = INF;
        for (int i = 1; i < m; i++) {
            for (int j = 0; j <= k; j++) {
                for (int z = 0; z <= k; z++) {
                    if (dp[i - 1][j][z] == INF) {
                        continue;
                    }
                    if (j == k) {
                        ans = min(ans, dp[i - 1][j][z]);
                    } else {
                        dp[i][j + 1][z] = min(dp[i][j + 1][z], dp[i - 1][j][z] + sizes[i] - 1);
                    }
                    if (z + sizes[i] <= k) {
                        dp[i][j][z + sizes[i]] = min(dp[i][j][z + sizes[i]], dp[i - 1][j][z]);
                    }
                }
            }
        }
        for (int j = 0; j <= k; j++) {
            for (int z = 0; z <= k; z++) {
                ans = min(ans, dp[m - 1][j][z]);
            }
        }
        if (ans <= k) {
            cout << "Alice" << endl;
        } else {
            cout << "Bob" << endl;
        }
    }
    return 0;
}
