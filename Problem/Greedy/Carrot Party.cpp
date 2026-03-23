//https://mitit.org/Contest/ViewProblem/carrot-party?cid=qualification-2026-1
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


int simul(int a, int b, int c) {
    if (b > a) {
        return b + min(a, c);
    }
    return a + min(b, c);

}



int main() {
    IOS;

    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        vector<int> a(n);
        multiset<int> l, r;
        ll sl = 0, sr = 0, s = 0;

        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (i < n / 2) {
                l.insert(a[i]);
                sl += a[i];
            } else if (!(n % 2 == 1 && i == n / 2)) {
                r.insert(a[i]);
                sr += a[i];
            }
            s += a[i];
        }
        ll ans = 0;
        if (n % 2 == 0) {
            ans = sl - *l.begin() + max(*l.begin(), *r.begin());
        } else {
            ans = sl - *l.begin() + simul(*l.begin(), a[n / 2], *r.begin());

        }
        cout << ans << " " << s - ans << endl;
        for (int i = 0; i < q; i++) {
            int j, x;
            cin >> j >> x;
            j--;
            s -= a[j];
            if (j < n / 2) {
                l.erase(l.find(a[j]));
                sl -= a[j];
                a[j] = x;

                l.insert(a[j]);
                sl += a[j];
            } else if (!(n % 2 == 1 && j == n / 2)) {
                r.erase(r.find(a[j]));
                sr -= a[j];
                a[j] = x;

                r.insert(a[j]);
                sr += a[j];
            } else {
                a[j] = x;
            }
            s += a[j];
            ll ans = 0;
            if (n % 2 == 0) {
                ans = sl - *l.begin() + max(*l.begin(), *r.begin());
            } else {
                ans = sl - *l.begin() + simul(*l.begin(), a[n / 2], *r.begin());

            }
            cout << ans << " " << s - ans << endl;
        }

    }


    return 0;
}
