//https://codeforces.com/contest/2229/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 17;

pair<int, ll> dp[1 << N];

pair<int, ll> add(pair<int, ll> a, ll x, ll m) {
    a.second += x;
    if (a.second >= m) {
        a.first++;
        a.second = 0;
    }
    return a;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        if (n == k) {
            cout << a.back() << endl;
            continue;
        }
        int mx = a.back();
        a.pop_back();
        n = a.size();

        ll l = 1, r = 1e12, spl = 1;
        while (l <= r) {
            ll mid = (l + r) / 2;
            for (int i = 0; i < 1 << n; i++) {
                dp[i] = {0, 0};
                for (int j = 0; j < n; j++) {
                    int c = i & (1 << j);
                    if (c) {
                        dp[i] = max(dp[i], add(dp[i ^ (1 << j)], a[j], mid));
                    }
                }
            }
            if (dp[(1 << n) - 1].first >= k) {
                l = mid + 1;
                spl = mid;
            } else {
                r = mid - 1;
            }
        }
        cout << spl + mx << endl;
    }

    return 0;
}
