//https://codeforces.com/contest/1942/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5005;

int val[N][N];
int ind[N];
int suf[N];
vector<long long> dp[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        for (int i = 1; i <= n; i++) {
            for (int j = i; j <= n; j++) {
                cin >> val[i][j];
            }
        }
        dp[0].push_back(0);
        dp[1].push_back(val[1][1]);
        dp[1].push_back(0);
        sort(dp[1].begin(), dp[1].end(), greater<int>());
        for (int i = 2; i <= n; i++) {
            priority_queue<pair<long long, int>> pq;
            pq.push(make_pair(val[1][i], -1));
            for (int j = i - 1; j > 0; j--) {
                pq.push(make_pair(val[j + 1][i] + dp[j - 1][0], j - 1));
                ind[j - 1] = 0;
            }
            while (pq.size() && dp[i].size() < k) {
                long long x = pq.top().first; int j = pq.top().second;
                dp[i].push_back(x);
                pq.pop();
                if (j != -1) {
                    ind[j]++;
                    if (ind[j] < dp[j].size()) {
                        pq.push(make_pair(val[j + 2][i] + dp[j][ind[j]], j));
                    }
                }
            }
            int l = 0, r = 0;
            vector<long long> nx;
            while (nx.size() < k) {
                if (l == dp[i - 1].size() && r == dp[i].size()) {
                    break;
                }
                if (l == dp[i - 1].size()) {
                    nx.push_back(dp[i][r++]);
                } else if (r == dp[i].size()) {
                    nx.push_back(dp[i - 1][l++]);
                } else if (dp[i - 1][l] > dp[i][r]) {
                    nx.push_back(dp[i - 1][l++]);
                } else {
                    nx.push_back(dp[i][r++]);
                }
            }
            dp[i] = nx;
        }
        for (int i = 0; i < k; i++) {
            cout << dp[n][i] << " ";
        }
        cout << endl;
        for (int i = 0; i <= n; i++) {
            dp[i].clear();
            ind[i] = 0;
        }


    }
    return 0;
}
