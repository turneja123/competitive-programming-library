//https://www.codechef.com/problems/GCDXOR
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
vector<int> bad;

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        bad.clear();
        int n, x;
        cin >> n >> x;
        bool can = true; bool can1 = true;
        int k = -1;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (a[i] != x) {
                can = false;
                if (k == -1) {
                    k = a[i];
                } else if (k != a[i]) {
                    can1 = false;
                }
                bad.push_back(i);
            }
        }
        if (can) {
            cout << 0 << endl;
            continue;
        }
        for (int i = 1; i < bad.size(); i++) {
            if (bad[i] - bad[i - 1] > 1) {
                can1 = false;
            }
        }
        int l = bad[0], r = bad[bad.size() - 1];
        int g = a[l];
        for (int i = l; i <= r; i++) {
            g = __gcd(g, a[i]);
        }
        if (g % x == 0) {
            can1 = true;
        }
        if (can1) {
            cout << 1 << endl;
        } else {
            cout << 2 << endl;
        }
    }

    return 0;
}
