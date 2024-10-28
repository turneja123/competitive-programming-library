//https://codeforces.com/contest/2026/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;

long long a[N];
long long b[N];

long long prefindl[N];
long long prefindr[N];
long long pref_b[N];
long long pref[N];
long long pref_arith[N];

long long arith(int l, int r) {
    if (l > r) {
        return 0;
    }
    long long ans = (pref[r] - (l > 0 ? pref[l - 1] : 0)) * (r + 1) - (pref_arith[r] - (l > 0 ? pref_arith[l - 1] : 0));
    return ans;
}

long long calc(int g, int l, int r) {
    if (l > r) {
        return 0;
    }
    long long ans = 0;
    /*
    for (int i = g, k = l; i <= g + (r - l); i++, k++) {
        for (int j = g; j <= g + k; j++) {
            ans += a[j];
        }
    }
    return ans;
    */
    ans = (pref[g + l] - ((g == 0) ? 0 : pref[g - 1])) * (r - l + 1) + arith(g + l + 1, g + l + (r - l));
    return ans;
}


int main() {
    IOS;
    int n, q;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        prefindl[i] = ((i == 0) ? 0 : prefindl[i - 1] + (n - i + 1));
        prefindr[i] = ((i == 0) ? n - i - 1 : prefindr[i - 1] + (n - i));
        b[0] += a[i] * (n - i);
        pref_arith[i] = ((i == 0) ? 0 : pref_arith[i - 1] + a[i] * (i));
        pref[i] = ((i == 0) ? a[i] : pref[i - 1] + a[i]);
    }
    pref_b[0] = b[0];
    for (int i = 1; i < n; i++) {
        b[i] = b[i - 1] - (n - i + 1) * a[i - 1];
        pref_b[i] = pref_b[i - 1] + b[i];
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        long long l, r;
        cin >> l >> r;
        int lg, rg;
        l--, r--;
        lg = lower_bound(prefindl, prefindl + n, l) - prefindl;
        rg = upper_bound(prefindr, prefindr + n, r) - prefindr - 1;
        long long ans = 0;
        if (lg <= rg) {
            ans += pref_b[rg] - ((lg == 0) ? 0 : pref_b[lg - 1]);
            if (lg > 0) {
                ans += calc(lg - 1, n - (lg - 1) - 1 - (prefindr[lg - 1] - l), n - (lg - 1) - 1);
            }
            if (rg < n - 1) {
                ans += calc(rg + 1, 0, r - prefindl[rg + 1]);
            }
        } else {
            if (r >= prefindl[lg]) {
                ans += calc(lg, max(0ll, l - prefindl[lg]), l - prefindl[lg] + (r - l));
            }
            lg--;
            if (lg >= 0){
                if (l >= prefindl[lg]) {
                    ans += calc(lg, l - prefindl[lg], min((long long)n - lg - 1, l - prefindl[lg] + (r - l)));
                }
            }
        }
        cout << ans << endl;
    }

    return 0;
}
