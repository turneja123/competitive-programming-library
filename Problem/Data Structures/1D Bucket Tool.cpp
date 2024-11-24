//https://atcoder.jp/contests/abc380/tasks/abc380_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

using ll = long long;

const int N = 5e5 + 5;

int ans[N];

int main() {
    IOS;
    int n, q;
    cin >> n >> q;
    set<pair<pair<int, int>, int>> st;
    for (int i = 0; i < n; i++) {
        st.insert(make_pair(make_pair(i, i), i));
        ans[i] = 1;
    }
    for (int i = 0; i < q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int j, x;
            cin >> j >> x;
            j--, x--;
            auto it = st.upper_bound(make_pair(make_pair(j, N), N));
            it--;
            int l = it->first.first, r = it->first.second;
            if (it != st.begin()) {
                it--;
                if (it->second == x) {
                    l = it->first.first;
                    ans[it->second] -= it->first.second - it->first.first + 1;
                    it = st.erase(it);
                } else {
                    it++;
                }
            }
            it++;
            if (it != st.end()) {
                if (it->second == x) {
                    r = it->first.second;
                    ans[it->second] -= it->first.second - it->first.first + 1;
                    it = st.erase(it);
                }
            }
            it--;
            st.erase(it);
            ans[it->second] -= it->first.second - it->first.first + 1;
            st.insert(make_pair(make_pair(l, r), x));
            ans[x] += r - l + 1;
        } else {
            int x;
            cin >> x;
            x--;
            cout << ans[x] << endl;
        }
    }
    return 0;
}
