//https://www.codechef.com/problems/P5169
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a, b;
        long long l = 0;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            l = max(l, (ll)x);
            if (x >= 0) {
                a.push_back(x);
            } else {
                b.push_back(x);
            }
        }
        long long r = 1e16, ans = 1e16;
        while (l <= r) {
            long long mid = (l + r) / 2;
            int i = 0, j = 0;
            long long sum = 0, mn = 0;
            bool can = true;
            while (i < a.size()) {
                long long val = sum + a[i] - mn;
                if (val <= mid) {
                    sum += a[i];
                    i++;
                } else {
                    if (j < b.size()) {
                        sum += b[j];
                        mn = min(mn, sum);
                        j++;
                    } else {
                        can = false;
                        break;
                    }
                }
            }
            if (can) {
                ans = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
