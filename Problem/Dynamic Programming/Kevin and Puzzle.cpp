//https://codeforces.com/contest/2061/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long M = 998244353;

int a[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        map<tuple<int, int, int>, long long> dp;
        queue<tuple<int, int, int>> q;
        if (a[0] == 0) {
            dp[make_tuple(0, 0, 0)] = 1;
            dp[make_tuple(0, 1, 1)] = 1;
            q.push(make_tuple(0, 0, 0));
            q.push(make_tuple(0, 1, 1));
        } else {
            dp[make_tuple(0, 1, 1)] = 1;
            q.push(make_tuple(0, 1, 1));
        }
        long long ans = 0;
        while (q.size()) {
            auto [i, l, f] = q.front();
            q.pop();
            i++;
            if (i == n) {
                ans = (ans + dp[make_tuple(i - 1, l, f)]) % M;
                continue;
            }
            if (f == 0) {
                if (a[i] == l) {
                    auto it = dp.find(make_tuple(i, l, 0));
                    if (it == dp.end()) {
                        dp[make_tuple(i, l, 0)] = dp[make_tuple(i - 1, l, 0)];
                        q.push(make_tuple(i, l, 0));
                    } else {
                        it->second = (it->second + dp[make_tuple(i - 1, l, 0)]) % M;
                    }
                }
                auto it = dp.find(make_tuple(i, l + 1, 1));
                if (it == dp.end()) {
                    dp[make_tuple(i, l + 1, 1)] = dp[make_tuple(i - 1, l, 0)];
                    q.push(make_tuple(i, l + 1, 1));
                } else {
                    it->second = (it->second + dp[make_tuple(i - 1, l, 0)]) % M;
                }
            } else {
                if (a[i] == l) {
                    auto it = dp.find(make_tuple(i, l, 0));
                    if (it == dp.end()) {
                        dp[make_tuple(i, l, 0)] = dp[make_tuple(i - 1, l, 1)];
                        q.push(make_tuple(i, l, 0));
                    } else {
                        it->second = (it->second + dp[make_tuple(i - 1, l, 1)]) % M;
                    }
                }
            }
        }
        cout << ans << endl;
    }
    return 0;
}
