//https://codeforces.com/contest/2161/problem/C
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
        int n, x;
        cin >> n >> x;
        vector<int> a(n);
        multiset<int> st;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            st.insert(a[i]);
        }
        ll ans = 0, ansm = 0;
        vector<int> v;
        while (st.size()) {
            auto it = st.begin();
            if (ansm + *it < x) {
                ansm += *it;
                v.push_back(*it);
                st.erase(it);
            } else {
                auto it = st.end();
                it--;
                ans += *it;
                ansm = (ansm + *it) % x;
                v.push_back(*it);
                st.erase(it);
            }
        }

        cout << ans << endl;
        for (int y : v) {
            cout << y << " ";
        }
        cout << endl;
    }
    return 0;
}
