//https://www.codechef.com/problems/ANTIPALQ
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 2e5 + 5;

int a[N];
int pref[N][3];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            a[i]--;
            for (int j = 0; j < 3; j++) {
                pref[i][j] = ((i == 0) ? 0 : pref[i - 1][j]);
            }
            pref[i][a[i]]++;
        }
        for (int i = 0; i < q; i++) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            if ((r - l + 1) % 2 == 1) {
                cout << "No" << endl;
                continue;
            }
            vector<int> v;
            for (int j = 0; j < 3; j++) {
                int ct = pref[r][j] - ((l == 0) ? 0 : pref[l - 1][j]);
                v.push_back(ct);
            }
            sort(v.begin(), v.end());
            if (v[2] > (r - l + 1) / 2) {
                cout << "No" << endl;
                continue;
            }
            if (v[0] > (r - l + 1) / 2 - v[1]) {
                cout << "No" << endl;
                continue;
            }
            cout << "Yes" << endl;
        }

    }
    return 0;
}
