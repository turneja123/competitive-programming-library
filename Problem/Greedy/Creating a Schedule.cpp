//https://codeforces.com/contest/2111/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

int a[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < m; i++) {
            cin >> a[i];
        }
        sort(a, a + m);
        for (int i = 0; i < n; i++) {
            vector<int> v{a[i / 2], a[m - 1 - i / 2], a[i / 2], a[m - 1 - i / 2], a[i / 2], a[m - 1 - i / 2]};
            if (i % 2 == 1) {
                reverse(v.begin(), v.end());
            }
            for (int x : v) {
                cout << x << " ";
            }
            cout << endl;
        }
    }
    return 0;
}
