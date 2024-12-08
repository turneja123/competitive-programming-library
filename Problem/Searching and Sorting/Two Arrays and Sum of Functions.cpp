//https://codeforces.com/contest/1165/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int M = 998244353;

long long a[N], b[N];

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] = a[i] * (i + 1) * (n - i);
    }
    sort(a, a + n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    sort(b, b + n);
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        ans = (ans + a[i] % M * b[n - 1 - i] % M) % M;
    }
    cout << ans;

    return 0;
}
