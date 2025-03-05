//https://codeforces.com/contest/2071/problem/D1
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;
const long long R = 1e18;

int p[N];

int calc(long long x, int n) {
    if (x < 2 * n) {
        return p[x];
    }
    if (n % 2 == 1) {
        if (x % 2 == 1) {
            return p[n];
        }
        return p[n] ^ calc(x / 2, n);
    } else {
        if (x % 2 == 1) {
            return p[n] ^ p[n / 2];
        }
        return p[n] ^ p[n / 2] ^ calc(x / 2, n);
    }
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n; long long l, r;
        cin >> n >> l >> r;
        vector<int> a(n + 1);
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            p[i] = p[i - 1] ^ a[i];
        }
        int ans = 0;
        if (l <= n) {
            cout << a[l] << endl;
            continue;
        }
        for (int i = n + 1; i < 2 * n; i++) {
            p[i] = p[i - 1] ^ p[i / 2];
        }
        cout << calc(l / 2, n) << endl;

    }

    return 0;
}
