//solution for https://atcoder.jp/contests/abc184/tasks/abc184_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e6 + 5;

ll suma[N];
ll sumb[N];

int main() {
    IOS;
    int n;
    ll t;
    cin >> n >> t;
    int na = n / 2 + n % 2;
    int nb = n / 2;
    ll a[na] = { };
    ll b[nb] = { };
    for (int i = 0; i < na; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < nb; i++) {
        cin >> b[i];
    }
    int pwa = 1 << na;
    int pwb = 1 << nb;
    for (int i = 0; i < pwa; i++) {
        ll cur = 0;
        for (int j = 0; j < na; j++) {
            if (i & (1 << j)) {
                cur += a[j];
            }
        }
        suma[i] = cur;
    }
    for (int i = 0; i < pwb; i++) {
        ll cur = 0;
        for (int j = 0; j < nb; j++) {
            if (i & (1 << j)) {
                cur += b[j];
            }
        }
        sumb[i] = cur;
    }
    sort(suma, suma + pwa);
    sort(sumb, sumb + pwb);
    ll best = 0;
    int r = pwb - 1;
    for (int i = 0; i < pwa; i++) {
        while (r >= 0 && (suma[i] + sumb[r]) > t) {
            r--;
        }
        if (r < 0) {
            break;
        }
        best = max(best, suma[i] + sumb[r]);
    }
    cout << best;
    return 0;
}

