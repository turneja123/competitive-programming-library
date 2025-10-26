//https://codeforces.com/contest/2156/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int freq[N];
int pref[N];
int a[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            freq[a[i]]++;
        }
        for (int i = 1; i <= n; i++) {
            pref[i] = pref[i - 1] + freq[i];
        }
        int ans = 1;
        for (int i = 2; i <= n; i++) {
            int need = pref[min(n, 4 * i - 1)];
            if (3 * i <= n) {
                need -= freq[3 * i];
            }
            if (2 * i <= n) {
                need -= freq[2 * i];
            }
            if (i <= n) {
                need -= freq[i];
            }

            if (need <= k) {
                ans = i;
            }
        }
        cout << ans << endl;
        for (int i = 1; i <= n; i++) {
            freq[i] = 0;
            pref[i] = 0;
        }
    }

    return 0;
}
