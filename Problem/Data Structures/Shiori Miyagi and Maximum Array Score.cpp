//https://codeforces.com/contest/2171/problem/H
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
        int n, m;
        cin >> n >> m;
        set<pair<int, int>> st;
        st.insert({1, 0});
        int add = 0;
        for (int i = 2; i <= n; i++) {
            int x = m / i;
            vector<pair<int, int>> v;
            for (int j = i * x; j >= i; j -= i) {
                int t = j, e = 0;
                while (t % i == 0) {
                    e++;
                    t /= i;
                }
                auto it = st.lower_bound({j - add, -1});
                if (it == st.begin()) {
                    break;
                }
                it--;
                v.push_back({j, it->second + e});
            }
            add++;
            for (auto [x, y] : v) {
                auto it = st.lower_bound({x - add, -1});
                if (it != st.begin()) {
                    it--;
                    if (it->second >= y) {
                        continue;
                    }
                    it++;
                }
                while (it != st.end() && it->second <= y) {
                    it = st.erase(it);
                }
                st.insert({x - add, y});
            }
        }
        int ans = 0;
        for (auto [x, y] : st) {
            if (x + add <= m) {
                ans = max(ans, y);
            }
        }
        cout << ans << endl;
    }
    return 0;
}
