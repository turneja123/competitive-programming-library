//https://ocpc2025s.eolymp.space/en/compete/mdpvbmkn7129t7jclok5kktmig/problem/9
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 1e5 + 5;
const int SQ = 4e6 + 5;

int a[N], b[N], c[N];

long long pref[N];

int main() {
    IOS;
    int n;
    cin >> n;
    long long sa = 0, sb = 0, sc = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i] >> b[i];
        c[i] = b[i] - a[i];
        sa += a[i];
        sb += b[i];
        sc += c[i];
    }
    sort(c, c + n, greater<int>());
    for (int i = 0; i < n; i++) {
        pref[i] = (i == 0 ? c[i] : pref[i - 1] + c[i]);
    }
    long long ans = 0;
    for (int i = 1; i <= min(sb, (ll)SQ); i++) {
        long long d = (sa + i - 1) / i * i;
        if (d != sa) {
            d = d - sa;
            if (d <= sc) {
                ans += lower_bound(pref, pref + n, d) - pref + 1;
            }
        }
    }
    for (int k = 1; k <= (sa + SQ - 1) / SQ; k++) {
        ll hi = (k == 1 ? sb : (sa - 1) / (k - 1));
        int st = lower_bound(pref, pref + n, k * (SQ + 1) - sa) - pref;
        for (int i = st; i < n; i++) {
            long long l = (sa + (i == 0 ? 0 : pref[i - 1])) / k;
            long long r = min((sa + pref[i]) / k, hi);
            l = max(l, (ll)SQ) + 1;
            if (l > hi) {
                break;
            }
            if (l <= r) {
                ans += (ll)(i + 1) * (r - l + 1);
            }
        }
    }

    cout << ans;
    return 0;
}
