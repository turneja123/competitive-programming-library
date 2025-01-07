//https://dmoj.ca/problem/utso24p2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int a[N], b[N];
long long prefa[N], prefb[N];

int main() {
    IOS;
    int t, k, n = 0, m = 0;
    cin >> t >> k;
    for (int i = 0; i < t; i++) {
        int x;
        cin >> x;
        if (x >= 0) {
            a[n++] = -x;
        } else {
            b[m++] = x;
        }
    }
    sort(a, a + n);
    sort(b, b + m);
    for (int i = 0; i < n; i++) {
        prefa[i] = (i == 0 ? -a[i] : prefa[i - 1] - a[i]);
    }
    for (int i = 0; i < m; i++) {
        prefb[i] = (i == 0 ? -b[i] : prefb[i - 1] - b[i]);
    }
    int take = min(m, k / 2);
    long long ans = (take == 0 ? 0 : prefb[take - 1]);
    for (int i = 0; i < n && i < k; i++) {
        int take = min(m, (k - i - 1) / 2);
        ans = max(ans, prefa[i] + prefb[take - 1]);
    }
    cout << ans;
    return 0;
}
