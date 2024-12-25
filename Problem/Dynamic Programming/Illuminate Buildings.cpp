//https://atcoder.jp/contests/abc385/tasks/abc385_c
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3005;

int a[N];
bool seen[N];
vector<int> pos[N];
int dp[N][N];

int solve(vector<int> a) {
    int n = a.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < N; j++) {
            dp[i][j] = -1;
        }
    }
    int ans = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (dp[j][a[i] - a[j]] == -1) {
                dp[i][a[i] - a[j]] = max(dp[i][a[i] - a[j]], 2);
            } else {
                dp[i][a[i] - a[j]] = max(dp[i][a[i] - a[j]], dp[j][a[i] - a[j]] + 1);
            }
            ans = max(ans, dp[i][a[i] - a[j]]);
        }
    }
    return ans;
}

int main() {
    IOS;
    int n;
    cin >> n;
    int ans = 1;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pos[a[i]].push_back(i);
    }
    for (int i = 0; i < n; i++) {
        if (!seen[a[i]]) {
            seen[a[i]] = true;
            ans = max(ans, solve(pos[a[i]]));
        }
    }
    cout << ans;

    return 0;
}
