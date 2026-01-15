//https://dmoj.ca/problem/aaaa1p3
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


int main() {
    IOS;
    int n, t;
    cin >> t >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    if (t == 1) {
        vector<int> diff(n + 2, 0);
        for (int i = 0; i < n; i++) {
            diff[a[i] + 1]--;
        }

        for (int i = 0; i < n - 1; i++) {
            diff[min(a[i], a[i + 1]) + 1]++;
        }
        int ans = 1;
        for (int i = 1; i <= n; i++) {
            ans += diff[i];
            cout << ans << " ";
        }
    } else {
        vector<int> v(n, 0);
        int x = 0, y = 1, ans = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (a[i] > ans) {
                for (int j = 0; j < a[i] - ans; j++) {
                    if (x >= n) {
                        cout << -1;
                        return 0;
                    }
                    v[x] = i + 1;
                    x += 2;
                }
                ans = a[i];
            } else if (a[i] < ans) {
                if (a[i] == 0) {
                    cout << -1;
                    return 0;
                }
                for (int j = 0; j < ans - a[i]; j++) {
                    if (y >= n) {
                        cout << -1;
                        return 0;
                    }
                    v[y] = i + 1;
                    y += 2;
                }
                ans = a[i];
            }
        }
        for (int i = 0; i < n; i++) {
            cout << v[i] << " ";
        }
    }

    return 0;
}
