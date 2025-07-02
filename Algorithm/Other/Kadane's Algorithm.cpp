//https://cses.fi/problemset/task/1643/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const int INF = 1e9;

int a[N];

int main() {
    IOS;
    int n;
    cin >> n;
    int g = -INF;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        g = max(g, a[i]);
    }
    if (g < 0) {
        cout << g;
        return 0;
    }
    /*long long cur = 0, ans = 0, d = 0;
    for (int i = 0; i < n; i++) {
        cur += a[i];
        d += a[i];
        if (cur < 0) {
            d -= cur;
            cur = 0;
        }
        if (d > 0) {
            ans += d;
            d = 0;
        }
    }*/
    long long ans = 0, cur = 0;
    for (int i = 0; i < n; i++) {
        cur += a[i];
        ans = max(ans, cur);
        cur = max(cur, 0ll);
    }
    cout << ans;

    return 0;
}
