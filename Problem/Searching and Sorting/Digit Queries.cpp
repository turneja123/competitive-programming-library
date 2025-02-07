//https://cses.fi/problemset/task/2431/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

int main() {
    IOS;
    int q;
    cin >> q;
    while (q--) {
        long long k;
        cin >> k;
        long long l = 1, r = 1e17;
        long long spl = 0, rem = 0;
        while (l <= r) {
            long long mid = (l + r) / 2;
            long long pw = 1;
            long long ct = 0;
            for (int i = 0, j = 1; i < 20; i++, j++) {
                long long nx = min(pw * 10, mid);
                ct += (nx - pw) * j;
                pw *= 10;
                if (pw > mid) {
                    break;
                }
            }
            if (ct < k) {
                spl = mid;
                rem = ct;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        string s = to_string(spl);
        int i = k - rem - 1;
        cout << s[i] << endl;
    }
    return 0;
}
