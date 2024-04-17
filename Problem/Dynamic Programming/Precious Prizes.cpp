//https://www.spoj.com/problems/PRIZES/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 105;
const int K = 2005;

int dp[N][K];
int best[N][K];
pair<int, int> a[N];

int main() {
	IOS;
	int t;
	cin >> t;
	for (int c = 1; c <= t; c++) {
        int n, k;
        cin >> k >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i].first >> a[i].second;
        }
        for (int i = 0; i <= n; i++) {
            for (int j = 0; j <= k; j++) {
                dp[i][j] = -1;
                best[i][j] = 0;
            }
        }
        dp[0][0] = 0;
        int ans = 0; int ind = 0, wt = 0;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= k; j++) {
                if (dp[i - 1][j] != -1 && dp[i - 1][j] > dp[i][j]) {
                    dp[i][j] = dp[i - 1][j];
                    best[i][j] = best[i - 1][j];
                }
            }
            for (int j = 1; j <= k; j++) {
                if (j - a[i].first >= 0 && dp[i - 1][j - a[i].first] != -1 && dp[i - 1][j - a[i].first] + a[i].second > dp[i][j]) {
                    dp[i][j] = dp[i - 1][j - a[i].first] + a[i].second;
                    best[i][j] = i;
                    if (dp[i][j] > ans) {
                        ans = dp[i][j];
                        ind = i;
                        wt = j;
                    } else if (dp[i][j] == ans && wt > j) {
                        ind = i;
                        wt = j;
                    }
                }
            }
        }
        vector<int> v;
        while (ind != 0) {
            v.push_back(ind);
            wt = wt - a[ind].first;
            ind = best[ind - 1][wt];
        }
        cout << "Case " << c << ": " << endl;
        if (v.size() == 0) {
            cout << 0 << endl;
        }
        for (int i = v.size() - 1; i >= 0; i--) {
            cout << v[i] << endl;
        }


	}

	return 0;
}
