//https://codeforces.com/contest/2230/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

vector<int> posa[N];
vector<int> posb[N];


int dp[N];


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {

        int n;
        cin >> n;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            posa[a[i]].push_back(i);
            dp[i] = -1;
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
            posb[b[i]].push_back(i);
        }

        for (int i = n - 1; i >= 0; i--) {
            if (a[i] != b[i]) {
                dp[i] = i;
                continue;
            }
            auto ja = upper_bound(posa[a[i] + 1].begin(), posa[a[i] + 1].end(), i);
            auto jb = upper_bound(posb[a[i] + 1].begin(), posb[a[i] + 1].end(), i);
            int r = n;

            dp[i] = n;

            if (ja != posa[a[i] + 1].end()) {
                dp[i] = dp[*ja];
                r = *ja;
            }
            if (jb != posb[a[i] + 1].end() && *jb < r) {
                dp[i] = min(dp[i], *jb);
            }

        }
        ll ans = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] == 1 && b[i] != 1) {
                continue;
            }
            if (a[i] != 1 && b[i] == 1) {
                continue;
            }
            if (a[i] == 1 && b[i] == 1) {
                ans += dp[i] - i;
                continue;
            }
            auto ja = upper_bound(posa[1].begin(), posa[1].end(), i);
            auto jb = upper_bound(posb[1].begin(), posb[1].end(), i);


            int r = n, pos = n;
            if (ja != posa[1].end()) {
                r = dp[*ja];
                pos = *ja;
            }
            if (jb != posb[1].end() && *jb < pos) {
                r = min(r, *jb);
            }
            ans += r - i;
        }
        cout << ans << endl;
        for (int i = 1; i <= n; i++) {
            posa[i].clear();
            posb[i].clear();
        }


    }
    return 0;
}
