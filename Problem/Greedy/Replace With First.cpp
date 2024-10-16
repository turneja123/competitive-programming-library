//https://www.codechef.com/problems/STRFIRSTCHAR
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        string a, b;
        cin >> a >> b;
        if (a == b) {
            cout << 0 << endl;
            continue;
        }
        if (a.size() > b.size()) {
            swap(a, b);
        }
        if (a[0] != b[0]) {
            cout << -1 << endl;
            continue;
        }
        n = a.size(), m = b.size();
        int l = 0;
        for (; l < n; l++) {
            if (a[l] != b[l]) {
                break;
            }
        }
        int r = n - 1, ind = m - 1;
        for (; r >= 0; r--, ind--) {
            if (a[r] != b[ind]) {
                break;
            }
        }
        if (l > r) {
            cout << 1 << endl;
        } else {
            cout << 2 << endl;
        }
    }
    return 0;
}
