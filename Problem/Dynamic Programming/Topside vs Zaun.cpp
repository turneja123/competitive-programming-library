//https://codesprintla25.kattis.com/contests/codesprintla25open/problems/topsidevszaun
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 305;
const int S = sqrt(90005);

int a[N];
int dp[2 * N][2 * S];
int dp_nx[2 * N][2 * S];
bool seen[2 * N][2 * S];

mt19937 gen(3);

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    shuffle(a, a + n, gen);
    dp[N][S] = 0;
    dp[N - 1][S - a[0]] = 1;
    dp[N + 1][S + a[0]] = 1;
    vector<pair<int, int>> go{{N, S}, {N - 1, S - a[0]}, {N + 1, S + a[0]}};
    int ans = 0;
    for (int i = 1; i < n; i++) {
        vector<pair<int, int>> nx;
        for (auto [ct, j] : go) {
            dp_nx[ct][j] = max(dp_nx[ct][j], dp[ct][j]);
            if (!seen[ct][j]) {
                    nx.push_back(make_pair(ct, j));
                    seen[ct][j] = true;
                }
            if (ct + 1 < 2 * N && j + a[i] < 2 * S) {
                dp_nx[ct + 1][j + a[i]] = max(dp_nx[ct + 1][j + a[i]], dp[ct][j] + 1);
                if (!seen[ct + 1][j + a[i]]) {
                    nx.push_back(make_pair(ct + 1, j + a[i]));
                    seen[ct + 1][j + a[i]] = true;
                }
            }
            if (ct - 1 >= 0 && j - a[i] >= 0) {
                dp_nx[ct - 1][j - a[i]] = max(dp_nx[ct - 1][j - a[i]], dp[ct][j] + 1);
                if (!seen[ct - 1][j - a[i]]) {
                    nx.push_back(make_pair(ct - 1, j - a[i]));
                    seen[ct - 1][j - a[i]] = true;
                }
            }
            dp[ct][j] = 0;
        }
        go = nx;
        for (auto [ct, j] : go) {
            seen[ct][j] = false;
            if (j == S && ct == N) {
                ans = max(ans, dp_nx[ct][j]);
            }
            dp[ct][j] = max(dp[ct][j], dp_nx[ct][j]);
            dp_nx[ct][j] = 0;
        }
    }
    cout << ans / 2;
    return 0;
}
