//https://codeforces.com/contest/802/problem/N
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const ll INF = 1e18;

long long a[N];
long long b[N];
pair<long long, int> dp[N];
pair<long long, int> dp_nx[N];

pair<long long, int> calc(int n, long long cost) {
    vector<pair<ll, int>> items;
    for (int i = 1; i <= n; i++) {
        items.push_back({a[i] + cost, 1});
        items.push_back({b[i] + cost, -1});
    }
    n = items.size();

    for (int j = 0; j <= n; j++) {
        dp[j] = {INF, 0};
        dp_nx[j] = {INF, 0};
    }
    dp[0] = make_pair(0, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= i; j++) {
            dp_nx[j] = dp[j];
            if (j - items[i - 1].second >= 0 && dp[j - items[i - 1].second].first != INF) {
                dp_nx[j] = min(dp_nx[j], {dp[j - items[i - 1].second].first + items[i - 1].first, dp[j - items[i - 1].second].second - 1});
            }
        }
        for (int j = 0; j <= i; j++) {
            dp[j] = dp_nx[j];
            dp_nx[j] = {INF, 0};
        }

    }
    return dp[0];
}

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    k *= 2;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }

    long long l = -1e13, r = 1e13, opt = 0;
    while (l <= r) {
        long long mid = (l + r) / 2;
        if (-calc(n, mid).second >= k) {
            opt = mid;
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    //cout << calc(n, opt).first << " " << calc(n, opt).second << endl;
    long long ans = calc(n, opt).first - opt * k;
    cout << ans;
    return 0;
}
