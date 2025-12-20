//https://codeforces.com/contest/2173/problem/F
#pragma GCC target ("avx2")
#pragma GCC optimize ("O3")
#pragma GCC optimize ("unroll-loops")
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 150005;

int a[N];
ll pref[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;

        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            pref[i] = pref[i - 1] + a[i];
        }
        for (int i = 1; i <= q; i++) {
            int lq, rq, x;
            cin >> lq >> rq >> x;

            int l = lq, r = rq, spl = -1;
            while (l <= r) {
                int mid = (l + r) / 2;
                ll s = pref[mid] - pref[lq - 1];
                if (s >= x) {
                    spl = mid;
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            }
            if (spl == -1) {
                cout << 0 << " " << pref[rq] - pref[lq - 1] << endl;
                continue;
            }
            int ct = 0, sum = 0;
            int k = spl - lq + 1;
            while (1) {
                int l = 1, r = (rq - lq + 1) / k + 3, spl = -1;
                while (l <= r) {
                    int mid = (l + r) / 2;

                    int st = lq + k * (mid - 1), en = st + k - 1;
                    if (en > rq) {
                        r = mid - 1;
                        continue;
                    }
                    ll s = pref[en] - pref[st - 1];
                    if (s >= x) {
                        spl = mid;
                        l = mid + 1;
                    } else {
                        r = mid - 1;
                    }
                }
                if (spl == -1) {
                    break;
                }
                ct += spl;
                lq += k * spl;
                k++;
            }
            while (lq <= rq) {
                int l = lq, r = rq, spl = -1;
                while (l <= r) {
                    int mid = (l + r) / 2;
                    ll s = pref[mid] - pref[lq - 1];
                    if (s >= x) {
                        spl = mid;
                        r = mid - 1;
                    } else {
                        l = mid + 1;
                    }
                }
                ct++;
                if (spl == -1) {
                    ct--;
                    sum = pref[rq] - pref[lq - 1];
                    break;
                } else {
                    lq = spl + 1;
                }
            }
            cout << ct << " " << sum << endl;
        }
    }


    return 0;
}
