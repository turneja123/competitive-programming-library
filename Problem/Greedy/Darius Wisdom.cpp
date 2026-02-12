//https://codeforces.com/contest/2034/problem/D
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
        vector<int> a(n);
        vector<int> pos;
        set<int> st;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (a[i] == 1) {
                st.insert(i);
            } else if (a[i] == 2) {
                pos.push_back(i);
            }
        }
        vector<pair<int, int>> ans;
        int r = n - 1;
        for (int i : pos) {
            while (r >= 0 && a[r] == 2) {
                r--;
            }
            if (i >= r) {
                break;
            }
            if (a[r] == 1) {
                a[i]--;
                a[r]++;
                ans.push_back({i, r});
                st.insert(i);
                st.erase(r);
            } else {
                int j = *st.begin();
                a[j]--;
                a[i]--;
                ans.push_back({j, r});
                ans.push_back({i, r});
                a[r] += 2;
                st.erase(j);
                st.insert(i);
            }
        }
        queue<int> q;
        for (int i = 0; i < n; i++) {
            if (a[i] == 1) {
                q.push(i);
            } else if (a[i] == 0 && q.size()) {
                ans.push_back({q.front(), i});
                q.pop();
                q.push(i);
            }
        }
        cout << ans.size() << endl;
        for (auto [u, v] : ans) {
            cout << u + 1 << " " << v + 1 << endl;
        }

    }

    return 0;
}
