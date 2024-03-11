//https://www.spoj.com/problems/STACKOFBOXES/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const long long N = 100005;

long long arr[N];
long long pref[N];
long long n, a, r, m;

long long best = 1e18;

int main() {
    IOS;
    cin >> n >> a >> r >> m;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    sort(arr, arr + n);
    pref[0] = arr[0];
    for (long long i = 1; i < n; i++) {
        pref[i] = pref[i - 1] + arr[i];
    }
    if (arr[0] == arr[n - 1]) {
        cout << 0 << endl;
        return 0;
    }
    for (long long i = 0; i < n;) {
        long long lf = i;
        while (arr[lf] == arr[i]) {
            i++;
        }
        if (i == n) {
            break;
        }

        best = min(best, (i * arr[lf] - pref[i - 1]) * a + (pref[n - 1] - pref[i - 1] - arr[lf] * (n - i)) * r);
        best = min(best, (i * arr[i] - pref[i - 1]) * a + (pref[n - 1] - pref[i - 1] - arr[i] * (n - i)) * r);

        long long lval = arr[lf];
        long long rval = arr[i];
        while (lval <= rval) {
            long long mid = (lval + rval) / 2;

            long long ldif = i * mid - pref[i - 1];
            long long rdif = (pref[n - 1] - pref[i - 1]) - (n - i) * mid;
            long long dif = min(ldif, rdif);

            best = min(best, dif * m + (i * mid - pref[i - 1] - dif) * a + (pref[n - 1] - pref[i - 1] - mid * (n - i) - dif) * r);

            if (rdif >= ldif) {
                lval = mid + 1;
            } else {
                rval = mid - 1;
            }
        }
    }
    cout << best << endl;
}
