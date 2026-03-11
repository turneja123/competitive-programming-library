//https://repovive.com/contests/4/problems/E
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
        int n;
        cin >> n;
        vector<tuple<int, int, int>> a;
        vector<int> vis(n, 0);
        set<pair<int, int>> st;
        set<int> ord;
        for (int i = 0; i < n; i++) {
            int l, r;
            cin >> l >> r;
            a.push_back({l, r, i});
            st.insert({r, i});
        }
        sort(a.begin(), a.end());
        vector<int> ans(n);
        int j = 0, ct = 0;
        while (ct < n) {
            while (vis[st.begin()->second]) {
                st.erase(st.begin());
            }
            int R = st.begin()->first;
            while (j < n && get<0>(a[j]) <= R) {
                ord.insert(get<2>(a[j]));
                j++;
            }
            ans[ct++] = *ord.begin();
            vis[*ord.begin()] = 1;
            ord.erase(ord.begin());
        }
        for (int i = 0; i < n; i++) {
            cout << ans[i] + 1 << " ";
        }
        cout << endl;

    }


    return 0;
}
