//https://atcoder.jp/contests/abc388/tasks/abc388_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;
const int K = 17;
const int INF = 1e9;

int a[N];
int b[N];
int table[K][N];

void build(int n) {
    for (int i = 1; i <= n; i++) {
        table[0][i] = b[i - 1] - (i - 1);
    }
    for (int k = 1; k < K; k++) {
        for (int i = 1; i + (1 << k) - 1 <= n; i++) {
            table[k][i] = max(table[k - 1][i], table[k - 1][i + (1 << (k - 1))]);
        }
    }
    return;
}

int query(int l, int r) {
    l++, r++;
    int k = 31 - __builtin_clz(r - l + 1);
    return max(table[k][l], table[k][r - (1 << k) + 1]);
}
int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        int x = lower_bound(a, a + n, 2 * a[i]) - a;
        if (x == n) {
            b[i] = n;
        } else {
            b[i] = x;
        }
    }
    int q;
    cin >> q;
    build(n);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        int lq = l, rq = r, ans = 0;
        while (lq <= rq) {
            int mid = (lq + rq) / 2;
            int val = query(l, mid);
            if (val <= r - mid) {
                ans = max(ans, min(r - mid, mid - l + 1));
                lq = mid + 1;
            } else {
                rq = mid - 1;
            }
        }
        cout << ans << endl;
    }

    return 0;

}
