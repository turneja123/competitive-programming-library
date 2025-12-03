//https://codeforces.com/contest/713/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int INF = 1e9;

int main() {
    IOS;
    int n;
    cin >> n;
    ll ans = 0;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] += INF - i;
        ans += a[i];
    }
    multiset<int> st;
    for (int i = 0; i < n; i++) {
        st.insert(a[i]);
        auto it = st.end();
        it--;
        st.erase(it);
        st.insert(a[i]);
    }
    int slope = n, last = 0;
    for (auto x : st) {
        ans -= (ll)slope * (x - last);
        last = x;
        slope--;
    }
    cout << ans;

    return 0;
}
