//https://codeforces.com/contest/1043/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

int main() {
    IOS;
    vector<ll> a(N, 0);
    int n;
    cin >> n;
    int g = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        g = (g == 0 ? x : __gcd(g, x));
        a[x] = 1;
    }
    if (g > 1) {
        cout << -1;
        return 0;
    }
    vector<ll> b = a;
    vector<ll> c(N, 0);
    int ans = 1;
    while (1) {
        if (a[1]) {
            cout << ans;
            return 0;
        }

        for (int i = 1; i < N; i++) {
            ll ca = 0, cb = 0;
            for (int j = i; j < N; j += i) {
                ca += a[j];
                cb += b[j];
            }
            c[i] = ca * cb;
        }
        for (int i = N - 1; i > 0; i--) {
            for (int j = 2 * i; j < N; j += i) {
                c[i] -= c[j];
            }
        }
        for (int i = 1; i < N; i++) {
            c[i] = min(c[i], 1ll);
        }
        a = c;
        ans++;
    }


    return 0;
}
