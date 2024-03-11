#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

pair<int, pair<int, int>> a[N];


int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        int x, y, wt;
        cin >> x >> y >> wt;
        a[i] = {wt, {abs(x), abs(y)}};
    }
    sort(a, a + n);
    int ans = a[n - 1].first;
    int x = 0, y = 0;
    for (int i = n - 1; i >= 0; i--) {
        int cur = 0;
        if (i != 0) {
            cur = a[i - 1].first;
        }
        x = max(x, a[i].second.first);
        y = max(y, a[i].second.second);
        ans = min(ans, cur + 4 * x * k + 4 * y * k);
    }
    cout << ans;
    return 0;
}
