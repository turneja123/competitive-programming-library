//https://atcoder.jp/contests/arc212/tasks/arc212_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll M = 998244353;

int main() {
    IOS;
    int n, m, x;
    cin >> n >> m >> x;
    ll ans = 0;
    for (int i = 0; i <= m; i++) {
        int a = i, b = x, j = n - 2;
        while (j > 0) {
            if (a == 0) {
                a = (j % 3 == 2 ? b : 0);
                break;
            }
            if (b == 0) {
                b = (j % 3 == 2 ? a : 0);
                break;
            }
            int it = min(j / 3, (b - a) / (2 * a));
            b -= it * 2 * a, j -= it * 3;
            if (j > 0) {
                tie(a, b) = make_pair(abs(b - a), a);
                j--;
            }
        }
        ans = (ans + (ll)a * b) % M;
    }
    cout << ans;
    return 0;
}
