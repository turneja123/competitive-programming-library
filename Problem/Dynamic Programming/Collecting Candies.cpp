//https://www.spoj.com/problems/GSCANDY/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2005;

int a[N];
int mx[N];
int dp[N][N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        map<int, int> mp;
        int n, ans = 0;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (mp.find(a[i]) == mp.end()) {
                mp[a[i]] = mp.size();

            }
            a[i] = mp[a[i]];
            vector<int> nw(n + 1, 0);
            nw[1] = 1;
            for (int j = 0; j < n; j++) {
                if (j != a[i]) {
                    nw[1] = max(nw[1], mx[j] + 1);
                }
            }
            for (int j = 1; j < n && dp[a[i]][j] > 0; j++) {
                nw[j + 1] = dp[a[i]][j] + j + 1;
            }
            for (int j = 1; j <= n; j++) {
                mx[a[i]] = max(mx[a[i]], nw[j]);
                dp[a[i]][j] = nw[j];
            }
            ans = max(ans, mx[a[i]]);
        }
        cout << ans << endl;
        for (int i = 0; i < n; i++) {
            mx[i] = 0;
            for (int j = 1; j <= n; j++) {
                dp[i][j] = 0;
            }
        }
    }

    return 0;
}
