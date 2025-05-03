//https://algotester.com/en/ArchiveProblem/DisplayWithEditor/71135
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const int INF = 1e9;

int a[N];
int dp[N][2];

int main() {
    IOS;
    int n;
    cin >> n;
    vector<pair<int, int>> compr(n);
    for (int i = 0; i < n; i++) {
        cin >> compr[i].first;
        compr[i].second = i;
    }
    sort(compr.begin(), compr.end());
    int m = -1, last = INF + 1;
    for (int i = 0; i < n; i++) {
        if (compr[i].first != last) {
            last = compr[i].first;
            m++;
        }
        a[compr[i].second] = m;
    }
    dp[a[0]][0] = 1;
    int mx = 0;
    for (int i = 1; i < n; i++) {
        if (dp[a[i]][1] != 0) {
            dp[a[i]][1]++;
        }
        if (dp[a[i]][0] != 0) {
            dp[a[i]][1] = max(dp[a[i]][1], dp[a[i]][0] + 1);
        }
        dp[a[i]][0] = mx + 1;
        mx = max(mx, dp[a[i]][1]);
    }
    cout << mx << endl;
    return 0;
}
