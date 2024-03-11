//https://www.spoj.com/problems/HIGHBABA/
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
    for (int k = 1; k <= t; k++) {
        string a, b;
        cin >> a >> b;
        int l = b.size(), r = a.size(), ans = a.size() + 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            bool flag = false;
            int p = 0;
            for (int j = 0; j < mid; j++) {
                if (p < b.size() && a[j] == b[p]) {
                    p++;
                }
            }
            if (p == b.size()) {
                flag = true;
            }

            for (int i = 1; i + mid <= a.size() && !flag; i++) {
                if (a[i - 1] != b[0]) {
                    if (p < b.size() && a[i + mid - 1] == b[p]) {
                        p++;
                    }
                } else {
                    p = 0;
                    for (int j = i; j < i + mid; j++) {
                        if (p < b.size() && a[j] == b[p]) {
                            p++;
                        }
                    }
                }
                if (p == b.size()) {
                    flag = true;
                }
            }
            if (flag) {
                ans = min(ans, mid);
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        cout << "Case " << k << ": " << ((ans == a.size() + 1) ? -1 : ans) << endl;
    }
    return 0;
}
