//https://codeforces.com/contest/2050/problem/F
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int INF = 2e9;

vector<pair<int, int>> ans[N];
int a[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        map<int, int> mp;
        int diff = abs(a[1] - a[0]);
        mp[diff] = 0;
        ans[1].push_back(make_pair(0, diff));
        for (int i = 2; i < n; i++) {
            int diff = abs(a[i] - a[i - 1]);
            if (diff == 0) {
                auto it = mp.find(0);
                if (it == mp.end()) {
                    mp[0] = i - 1;
                }
            } else {
                map<int, int> nx;
                nx[diff] = i - 1;
                for (auto it = mp.begin(); it != mp.end(); ++it) {
                    int g = (it->first == 0 ? diff : __gcd(diff, it->first));
                    auto f = nx.find(g);
                    if (f == nx.end()) {
                        nx[g] = it->second;
                    } else {
                        nx[g] = min(nx[g], it->second);
                    }
                }
                mp = nx;
            }
            for (auto it = mp.begin(); it != mp.end(); ++it) {
                ans[i].push_back(make_pair(it->second, it->first));
            }
            sort(ans[i].begin(), ans[i].end());
        }
        for (int i = 0; i < q; i++) {
            int l, r;
            cin >> l >> r;
            l--, r--;
            if (l == r) {
                cout << 0 << " ";
                continue;
            }
            int x = upper_bound(ans[r].begin(), ans[r].end(), make_pair(l, INF)) - ans[r].begin() - 1;
            cout << ans[r][x].second << " ";
        }
        for (int i = 0; i <= n; i++) {
            ans[i].clear();
        }
        cout << endl;
    }

    return 0;
}
