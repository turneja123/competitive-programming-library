//https://codeforces.com/contest/2165/problem/C
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
        int n, q;
        cin >> n >> q;
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        sort(a.begin(), a.end());
        reverse(a.begin(), a.end());
        while (a.size() > 32) {
            a.pop_back();
        }
        multiset<int> st;
        for (int i = 0; i < a.size(); i++) {
            st.insert(a[i]);
        }

        while (q--) {
            int x;
            cin >> x;
            int ans = 0;
            multiset<int> tmp = st;
            for (int i = 29; i >= 0; i--) {
                int b = (1 << i) & x;
                int c = b & x;
                if (c) {
                    auto it = tmp.end();
                    it--;
                    int y = *it;
                    if (y >= x) {
                        break;
                    }
                    tmp.erase(it);
                    if (y >= b) {
                        tmp.insert(y - b);
                    } else {
                        ans += b - y;
                        tmp.insert(0);
                    }
                    x -= c;
                }
            }
            cout << ans << endl;
        }
    }
    return 0;
}
