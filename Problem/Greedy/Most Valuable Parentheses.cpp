//https://atcoder.jp/contests/abc407/tasks/abc407_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 4e5 + 5;

int a[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        n *= 2;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        long long ans = a[0];
        multiset<int> st;
        st.insert(a[1]);
        for (int i = 2; i < n; i += 2) {
            if (*st.rbegin() > a[i]) {
                auto it = st.end();
                it--;
                ans += *it;
                st.erase(it);
                st.insert(a[i]);
                st.insert(a[i + 1]);
            } else {
                ans += a[i];
                st.insert(a[i + 1]);
            }
        }
        cout << ans << endl;
    }
    return 0;
}
