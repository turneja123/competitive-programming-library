//https://codeforces.com/problemset/problem/439/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N], b[N];

long long calc(int k, int n, int m) {
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] < k) {
            ans += k - a[i];
        }
    }
    for (int i = 0; i < m; i++) {
        if (b[i] > k) {
            ans += b[i] - k;
        }
    }
    return ans;
}



int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    int l = 1, r = 1e9;
    while (r - l >= 3) {
        int m1 = l + (r - l) / 3;
        int m2 = r - (r - l) / 3;

        long long f1 = -calc(m1, n, m);
        long long f2 = -calc(m2, n, m);

        if (f1 < f2) {
            l = m1 + 1;
        } else {
            r = m2 - 1;
        }
    }
    long long ans = 1e18;
    for (; l <= r; l++) {
        ans = min(ans, calc(l, n, m));
    }
    cout << ans;
    return 0;
}
