//https://www.spoj.com/problems/MAXOR/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 12005;

int dp[N][N];
int pref[N];
int a[N];

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pref[i] = (i == 0 ? 0 : pref[i - 1]) ^ a[i];
        dp[i][i] = a[i];
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j + i < n; j++) {
            dp[j][j + i] = max({dp[j + 1][j + i], dp[j][j + i - 1], pref[j + i] ^ (j == 0 ? 0 : pref[j - 1])});
        }
    }
    int last = 0;
    for (int i = 0; i < q; i++) {
        ll l, r;
        cin >> l >> r;
        l = (l + last) % n, r = (r + last) % n;
        if (l > r) {
            swap(l, r);
        }
        last = dp[l][r];
        cout << last << endl;
    }

    return 0;
}
