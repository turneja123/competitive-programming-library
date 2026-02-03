//https://atcoder.jp/contests/arc213/tasks/arc213_a
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e4 + 5;
const int INF = 1e9;

vector<int> a[N];
int cost[N];
int id[10];
int n;
int dp[N];
int pref[N];

int dist(vector<int> &a, vector<int> &b) {
    for (int i = 0; i < n; i++) {
        id[a[i]] = i;
    }
    int d = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i - 1; j >= 0; j--) {
            if (id[b[i]] < id[b[j]]) {
                d++;
            }
        }
    }
    return d;
}

int main() {
    IOS;
    int m;
    cin >> m >> n;
    a[0].resize(n);
    iota(a[0].begin(), a[0].end(), 0);

    for (int i = 1; i <= m; i++) {
        dp[i] = -INF;
        cin >> cost[i];
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            x--;
            a[i].push_back(x);
        }
        for (int k = 1; k < 40; k++) {
            int j = i - k;
            if (j < 0) {
                break;
            }
            int d = dist(a[i], a[j]);
            if (d <= k && dp[j] != -INF) {
                dp[i] = max(dp[i], dp[j] + cost[i]);
            }
        }
        if (i - 40 >= 0) {
            dp[i] = max(dp[i], pref[i - 40] + cost[i]);
        }
        pref[i] = max(pref[i - 1], dp[i]);
    }
    cout << pref[m];

    return 0;
}
