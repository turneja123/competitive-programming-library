//https://www.codechef.com/problems/BALDIFF
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

long long a[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n; long long x;
        cin >> n >> x;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        long long l = 0, r = 1e10, ans = r;
        vector<long long> vals(n);
        while (l <= r) {
            long long mid = (l + r) / 2;
            vector<pair<long long, long long>> v(n);
            v[0] = make_pair(a[0] - mid, a[0] + mid);
            int can = 1;
            for (int i = 1; i < n; i++) {
                v[i] = make_pair(max(v[i - 1].first, a[i] - mid), min(v[i - 1].second + x, a[i] + mid));
                if (v[i].first > v[i].second) {
                    can = 0;
                    break;
                }
            }
            if (can) {
                ans = mid;
                r = mid - 1;
                vals[n - 1] = v[n - 1].first;
                for (int i = n - 1; i >= 0; i--) {
                    if (vals[i + 1] - x >= v[i].first && vals[i + 1] - x <= v[i].second) {
                        vals[i] = vals[i + 1] - x;
                    } else {
                        vals[i] = v[i].first;
                    }
                }
            } else {
                l = mid + 1;
            }
        }
        cout << ans << endl;
        for (int i = 0; i < n; i++) {
            cout << vals[i] << " ";
        }
        cout << endl;
    }
    return 0;
}
