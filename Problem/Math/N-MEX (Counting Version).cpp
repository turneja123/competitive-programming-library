//https://codeforces.com/contest/2207/problem/E2
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const ll M = 1e9 + 7;

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        vector<int> a(n), ans(n);
        multiset<int> st, x, take;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            st.insert(a[i]);
        }
        vector<int> pref(n + 1);
        for (int i = 0; i <= n; i++) {
            pref[i] = (i == 0 ? 0 : pref[i - 1]);
            x.insert(i);
            if (st.find(i) == st.end()) {
                take.insert(i);
                pref[i]++;
            }
        }

        int ok = 1; ll ct = 1;
        for (int i = 0, j = 0; i < n && ok; i++) {
            if (a[i] > n || (i != n - 1 && a[i] < a[i + 1])) {
                ok = 0;
                break;
            }
            int l = a[i], r = (i == 0 ? n : a[i - 1]);

            if (x.lower_bound(l) == x.lower_bound(r)) {
                auto it = take.lower_bound(a[i]);
                if (it == take.begin()) {
                    ok = 0;
                    break;
                }
                it--;
                ans[i] = *it;
            } else {
                ans[i] = r;
            }
            if (x.find(ans[i]) == x.end()) {
                ok = 0;
                break;
            }
            x.erase(ans[i]);
            take.erase(ans[i]);
            st.erase(st.find(a[i]));
            if (st.find(a[i]) == st.end()) {
                take.insert(a[i]);
            }
            if (l != r) {
                ct = ct * (i + 1) % M;
            }
        }
        for (int i = n - 1, j = 0; i >= 0 && ok; i--) {
            int l = a[i], r = (i == 0 ? n : a[i - 1]);
            if (l == r) {
                ct = ct * (pref[a[i]] - j) % M;
                j++;
            }
        }
        if (!ok) {
            cout << 0 << endl;
        } else {
            cout << ct << endl;

        }


    }


    return 0;
}
