//https://codeforces.com/contest/2110/problem/F
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
        set<int> st;
        int ans = 0, n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            if (st.empty()) {
                st.insert(x);
                cout << ans << " ";
                continue;
            }
            auto it = st.lower_bound(x);
            if (it != st.end() && *it == x) {
                cout << ans << " ";
                continue;
            }
            if (*st.rbegin() <= x / 2) {
                for (int y : st) {
                    ans = max(ans, x % y + y % x);
                }
            }
            if (*st.rbegin() < 2 * x) {
                ans = max(ans, *st.rbegin());
            }
            if (x < *st.rbegin() * 2) {
                ans = max(ans, x);
            }
            ans = max(ans, x % (*st.rbegin()) + (*st.rbegin()) % x);
            st.insert(x);
            cout << ans << " ";
        }
        cout << endl;
    }
    return 0;
}
