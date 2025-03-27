//https://codeforces.com/contest/2085/problem/D
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
        vector<int> a(n);
        multiset<int> st;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        long long ans = 0;
        int ct = 0;
        for (int i = n - 1; i >= 0; i--) {
            if (ct >= k) {
                ans += a[i];
                st.insert(a[i]);
                ct -= k;
            } else {
                if (st.size() && a[i] > *st.begin()) {
                    ans += (a[i] - *st.begin());
                    st.erase(st.begin());
                    st.insert(a[i]);
                }
                ct++;
            }
        }
        cout << ans << endl;
    }
    return 0;
}
