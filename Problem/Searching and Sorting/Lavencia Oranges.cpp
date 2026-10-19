//https://codeforces.com/contest/2273/problem/A
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
        int l = 1, r = n, spl;
        vector<int> ans;
        while (l <= r) {
            int mid = (l + r) / 2;
            vector<int> cur(n, 0);
            int ptr = 0;
            int ptr_group = 0;
            for (int i = n; i >= 1; i--) {
                int rem = n - ptr;
                int take_groups = min(mid / i, rem / i);
                for (int j = 0; j < take_groups; j++) {
                    for (int k = 0; k < i; k++) {
                        cur[ptr++] = ptr_group;
                    }
                    ptr_group++;
                }
            }
            if (ptr == n) {
                ans = cur;
                spl = mid;
                r = mid - 1;
            } else {
                l = mid + 1;
            }
        }
        cout << spl << endl;
        for (int i = 0; i < n; i++) {
            cout << ans[i] + 1 << " ";
        }
        cout << endl;
    }

    return 0;
}
