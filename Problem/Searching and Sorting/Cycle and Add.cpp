//https://www.codechef.com/problems/CYCADEQ
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5005;
const int K = 20;

int b[N];
int d[N];

int table[K][N];

void build(int n) {
    for (int i = 1; i <= n; i++) {
        table[0][i] = b[i - 1];
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            table[k][i] = min(table[k - 1][i], table[k - 1][i + (1 << (k - 1))]);
        }
    }
    return;
}

int query(int l, int r) {
    l++, r++;
    int k = 31 - __builtin_clz(r - l + 1);
    return min(table[k][l], table[k][r - (1 << k) + 1]);
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, c;
        cin >> n >> c;
        for (int i = 0; i < n; i++) {
            cin >> b[i];
            b[i + n] = b[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> d[i];
            d[i + n] = d[i];
        }
        build(2 * n);
        ll ans = 1e18;
        for (int j = 0; j < n; j++) {
            ll cost = (ll)j * c;
            for (int i = n; i < 2 * n; i++) {
                int k = query(i - j, i);
                cost += (ll)k * d[i];
            }
            ans = min(ans, cost);
        }
        cout << ans << endl;
    }
    return 0;
}
