//https://codeforces.com/contest/2239/problem/A
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
        int x = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            x ^= a[i];
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            int c = x ^ a[i];
            if (c < a[i]) {
                ans++;
            }
        }
        if (x == 0) {
            ans++;
        }
        cout << (n == 1 ? 0 : ans) << endl;

    }

    return 0;
}
