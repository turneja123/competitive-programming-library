//https://www.codechef.com/problems/EMPTYSTR
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
        string s;
        cin >> s;
        set<int> pos[2];
        for (int i = 0; i < n; i++) {
            if (s[i] == 'A') {
                pos[0].insert(i);
            } else {
                pos[1].insert(i);
            }
        }
        int ans = 0;
        while (pos[0].size() || pos[1].size()) {
            int x = (pos[0].size() ? *pos[0].begin() : n);
            int y = (pos[1].size() ? *pos[1].begin() : n);
            int last, ind = min(x, y);
            if (x < y) {
                last = 0;
            } else {
                last = 1;
            }
            vector<pair<int, int>> rem;
            while (ind != n) {
                rem.push_back(make_pair(last, ind));
                last ^= 1;
                auto it = pos[last].lower_bound(ind);
                if (it == pos[last].end()) {
                    ind = n;
                } else {
                    ind = *it;
                }
            }
            for (int i = 0; i < rem.size(); i++) {
                pos[rem[i].first].erase(rem[i].second);
            }
            ans++;
        }
        cout << ans << endl;

    }

    return 0;
}
