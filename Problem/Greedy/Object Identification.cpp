//https://codeforces.com/contest/2066/problem/A
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

//#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

pair<int, int> a[N];
int deg[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> a[i].first;
            a[i].second = i;
            deg[a[i].first]++;
        }
        int f = 0;
        for (int i = 1; i <= n; i++) {
            if (deg[i] == 0) {
                int j = 1;
                if (i == j) {
                    j = 2;
                }
                cout << "? " << i << " " << j << endl;
                int x;
                cin >> x;
                if (x == 0) {
                    cout << "! A" << endl;
                } else {
                    cout << "! B" << endl;
                }
                f = 1;
                break;
            }
        }
        if (!f) {
            sort(a + 1, a + n + 1);
            cout << "? " << a[1].second << " " << a[n].second << endl;
            int x;
            cin >> x;
            if (x < n - 1) {
                cout << "! A" << endl;
            } else if (x > n - 1) {
                cout << "! B" << endl;
            } else {
                cout << "? " << a[n].second << " " << a[1].second << endl;
                cin >> x;
                if (x < n - 1) {
                    cout << "! A" << endl;
                } else {
                    cout << "! B" << endl;
                }
            }
        }
        for (int i = 1; i <= n; i++) {
            deg[i] = 0;
        }
    }

    return 0;
}
