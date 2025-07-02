//https://ocpc2025s.eolymp.space/en/compete/s47ok89k9t7evbt1ovdfvc933c/problem/6
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

long long dp[N];

bool comp(pair<int, int> &a, pair<int, int> &b) {
    if (a.first != b.first) {
        return a.first < b.first;
    }
    return a.second > b.second;
}

int main() {
    IOS;
    int n;
    cin >> n;
    vector<pair<int, int>> items(n);
    for (int i = 0; i < n; i++) {
        cin >> items[i].first >> items[i].second;
    }
    sort(items.begin(), items.end(), comp);
    int best = 0;
    vector<pair<int, int>> st;
    for (int i = 0; i < n; i++) {
        if (best < items[i].second) {
            st.push_back(items[i]);
            best = items[i].second;
        }
    }
    for (int i = 1; i <= n; i++) {
        dp[i] = max(dp[i], dp[i - 1]);
        for (auto [s, v] : st) {
            if (i - s >= 0) {
                dp[i] = max(dp[i], dp[i - s] + v);
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << dp[i] << " ";
    }
    return 0;
}
