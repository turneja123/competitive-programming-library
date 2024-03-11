//https://codeforces.com/contest/1316/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int K = 7;

long long dp[N][(1 << K) + 5];
vector<pair<long long, vector<long long>>> a;

bool comp(pair<long long, vector<long long>> x, pair<long long, vector<long long>> y) {
    return x.first > y.first;
}

int main() {
    IOS;
    int n, p, k;
    cin >> n >> p >> k;
    a.resize(n, make_pair(0, vector<long long>(p, 0)));
    for (int i = 0; i < n; i++) {
        cin >> a[i].first;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < p; j++) {
            cin >> (a[i].second)[j];
        }
    }
    sort(a.begin(), a.end(), comp);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < (1 << p); j++) {
            dp[i][j] = -1;
        }
    }
    dp[0][0] = a[0].first;
    for (int s = 0; s < p; s++) {
        dp[0][(1 << s)] = (a[0].second)[s];
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < (1 << p); j++) {
            dp[i][j] = dp[i - 1][j];
            if (i + 1 - __builtin_popcount(j) <= k && dp[i - 1][j] != -1) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j] + a[i].first);
            }
            for (int s = 0; s < p; s++) {
                int c = j & (1 << s);
                if (i + 1 >= __builtin_popcount(j) && c != 0 && dp[i - 1][j ^ (1 << s)] != -1) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j ^ (1 << s)] + (a[i].second)[s]);
                }
            }
        }
    }
    cout << dp[n - 1][(1 << p) - 1] << endl;

    return 0;
}
