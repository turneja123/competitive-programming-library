//https://cses.fi/problemset/task/3406
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long N = 1e12;

int main() {
    IOS;
    vector<long long> sorted;
    for (int i = 1; i < 1e7; i++) {
        long long t = (long long)i * (i + 1) / 2;
        if (t > N) {
            break;
        }
        sorted.push_back(t);
    }
    int t;
    cin >> t;
    while (t--) {
        long long n;
        cin >> n;
        int r = lower_bound(sorted.begin(), sorted.end(), n) - sorted.begin();
        if (r != sorted.size() && sorted[r] == n) {
            cout << 1 << endl;
            continue;
        }
        r--;
        int ans = 3;
        for (int l = 0; l <= r; l++) {
            while (r >= 0 && sorted[l] + sorted[r] > n) {
                r--;
            }
            if (l > r) {
                break;
            }
            if (sorted[l] + sorted[r] == n) {
                ans = 2;
                break;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
