//https://cses.fi/problemset/task/1750/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int K = 30;

int a[N];
int up[K][N];

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        up[0][i] = a[i];
    }

    for (int k = 1; k < 30; k++) {
        for (int i = 0; i < n; i++) {
            up[k][i] = up[k - 1][up[k - 1][i]];
        }
    }
    for (int i = 0; i < q; i++) {
        int j, x;
        cin >> j >> x;
        j--;
        int ans = j;
        for (int k = 29; k >= 0; k--) {
            int c = x & (1 << k);
            if (c) {
                ans = up[k][ans];
            }
        }
        cout << ans + 1 << endl;

    }

    return 0;
}
