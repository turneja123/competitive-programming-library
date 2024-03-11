//solution for https://codeforces.com/contest/1475/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int p[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            cin >> p[i];
        }
        vector<int> a;
        vector<int> b;
        for (int i = 0; i < n; i++) {
            int k;
            cin >> k;
            if (k == 1) {
                a.push_back(p[i]);
            } else {
                b.push_back(p[i]);
            }
        }
        sort(a.begin(), a.end(), greater<int>());
        sort(b.begin(), b.end(), greater<int>());
        int cur = 0;
        int sum = 0;
        int ia = 0, ib = 0;
        while (ia < a.size() && sum < m) {
            sum += a[ia];
            ia++;
            cur++;
        }
        while (ib < b.size() && sum < m) {
            sum += b[ib];
            ib++;
            cur += 2;
        }
        if (sum < m) {
            cout << -1 << endl;
            continue;
        }
        int ans = cur;
        while (ia > 0) {
            ia--;
            sum -= a[ia];
            cur--;
            while (ib < b.size() && sum < m) {
                sum += b[ib];
                ib++;
                cur += 2;
            }
            if (sum >= m) {
                ans = min(ans, cur);
            }
        }
        cout << ans << endl;
    }

    return 0;
}
