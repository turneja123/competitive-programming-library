//https://codeforces.com/contest/2008/problem/H
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

int a[N];
int freq[N];
int pref[N];
int ans[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            freq[a[i]]++;
        }
        for (int i = 1; i <= n; i++) {
            pref[i] = pref[i - 1] + freq[i];
        }
        int pos = ((n % 2 == 0) ? (n + 2) / 2 : (n + 1) / 2);
        for (int i = 2; i <= n; i++) {
            int l = 0, r = i - 1;
            while (l <= r) {
                int mid = (l + r) / 2, ct = 0;
                for (int j = 0; j <= n; j += i) {
                    ct += pref[min(n, j + mid)] - pref[max(0, j - 1)];
                }
                if (ct >= pos) {
                    ans[i] = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
        }
        for (int i = 0; i < q; i++) {
            int x;
            cin >> x;
            cout << ans[x] << " ";
        }
        for (int i = 1; i <= n; i++) {
            freq[i] = 0;
            pref[i] = 0;
        }
        cout << endl;
    }
    return 0;
}
