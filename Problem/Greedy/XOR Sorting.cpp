//https://www.codechef.com/problems/XORSRT
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
        int n, k;
        cin >> n >> k;
        int can = 0;
        if (k != 0) {
            for (int i = 1; i <= n; i++) {
                int j = k ^ i;
                if (j != 0 && j <= n) {
                    can = 1;
                    vector<int> l, r;
                    int x = min(i, j), y = max(i, j);
                    for (int z = x; z <= y; z++) {
                        if (z == y || z == x) {
                            continue;
                        }
                        int gx = z ^ x, gy = z ^ y;
                        if (gx <= gy) {
                            l.push_back(z);
                        } else {
                            r.push_back(z);
                        }
                    }
                    for (int z = 1; z < x; z++) {
                        cout << z << " ";
                    }
                    for (int z : l) {
                        cout << z << " ";
                    }
                    cout << y << " " << x << " ";
                    for (int z : r) {
                        cout << z << " ";
                    }
                    for (int z = y + 1; z <= n; z++) {
                        cout << z << " ";
                    }
                    cout << endl;
                    break;
                }
            }
        } else {
            for (int i = 1; i <= n; i++) {
                cout << i << " ";
            }
            cout << endl;
            can = 1;
        }
        if (!can) {
            cout << -1 << endl;
        }
    }
    return 0;
}
