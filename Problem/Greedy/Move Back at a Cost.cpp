//https://codeforces.com/contest/2047/problem/D
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
        vector<bool> b(n, false);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        int mn = 2e9;
        for (int i = n - 1; i >= 0; i--) {
            mn = min(mn, a[i]);
            if (a[i] > mn) {
                b[i] = true;
            }
        }
        mn = 2e9;
        for (int i = 0; i < n; i++) {
            if (b[i]) {
                mn = min(mn, a[i]);
            }
            if (a[i] > mn + 1) {
                b[i] = true;
            }
        }
        for (int i = 0; i < n; i++) {
            if (b[i]) {
                a[i]++;
            }
        }
        sort(a.begin(), a.end());
        for (int x : a) {
            cout << x << " ";
        }
        cout << endl;
    }

    return 0;
}
