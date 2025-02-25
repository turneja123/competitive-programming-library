//https://codeforces.com/contest/2069/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        int n = s.size() / 2;
        string a = "", b = "";
        vector<int> diff(26, 0);

        for (int i = 0; i < n; i++) {
            a += s[i];
            diff[s[i] - 'a']++;
        }
        for (int i = n; i < 2 * n; i++) {
            b += s[i];
            diff[s[i] - 'a']--;
        }
        int i = n - 1;
        int bad = 0;
        for (int k = 0; k < 26; k++) {
            if (diff[k] > 0) {
                bad++;
            }
        }
        while (bad) {
            if (diff[a[i] - 'a'] > 0) {
                diff[a[i] - 'a'] -= 2;
                if (diff[a[i] - 'a'] == 0) {
                    bad--;
                }
            }
            i--;
        }
        int j = 0;
        bad = 0;
        for (int k = 0; k < 26; k++) {
            if (diff[k] < 0) {
                bad++;
            }
        }
        while (bad) {
            if (diff[b[j] - 'a'] < 0) {
                diff[b[j] - 'a'] += 2;
                if (diff[b[j] - 'a'] == 0) {
                    bad--;
                }
            }
            j++;
        }
        int ans = 0;
        if (i == n - 1) {
            int l = n, r = -1;
            for (int k = 0; k < n; k++) {
                if (a[k] != b[n - 1 - k]) {
                    l = min(l, k);
                    r = max(r, k);
                }
            }
            if (l <= r) {
                ans += r - l + 1;
            }
            cout << ans << endl;
            continue;
        }

        if (n - 1 - i > j) {
            ans = j;
            int l = n, r = n - 1;
            for (int k = 0; k <= i; k++) {
                if (a[k] != b[n - 1 - k]) {
                    l = min(l, k);
                }
            }
            if (l <= r) {
                ans += r - l + 1;
            }
            cout << ans << endl;
            continue;
        } else {
            ans = n - 1 - i;
            int l = 0, r = -1;
            for (int k = j; k < n; k++) {
                if (a[n - 1 - k] != b[k]) {
                    r = max(r, k);
                }
            }
            if (l <= r) {
                ans += r - l + 1;
            }
            cout << ans << endl;
        }

    }

    return 0;
}
