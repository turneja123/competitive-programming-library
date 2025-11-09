//https://cses.fi/problemset/task/3302/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 250005;
const ll M = 1e9 + 7;

int a[N];
int id[2 * N];
ll dp[2 * N];
ll dp_nx[2 * N];

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    int mn = 0, mx = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] -= k;
        if (a[i] < 0) {
            mn += a[i];
        } else {
            mx += a[i];
        }
    }
    for (int j = mn, k = 0; j <= mx; j++, k++) {
        id[j + N] = k;
    }
    mn = 0, mx = 0;
    dp[id[N]] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = mn; j <= mx; j++) {
            dp_nx[id[j + N]] = (dp_nx[id[j + N]] + dp[id[j + N]]) % M;
            dp_nx[id[j + a[i] + N]] = (dp_nx[id[j + a[i] + N]] + dp[id[j + N]]) % M;
        }
        if (a[i] < 0) {
            mn += a[i];
        } else {
            mx += a[i];
        }
        for (int j = mn; j <= mx; j++) {
            dp[id[j + N]] = dp_nx[id[j + N]];
            dp_nx[id[j + N]] = 0;
        }
    }
    cout << (dp[id[N]] - 1 + M) % M;


    return 0;
}
