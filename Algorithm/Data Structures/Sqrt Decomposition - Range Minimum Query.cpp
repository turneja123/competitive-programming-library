//solution for https://cses.fi/problemset/task/1647/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    int sqr = sqrt(n);
    if (sqr * sqr != n) {
        sqr++;
    }
    int sz = 0;
    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int b[sqr] = { };
    for (int i = 0; i < sqr; i++) {
        int mn = INT_MAX;
        int j;
        for (j = i * sqr; j < min((i + 1) * sqr, n); j++) {
            mn = min(mn, a[j]);
        }
        b[i] = mn;
        if (j == n) {
            sz = i;
            break;
        }
    }
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        int bl = l / sqr;
        int br = r / sqr;
        int sol = INT_MAX;
        if (bl == br || bl == br - 1) {
            for (int i = l; i <= r; i++) {
                sol = min(sol, a[i]);
            }
            cout << sol << endl;
        } else {
            for (int i = l; i < sqr * (bl + 1); i++) {
                sol = min(sol, a[i]);
            }
            for (int i = bl + 1; i < br; i++) {
                sol = min(sol, b[i]);
            }
            for (int i = sqr * br; i <= r; i++) {
                sol = min(sol, a[i]);
            }
            cout << sol << endl;
        }
    }
    return 0;
}
