//https://codeforces.com/contest/865/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);


int main() {
    IOS;
    int n;
    cin >> n;
    ll ans = 0;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    multiset<int> st;
    for (int i = 0; i < n; i++) {
        ans += a[i];
        st.insert(a[i]);
        st.insert(a[i]);
        ans -= *st.begin();
        st.erase(st.begin());
    }
    cout << ans;

    return 0;
}
