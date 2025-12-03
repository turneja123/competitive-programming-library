//https://evaluator.hsin.hr/events/coci26_2/tasks/HONI252627rastuci/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5005;
const ll INF = 1e18;

ll dp[N][N];
ll pref[N];
int go[N][N];
int a[N];


int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        pref[i] = pref[i - 1] + a[i];
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = INF;
        }
    }
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        ll s = 0;
        for (int j = i - 1; j >= 0; j--) {
            s += a[j + 1];
            int l = 0, r = j, spl = -1;
            while (l <= r) {
                int mid = (l + r) / 2;
                if (dp[j][mid] <= s) {
                    spl = mid;
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
            if (spl != -1) {
                if (dp[i][spl + 1] > s) {
                    dp[i][spl + 1] = s;
                    go[i][spl + 1] = j;
                }
            }
        }
        int best = i;
        for (int j = i; j >= 0; j--) {
            if (dp[i][j] >= dp[i][best]) {
                dp[i][j] = dp[i][best];
                go[i][j] = go[i][best];
            } else {
                best = j;
            }
        }
    }
    int ans = 0;
    for (int j = 1; j <= n; j++) {
        if (dp[n][j] != INF) {
            ans = j;
        }
    }
    cout << ans << endl;
    vector<ll> v;
    int i = n;
    while (ans != 0) {
        int nx = go[i][ans];
        v.push_back(pref[i] - pref[nx]);
        i = nx; ans--;
    }
    reverse(v.begin(), v.end());

    for (ll x : v) {
        cout << x << " ";
    }

    return 0;
}
