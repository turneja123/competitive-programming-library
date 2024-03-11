#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

int a[N];

int main() {
    IOS;
    int n, m, shift = 0;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        int q, x;
        cin >> q >> x;
        x %= n;
        x--;
        if (q == 1) {
            if (shift <= x) {
                shift = (n - 1) - (x - shift);
            } else {
                shift = shift - (x + 1);
            }
        } else {
            int ans = x - shift;
            if (ans < 0) {
                ans += n;
            }
            cout << a[ans] << endl;
        }
    }
    return 0;
}
