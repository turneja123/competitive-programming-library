//https://atcoder.jp/contests/abc386/tasks/abc386_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

vector<pair<int, int>> vw, vb;

multiset<int> st;

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        char c;
        cin >> c;
        if (c == 'W') {
            vw.push_back(make_pair(x, y));
        } else {
            vb.push_back(make_pair(x, y));
            st.insert(y);
        }
    }
    sort(vw.begin(), vw.end());
    sort(vb.begin(), vb.end());
    string ans = "Yes";
    for (int i = 0, l = 0; i < vw.size(); i++) {
        while (l < vb.size() && vb[l].first < vw[i].first) {
            st.erase(st.find(vb[l].second));
            l++;
        }
        if (st.size() && *st.rbegin() >= vw[i].second) {
            ans = "No";
        }
    }
    cout << ans;
    return 0;
}

