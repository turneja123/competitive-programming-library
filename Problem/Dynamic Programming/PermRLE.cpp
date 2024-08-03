//https://www.spoj.com/problems/GCJ08RND2PD/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

typedef long long ll;

const int K = 17;
const int INF = 1e9;

int cost[K][K];
int cost_connect[K][K];

int dp[K][1 << K];

vector<int> masks[K];

int calc(int f, int k) {
    for (int b = 2; b <= k; b++) {
        for (int i = 0; i < k; i++) {
            if (i == f) {
                continue;
            }
            for (int j : masks[b]) {
                int c = j & (1 << i);
                if (c) {
                    for (int l = 0; l < k; l++) {
                        if (dp[l][j ^ (1 << i)] != INF) {
                            dp[i][j] = min(dp[i][j], dp[l][j ^ (1 << i)] + cost[l][i]);
                        }
                    }
                }
            }
        }
    }
    int ans = INF;
    for (int i = 0; i < k; i++) {
        ans = min(ans, dp[i][(1 << k) - 1] + cost_connect[i][f]);
    }
    return ans;
}

int main(){
	IOS;
	int t;
	cin >> t;
	for (int tt = 1; tt <= t; tt++) {
        int k; string s;
        cin >> k >> s;
        int n = s.size();
        for (int i = 0; i < n; i += k) {
            for (int j = i; j < i + k; j++) {
                for (int p = j + 1; p < i + k; p++) {
                    if (s[j] != s[p]) {
                        cost[j - i][p - i]++;
                        cost[p - i][j - i]++;
                    }
                }
            }
            if (i + k != n) {
                for (int j = i; j < i + k; j++) {
                    for (int p = i; p < i + k; p++) {
                        if (s[j] == s[p + k]) {
                            cost_connect[j - i][p - i]--;
                        }
                    }
                }
            }
        }
        int ans = INF;
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < 1 << k; j++) {
                int c = j & (1 << i);
                if (!c) {
                    continue;
                }
                masks[__builtin_popcount(j)].push_back(j);
            }

            for (int l = 0; l < k; l++) {
                for (int j = 0; j < 1 << k; j++) {
                    dp[l][j] = INF;
                }
            }
            dp[i][1 << i] = n / k;
            ans = min(ans, calc(i, k));
            for (int j = 0; j <= k; j++) {
                masks[j].clear();
            }
        }
        cout << "Case #" << tt << ": " << ans << endl;
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < k; j++) {
                cost[i][j] = 0;
                cost_connect[i][j] = 0;
            }
        }
	}

	return 0;
}
