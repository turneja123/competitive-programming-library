//https://codeforces.com/contest/2170/problem/C
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
        int n; ll k;
        cin >> n >> k;
        multiset<ll> st;
        for (int i = 0; i < n; i++) {
            ll x;
            cin >> x;
            st.insert((k - x) / (x + 1));
        }
        vector<ll> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        reverse(a.begin(), a.end());
        int ans = 0;
        for (ll x : a) {
            auto it = st.lower_bound(x);
            if (it != st.end()) {
                ans++;
                st.erase(it);
            }
        }
        cout << ans << endl;
    }


    return 0;
}
