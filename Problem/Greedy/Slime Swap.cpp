//https://atcoder.jp/contests/arc206/tasks/arc206_b
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
int c[N];
int dp[N];

vector<int> pos[N];

int calc(vector<int> &a) {
    int n = a.size();
    int ans = 1;
    dp[1] = a[0];
    for (int i = 1; i < n; i++) {
        int l = 1, r = n, mx = 0;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (dp[mid] < a[i]) {
                l = mid + 1;
                mx = mid;
            } else {
                r = mid - 1;
            }
        }
        dp[mx + 1] = min(dp[mx + 1], a[i]);
        ans = max(ans, mx + 1);
    }
    for (int i = 1; i <= n + 1; i++) {
        dp[i] = INF;
    }
    return ans;
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        dp[i + 1] = INF;
    }
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        pos[c[i]].push_back(a[i]);
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        if (pos[i].size()) {
            int s = pos[i].size();
            s -= calc(pos[i]);
            ans += (ll)i * s;
        }
    }
    cout << ans;
    return 0;
}
