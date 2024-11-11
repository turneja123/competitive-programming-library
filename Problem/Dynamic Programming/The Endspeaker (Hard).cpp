//https://codeforces.com/contest/2027/problem/D2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const long long INF = 1e18;
const long long M = 1e9 + 7;

long long a[N];
long long pref[N];
long long b[N];

map<long long, vector<pair<int, long long>>> prefcounts[N];

long long get_count(int j, int i, long long best) {
    auto it = prefcounts[j].find(best);
    if (it == prefcounts[j].end()) {
        return 0;
    }
    int x = lower_bound((it->second).begin(), (it->second).end(), make_pair(i, -1ll)) - (it->second).begin();
    if (x == (it->second).size()) {
        return 0;
    }
    return ((it->second)[it->second.size() - 1].second - (x == 0 ? 0 : (it->second)[x - 1].second) + M) % M;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            pref[i] = (i == 0 ? a[i] : pref[i - 1] + a[i]);
        }
        for (int i = 0; i < m; i++) {
            cin >> b[i];
        }
        vector<vector<pair<long long, long long>>> dp(n, vector<pair<long long, long long>>(m, make_pair(INF, 0)));
        vector<vector<pair<long long, long long>>> dp_pref(n, vector<pair<long long, long long>>(m, make_pair(INF, 0)));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                int l = 0, r = i, spl = -1;
                while (l <= r) {
                    int mid = (l + r) / 2;
                    long long sum = pref[i] - (mid == 0 ? 0 : pref[mid - 1]);
                    if (sum <= b[j]) {
                        r = mid - 1;
                        spl = mid;
                    } else {
                        l = mid + 1;
                    }
                }
                if (spl != -1) {
                    if (spl == 0) {
                        dp[i][j].first = m - j - 1;
                        dp[i][j].second = get_count(j, 0, 0) + 1;
                    } else if (dp_pref[spl - 1][j].first != INF) {
                        dp[i][j].first = dp_pref[spl - 1][j].first + m - j - 1;
                        dp[i][j].second = get_count(j, spl - 1, dp_pref[spl - 1][j].first);
                    }
                }
            }
            for (int j = 0; j < m; j++) {
                dp_pref[i][j].first = (j == 0 ? dp[i][j].first : min(dp_pref[i][j - 1].first, dp[i][j].first));
                dp_pref[i][j].second = (j == 0 ? dp[i][j].second : dp[i][j].first < dp_pref[i][j - 1].first ? dp[i][j].second : dp[i][j].first == dp_pref[i][j - 1].first ? (dp[i][j].second + dp_pref[i][j - 1].second) % M : dp_pref[i][j - 1].second);
            }
            for (int j = 0; j < m; j++) {
                auto it = prefcounts[j].find(dp_pref[i][j].first);
                if (it == prefcounts[j].end()) {
                    prefcounts[j][dp_pref[i][j].first] = vector<pair<int, long long>>{make_pair(i, dp_pref[i][j].second)};
                } else {
                    (it->second).push_back(make_pair(i, (dp_pref[i][j].second + (it->second)[it->second.size() - 1].second)));
                }
            }
        }
        for (int j = 0; j < m; j++) {
            prefcounts[j].clear();
        }
        if (dp_pref[n - 1][m - 1].first == INF) {
            cout << -1 << endl;
        } else {
            cout << dp_pref[n - 1][m - 1].first << " " << dp_pref[n - 1][m - 1].second << endl;
        }
    }
    return 0;
}
