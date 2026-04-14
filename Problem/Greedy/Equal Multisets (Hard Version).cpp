//https://codeforces.com/contest/2211/problem/C2
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
        vector<int> a(n), b(n), c(k);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }
        string ans = "YES";
        for (int i = 0; i < k; i++) {
            set<int> st;
            for (int j = i; j < n; j += k) {
                if (a[i] != a[j]) {
                    c[i] = 1;
                }
                if (b[j] != -1) {
                    st.insert(b[j]);
                }
            }
            if (c[i]) {
                for (int j = i; j < n; j += k) {
                    if (a[j] != b[j] && b[j] != -1) {
                        ans = "NO";
                    }
                }
            } else if (st.size() > 1) {
                ans = "NO";
            } else if (st.size() == 1) {
                b[i] = *st.begin();
            }
        }

        multiset<int> st;
        for (int i = 0; i < k; i++) {
            if (!c[i]) {
                st.insert(a[i]);
            }
        }
        for (int i = 0; i < k; i++) {
            if (!c[i]) {
                if (b[i] != -1) {
                    auto it = st.find(b[i]);
                    if (it == st.end()) {
                        ans = "NO";
                        break;
                    }
                    st.erase(it);
                }
            }
        }
        cout << ans << endl;
    }

    return 0;
}
