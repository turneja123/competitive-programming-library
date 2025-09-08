//https://atcoder.jp/contests/arc205/tasks/arc205_b
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int deg[N];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    ll ans = (ll)n * (n - 1) / 2;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        deg[u]++, deg[v]++;
    }
    int a = 0, b = 0;
    for (int i = 0; i < n; i++) {
        if (deg[i] % 2 == 0) {
            a++;
        } else {
            b++;
        }
    }
    if (n % 2 == 0) {
        ans -= a / 2;
    } else {
        ans -= b / 2;
    }
    cout << ans << endl;

    return 0;
}
