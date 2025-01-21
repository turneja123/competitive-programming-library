//https://codeforces.com/contest/2061/problem/B
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        tuple<int, int, int, int> ans;
        get<0>(ans) = -1;
        for (int i = 2; i < n - 1; i++) {
            if (a[i] == a[i + 1]) {
                ans = make_tuple(a[i - 2], a[i - 1], a[i], a[i + 1]);
                break;
            }
        }
        if (a[1] == a[2]) {
            if (a[0] + a[1] + a[2] > a[3]) {
                ans = make_tuple(a[0], a[1], a[2], a[3]);
            }
            for (int i = 3; i < n - 1; i++) {
                if (a[1] + a[2] + a[i] > a[i + 1]) {
                    ans = make_tuple(a[1], a[2], a[i], a[i + 1]);
                }
            }
        }
        if (a[0] == a[1]) {
            for (int i = 2; i < n - 1; i++) {
                if (a[0] + a[1] + a[i] > a[i + 1]) {
                    ans = make_tuple(a[0], a[1], a[i], a[i + 1]);
                }
            }
        }
        auto [x, y, z, p] = ans;
        if (x == -1) {
            cout << -1 << endl;
        } else {
            cout << x << " " << y << " " << z << " " << p << endl;
        }
    }
    return 0;
}
