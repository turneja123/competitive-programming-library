//https://codeforces.com/contest/1942/problem/C2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


bool comp(int a, int b) {
    if (a % 2 != b % 2) {
        return a % 2 == 0;
    }
    return a < b;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, x, y;
        cin >> n >> x >> y;
        vector<int> a(x);
        for (int i = 0; i < x; i++) {
            cin >> a[i];
            a[i]--;
        }
        sort(a.begin(), a.end());
        int ans = x - 2;
        vector<int> diff;
        for (int i = 1; i < x; i++) {
            if (a[i] - a[i - 1] == 2) {
                ans++;
            }
            diff.push_back({a[i] - a[i - 1]});
        }
        if ((a.back() + 2) % n == a[0]) {
            ans++;
        }
        diff.push_back(a[0] + n - a.back());
        sort(diff.begin(), diff.end(), comp);
        for (int i = 0; i < diff.size(); i++) {
            if (diff[i] <= 2) {
                continue;
            }
            int ct = (diff[i] - 1) / 2;
            int d = min(ct, y);
            ans += 2 * min(ct, y);
            ct -= d;
            y -= d;
            if (diff[i] % 2 == 0 && ct == 0) {
                ans++;
            }
            if (y == 0) {
                break;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
