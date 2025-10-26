//https://www.facebook.com/codingcompetitions/hacker-cup/2025/practice-round/problems/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

vector<tuple<int, int, int>> queries[N];

int main() {
    IOS;
    freopen("248.in", "r", stdin);
    freopen("248.out", "w", stdout);
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        int n, q, l;
        cin >> n >> q >> l;
        vector<int> x(n);
        map<int, int> mp;
        for (int i = 0; i < n; i++) {
            cin >> x[i];
            mp[x[i]] = i;
        }
        set<int> wall;
        set<int> st;
        wall.insert(1);
        wall.insert(l);
        for (int i = 0; i < q; i++) {
            int t;
            cin >> t;
            if (t == 1) {
                int y;
                cin >> y;
                wall.insert(y);
            } else {
                int j, s;
                cin >> j >> s;
                j--;
                auto it = wall.lower_bound(x[j]);
                int r = *it;
                it--;
                int l = *it;
                queries[j].push_back({l, r, s});
            }
        }
        ll ans = 0;
        for (int j = n - 1; j >= 0; j--) {
            for (auto [l, r, s] : queries[j]) {
                if (st.empty()) {
                    continue;
                }
                auto it = st.lower_bound(r);
                if (it == st.begin()) {
                    continue;
                }
                it--;
                if (*it < l) {
                    continue;
                }
                int len = r - l, id = -1;
                if (s >= len) {
                    id = *it;
                    s %= len;
                }
                int lf = l, rt = r, spl = -1;
                while (lf <= rt) {
                    int mid = (lf + rt) / 2;
                    int tim = (x[j] + mid + 1) / 2 - l;
                    if (tim <= s) {
                        spl = mid;
                        lf = mid + 1;
                    } else {
                        rt = mid - 1;
                    }
                }
                if (spl != -1) {
                    auto it = st.upper_bound(spl);
                    if (it != st.begin()) {
                        it--;
                        if (*it >= l) {
                            id = *it;
                        }
                    }
                }
                if (id != -1) {
                    ans += mp[id] + 1;
                }
            }
            st.insert(x[j]);
            queries[j].clear();
        }
        cout << "Case #" << tt << ": " << ans << " " << endl;


    }

    return 0;
}
