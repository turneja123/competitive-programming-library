//https://codeforces.com/contest/2229/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

vector<pair<int, int>> rle(vector<int> &a) {
    int n = a.size();
    vector<pair<int, int>> v;
    int last = -1, ct = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] != last) {
            if (ct) {
                v.push_back({last, ct});
            }
            last = a[i];
            ct = 1;
        } else {
            ct++;
        }
    }
    v.push_back({last, ct});
    return v;
}

int main() {
    IOS;

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n), b(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }
        int l = 1, r = 2 * n, ans = 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            vector<int> c;
            for (int i = 0; i < n; i++) {
                int x = a[i] >= mid, y = b[i] >= mid;
                if (x + y == 0) {
                    c.push_back(-1);
                } else if (x + y == 2) {
                    c.push_back(1);
                }
            }
            auto v = rle(c);
            int bal = 0;
            for (auto [x, f] : v) {
                if (x == -1) {
                    bal--;
                } else {
                    bal += f;
                }
            }
            if (bal > 0) {
                ans = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        cout << ans << endl;
    }

    return 0;
}
