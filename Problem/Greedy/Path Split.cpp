//https://codeforces.com/contest/2165/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e6 + 5;

set<int> st[N];
vector<int> pos[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            int a;
            cin >> a;
            pos[a].push_back(i);
            st[a].insert(i);
        }
        int ans = n;
        for (int i = 2 * n; i >= 1; i--) {
            if (pos[i].empty()) {
                continue;
            }
            reverse(pos[i].begin(), pos[i].end());
            for (int j : pos[i]) {
                int found = 0;
                if (st[i + 1].size()) {
                    auto it = st[i + 1].upper_bound(j);
                    if (it != st[i + 1].end()) {
                        ans--;
                        found = 1;
                        st[i + 1].erase(it);
                    }
                }
                if (!found && st[i - 1].size()) {
                    auto it = st[i - 1].upper_bound(j);
                    if (it != st[i - 1].end()) {
                        ans--;
                        st[i - 1].erase(it);
                    }
                }
            }
        }
        for (int i = 2 * n; i >= 1; i--) {
            st[i].clear();
            pos[i].clear();
        }
        cout << ans << endl;

    }
    return 0;
}
