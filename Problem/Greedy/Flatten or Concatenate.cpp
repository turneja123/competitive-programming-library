//https://codeforces.com/contest/2178/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

//#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int L = 1, R = n;
        ll all;
        cout << "? " << L << " " << R << endl;
        cin >> all;
        while (L != R) {
            int l = L, r = R; int spl = L; ll lf_s, rt_s;
            while (l <= r) {
                int mid = (l + r) / 2;
                ll lf;
                cout << "? " << L << " " << mid << endl;
                cin >> lf;
                if (lf <= all - lf) {
                    l = mid + 1;
                    spl = mid;
                    lf_s = lf;
                    rt_s = all - lf;
                } else {
                    r = mid - 1;
                }
            }
            if (spl - L + 1 <= R - spl) {
                R = spl;
                all = lf_s;
            } else {
                L = spl + 1;
                all = rt_s;
            }
        }
        cout << "? " << L << " " << L << endl;
        cin >> all;

        cout << "! " << all << endl;
    }
    return 0;
}
