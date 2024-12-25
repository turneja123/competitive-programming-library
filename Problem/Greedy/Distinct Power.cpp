//https://www.codechef.com/START166A/problems/DPOWER
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 3e5 + 5;

int a[N];
pair<int, int> compr[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            compr[i] = make_pair(a[i], i);
        }
        sort(compr, compr + n);
        int m = 0;
        for (int i = 0; i < n; i++) {
            if (i > 0 && compr[i].first > compr[i - 1].first) {
                m++;
            }
            a[compr[i].second] = m;
        }
        m++;
        for (int i = 0; i < n; i++) {
            a[i] = n - a[i];
        }
        int ans = n;
        for (int i = 1; i < n; i++) {
            if (abs(a[i] - a[i - 1]) == 1) {
                ans--;
            }
        }
        cout << ans << endl;

    }

    return 0;
}
