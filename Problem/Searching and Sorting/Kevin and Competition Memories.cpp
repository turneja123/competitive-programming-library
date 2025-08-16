//https://codeforces.com/contest/2048/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

int a[N];
int b[N];

int main() {
	IOS;
	int t;
	cin >> t;
	while (t--) {
        int n, m;
        cin >> n >> m;
        int v;
        cin >> v;
        n--;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        if (n) {
            sort(a, a + n);
        }
        for (int i = 0; i < m; i++) {
            cin >> b[i];
        }
        sort(b, b + m);
        int s = upper_bound(b, b + m, v) - b;

        for (int k = 1; k <= m; k++) {
            if (n == 0 || s >= m - m % k) {
                cout << m / k << " ";
                continue;
            }
            ll ans = m / k;
            int skip = m % k;
            int j = (m - (s + skip) - 1) % k + 1;
            for (int i = m - j; i >= s + skip; i -= k) {
                int x = b[i];
                int j = lower_bound(a, a + n, x) - a;
                ans += (n - j);
            }
            cout << ans << " ";
        }
        cout << endl;
	}
	return 0;
}
