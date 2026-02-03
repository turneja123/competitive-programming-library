//https://ocpc2026w.eolymp.space/en/compete/rofq4l68mt2dp1esn9ncjjllcg/problem/2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

int id[5];

int main() {
    IOS;
    id[0] = 0, id[1] = 2, id[2] = 4, id[3] = 1, id[4] = 3;
    int t;
    cin >> t;
    while (t--) {
        int a, b;
        cin >> a >> b;
        int f = 0;
        if (a > b) {
            swap(a, b);
            f = 1;
        }
        a *= 50, b *= 50;
        if (4 * a < b) {
            cout << -1 << endl;
            continue;
        }
        int sz = a + b;
        int n = sz / 5;
        vector<vector<int>> ans(5, vector<int>(n));
        int base = sz / 5, need = a - base;

        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < n; j++) {
                if (j % 5 == id[i]) {
                    ans[i][j] = 0;
                } else {
                    ans[i][j] = 1;
                }
            }
        }

        for (int i = 0; i < 5; i++) {
            for (int j = id[i] % 2; j < n && need; j += 2) {
                if (ans[i][j] == 1) {
                    ans[i][j] = 0;
                    need--;
                }
            }
        }
        cout << 5 << " " << n << endl;
        for (int i = 0; i < 5; i++) {
            for (int j = 0; j < n; j++) {
                int cur = ans[i][j] ^ f;
                if (cur == 0) {
                    cout << '.';
                } else {
                    cout << '@';
                }
            }
            cout << endl;
        }
    }



    return 0;
}
