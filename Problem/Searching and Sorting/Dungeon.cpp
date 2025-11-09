//https://codeforces.com/contest/2164/problem/C
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int b[N];
int c[N];

bool comp(pair<int, int> a, pair<int, int> b) {
    if (a.first != b.first) {
        return a.first < b.first;
    }
    return a.second > b.second;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        multiset<int> st;
        for (int i = 0; i < n; i++) {
            int x;
            cin >> x;
            st.insert(x);
        }
        vector<pair<int, int>> l, r;
        for (int i = 0; i < m; i++) {
            cin >> b[i];
        }
        for (int i = 0; i < m; i++) {
            cin >> c[i];
            if (c[i] > 0) {
                l.push_back({b[i], c[i]});
            } else {
                r.push_back({b[i], c[i]});
            }
        }
        sort(l.begin(), l.end(), comp);
        sort(r.begin(), r.end(), comp);
        int ans = 0;
        for (auto [b, c] : l) {
            auto it = st.lower_bound(b);
            if (it == st.end()) {
                continue;
            }
            int d = *it;
            st.erase(it);
            ans++;
            st.insert(max(d, c));
        }
        for (auto [b, _] : r) {
            auto it = st.lower_bound(b);
            if (it == st.end()) {
                continue;
            }
            int d = *it;
            st.erase(it);
            ans++;

        }
        cout << ans << endl;


    }
    return 0;
}
