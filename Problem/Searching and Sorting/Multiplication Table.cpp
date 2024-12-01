//https://cses.fi/problemset/task/2422
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    IOS;
    int n;
    cin >> n;
    long long l = 1, r = 1e18, ans = 0, need = (long long)n * n / 2 + 1;
    while (l <= r) {
        long long mid = (l + r) / 2, sum = 0;
        for (int i = 1; i <= n; i++) {
            sum += min((long long)n, mid / i);
        }
        if (sum >= need) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }
    cout << ans;

    return 0;
}
