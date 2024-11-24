//https://cses.fi/problemset/task/1191
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 20;

int a[N];
long long pref[N];
pair<int, long long> up[K][N];

int main() {
    IOS;
    int n; long long k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pref[i] = (i == 0 ? a[i] : pref[i - 1] + a[i]);
    }
    for (int i = 0; i < n; i++) {
        int l = 0, r = n - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            int j = (i + mid) % n;
            long long cur;
            if (j >= i) {
                cur = pref[j] - (i == 0 ? 0 : pref[i - 1]);
            } else {
                cur = pref[n - 1] - (i == 0 ? 0 : pref[i - 1]) + pref[j];
            }
            if (cur <= k) {
                l = mid + 1;
                up[0][i] = make_pair(j + 1, cur);
            } else {
                r = mid - 1;
            }
        }
    }
    for (int k = 1; k < K; k++) {
        for (int i = 0; i < n; i++) {
            int v = up[k - 1][i].first;
            if (v == -1) {
                up[k][i] = make_pair(-1, -1);
                continue;
            }
            long long sum = up[k - 1][i].second + up[k - 1][v].second;
            if (sum > pref[n - 1]) {
                up[k][i] = make_pair(-1, -1);
            } else {
                up[k][i] = make_pair(up[k - 1][v].first, sum);
            }
        }
    }
    int ans = n;
    for (int i = 0; i < n; i++) {
        long long sum = 0; int cur = 0, u = i;
        for (int k = K - 1; k >= 0; k--) {
            if (up[k][u].first == -1) {
                continue;
            }
            if (sum + up[k][u].second <= pref[n - 1]) {
                sum += up[k][u].second;
                cur += 1 << k;
                u = up[k][u].first;
            } else {
                ans = min(ans, cur + (1 << k));
            }
        }
        if (sum == pref[n - 1]) {
            ans = min(ans, cur);
        } else {
            ans = min(ans, cur + 1);
        }
    }
    cout << ans;

    return 0;
}
