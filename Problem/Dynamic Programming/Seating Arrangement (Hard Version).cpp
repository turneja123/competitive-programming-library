//https://codeforces.com/contest/2232/problem/C2
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
        int n, x, s;
        cin >> n >> x >> s;
        string S;
        cin >> S;
        multiset<int, greater<int>> st;
        for (int i = 0; i < n; i++) {
            if (S[i] == 'I') {
                st.insert(1);
            } else if (S[i] == 'E') {
                if (!st.empty()) {
                    auto it = st.upper_bound(s);
                    if (it != st.end()) {
                        int y = *it;
                        st.erase(it);
                        st.insert(y + 1);
                    }
                }
            } else {
                if (st.empty()) {
                    st.insert(1);
                } else {
                    auto it = st.upper_bound(s);
                    if (it != st.end()) {
                        int y = *it;
                        st.erase(it);
                        st.insert(y + 1);
                        st.insert(0);
                    } else {
                        st.insert(1);
                    }
                }
            }
        }
        int ans = 0;
        int j = 0;
        while (st.size() && j < x) {
            ans += *st.begin();
            st.erase(st.begin());
            j++;
        }
        cout << ans << endl;
    }
    return 0;
}
