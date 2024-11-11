//https://atcoder.jp/contests/abc375/tasks/abc375_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 105;
const int S = 1505;

int a[N];
int b[N];

int sum[3];
int dp[2 * S][2 * S];
int dp_next[2 * S][2 * S];

vector<pair<int, int>> nx;

void chmin(int j, int k, int val) {
    if (dp_next[j][k] == N) {
        nx.push_back(make_pair(j, k));
    }
    dp_next[j][k] = min(dp_next[j][k], val);
    return;
}

int main() {
    IOS;
    int mid = 1502;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        a[i]--;
        sum[a[i]] += b[i];
    }
    for (int j = 0; j < 2 * S; j++) {
        for (int k = 0; k < 2 * S; k++) {
            dp[j][k] = N;
            dp_next[j][k] = N;
        }
    }
    dp[mid - (sum[0] - sum[1])][mid - (sum[0] - sum[2])] = 0;
    vector<pair<int, int>> nonzero{make_pair(mid - (sum[0] - sum[1]), mid - (sum[0] - sum[2]))};
    for (int i = 0; i < n; i++) {
        for (pair<int, int> p : nonzero) {
            int j = p.first, k = p.second;
            if (a[i] == 0) {
                chmin(j, k, dp[j][k]);
                chmin(j + 2 * b[i], k + b[i], dp[j][k] + 1);
                chmin(j + b[i], k + 2 * b[i], dp[j][k] + 1);
            } else if (a[i] == 1) {
                chmin(j, k, dp[j][k]);
                chmin(j - 2 * b[i], k - b[i], dp[j][k] + 1);
                chmin(j - b[i], k + b[i], dp[j][k] + 1);
            } else {
                chmin(j, k, dp[j][k]);
                chmin(j - b[i], k - 2 * b[i], dp[j][k] + 1);
                chmin(j + b[i], k - b[i], dp[j][k] + 1);
            }
        }
        for (pair<int, int> p : nx) {
            int j = p.first, k = p.second;
            dp[j][k] = min(dp[j][k], dp_next[j][k]);
            dp_next[j][k] = N;
        }
        nonzero = nx;
        nx.clear();
    }
    cout << (dp[mid][mid] == N ? -1 : dp[mid][mid]);
    return 0;
}
