//https://codeforces.com/contest/2229/problem/C2
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
        int n;
        cin >> n;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        ll best = 0; int j = -1;
        ll sum = 0;
        for (int i = 0; i < n; i++) {

            if (a[i] > 0 && sum - a[i] > best) {
                best = sum - a[i];
                j = i;
            }
            if (a[i] < 0) {
                sum += abs(a[i]);
            }
        }
        if (j == -1) {
            cout << 0 << endl << endl;
            continue;
        }
        vector<int> ans;
        int f = 1;
        for (int i = j - 1; i >= 0; i--) {
            if (f * a[i] > 0) {
                ans.push_back(i);
                f *= -1;
            }
        }
        ans.push_back(j);
        cout << ans.size() << endl;
        for (int i : ans) {
            cout << i + 1 << " ";
        }
        cout << endl;

    }

    return 0;
}
