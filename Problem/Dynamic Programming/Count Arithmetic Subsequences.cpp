//https://atcoder.jp/contests/abc362/tasks/abc362_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 85;
const long long M = 998244353;

int a[N];

map<pair<int, int>, long long> dp[N];
map<pair<int, int>, long long> dp_next[N];

int main() {
	IOS;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
        cin >> a[i];
        for (int j = 0; j < i; j++) {
            dp_next[2][make_pair(a[i], a[i] - a[j])]++;
        }
        for (int k = 3; k <= n; k++) {
            for (auto it = dp[k - 1].begin(); it != dp[k - 1].end(); ++it) {
                if (a[i] - (it->first).first != (it->first).second) {
                    continue;
                }
                dp_next[k][make_pair(a[i], a[i] - (it->first).first)] += it->second;
            }
        }
        for (int k = 2; k <= n; k++) {
            for (auto it = dp_next[k].begin(); it != dp_next[k].end(); ++it) {
                dp[k][it->first] = (dp[k][it->first] + it->second) % M;
            }
            dp_next[k].clear();
        }
	}
    cout << n << " ";
    for (int k = 2; k <= n; k++) {
        long long ans = 0 ;
        for (auto it = dp[k].begin(); it != dp[k].end(); ++it) {
            ans += it->second;
        }
        cout << ans % M << " ";
    }

	return 0;
}
