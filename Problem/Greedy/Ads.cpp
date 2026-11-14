//https://qoj.ac/contest/1964/problem/10312
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
        multiset<int> st;
        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            st.insert(a);
        }
        int ans = 0;
        int pairs = 0;
        while (st.size() > 1) {
            int x = *st.begin();
            auto it = st.lower_bound(k - x);
            if (it == st.begin()) {
                break;
            }
            it--;
            if (it == st.begin()) {
                break;
            }
            pairs++;
            st.erase(it);
            st.erase(st.begin());
        }
        while (pairs > 0 && st.size()) {
            ans++;
            pairs--;
            auto it = st.end();
            it--;
            st.erase(it);
        }
        while (st.size() > 1 && *st.begin() < k) {
            st.erase(st.begin());
            auto it = st.end();
            it--;
            st.erase(it);
            ans++;
        }
        ans += st.size();
        int rem = 2 * pairs;
        ans += (rem + 2) / 3;
        cout << ans - 1 << endl;

    }


    return 0;
}
