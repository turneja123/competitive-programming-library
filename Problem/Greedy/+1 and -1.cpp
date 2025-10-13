//https://atcoder.jp/contests/arc185/tasks/arc185_b
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        int need = a[0]; ll sum = a[0], suf = 0;
        for (int i = 1; i < n; i++) {
            sum += a[i];
            if (a[i] < need) {
                suf += need - a[i];
            } else {
                if (suf >= a[i] - need) {
                    suf -= a[i] - need;
                } else {
                    suf = 0;
                    need = (sum + i) / (i + 1);
                }
            }
        }
        if (suf == 0) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
    return 0;
}
