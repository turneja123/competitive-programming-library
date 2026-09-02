//https://codeforces.com/contest/2124/problem/E
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
        vector<ll> a(n), pref(n);
        ll mx = 0;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            mx = max(mx, a[i]);
            pref[i] = (i == 0 ? 0 : pref[i - 1]) + a[i];
        }
        if (pref.back() % 2 == 1 || mx > pref.back() / 2) {
            cout << -1 << endl;
            continue;
        }
        int ok = 0;
        for (int i = 0; i < n; i++) {
            if (pref[i] == pref.back() / 2) {
                ok = 1;
            }
        }
        if (ok) {
            cout << 1 << endl;
            for (int i = 0; i < n; i++) {
                cout << a[i] << " ";
            }
            cout << endl;
            continue;
        }
        cout << 2 << endl;

        int j = 0;
        while (pref[j] <= pref.back() / 2) {
            j++;
        }
        vector<ll> ans(n, 0);
        for (int i = 0; i < j; i++) {
            ans[i] = a[i];
        }
        ans[j] = pref.back() / 2 - (pref.back() - pref[j]);
        ll need = pref.back() - a[j] - pref.back() / 2;
        for (int i = j + 1; i < n; i++) {
            ans[i] = min(a[i], need);
            need -= min(a[i], need);
        }
        for (int i = 0; i < n; i++) {
            cout << ans[i] << " ";
            a[i] -= ans[i];
        }
        cout << endl;
        for (int i = 0; i < n; i++) {
            cout << a[i] << " ";
        }
        cout << endl;
    }
    return 0;
}
