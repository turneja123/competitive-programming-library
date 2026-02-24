//https://codeforces.com/contest/2201/problem/F2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e6 + 5;

int X[N];
int Y[N];
int pref[N];


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        ll ans = 0;
        for (int i = 0; i < q; i++) {
            int x, y;
            cin >> x >> y;
            X[x]++;
            ans += pref[X[x]];
            pref[X[x]]++;
            ans -= Y[y];
            Y[y]++;
            if (!ans) {
                cout << "YES" << endl;
            } else {
                cout << "NO" << endl;
            }
        }
        for (int i = 0; i <= n; i++) {
            pref[i] = 0, X[i] = 0, Y[i] = 0;
        }
    }


    return 0;
}
