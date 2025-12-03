//https://codeforces.com/contest/2170/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const ll M = 998244353;

int j[N];
ll dp[N];
ll dp_s[N];


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        vector<pair<int, int>> a(m), ivals;
        for (int i = 0; i <= n; i++) {
            j[i] = -1;
        }

        for (int i = 0; i < m; i++) {
            int l, r;
            cin >> l >> r;
            a[i] = {l, -(r - 1)};
        }
        sort(a.begin(), a.end());
        for (int i = 0; i < m; i++) {
            a[i].second *= -1;
            while (ivals.size() && ivals.back().second >= a[i].second) {
                ivals.pop_back();
            }
            ivals.push_back(a[i]);
        }
        for (auto [l, r] : ivals) {
            j[r] = l;
        }
        dp[0] = 1, dp_s[0] = 1;
        int l = 0;
        for (int i = 1; i < n; i++) {
            dp[i] = (dp_s[i - 1] - (l == 0 ? 0 : dp_s[l - 1]) + M) % M;
            dp_s[i] = (dp_s[i - 1] + dp[i]) % M;
            l = max(l, j[i]);
        }
        cout << (dp_s[n - 1] - (l == 0 ? 0 : dp_s[l - 1]) + M) * 2 % M << endl;


    }


    return 0;
}
