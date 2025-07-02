//https://www.codechef.com/START192A/problems/PARTMIN
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int a[N];
int f[N];

set<int> adj[N];

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        int ans = n;
        set<int> st;
        for (int i = 1; i <= n; i++) {
            st.insert(i);
        }
        for (int i = 0; i < n; i++) {
            cin >> a[i];
            if (a[i] != 0) {
                st.erase(a[i]);
            }
        }
        vector<int> all;
        for (int x : st) {
            all.push_back(x);
        }
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            if (a[v]) {
                adj[u].insert(a[v]);
            } else {
                f[u]++;
            }
            if (a[u]) {
                adj[v].insert(a[u]);
            } else {
                f[v]++;
            }
        }
        for (int i = 0; i < n; i++) {
            if (a[i] > 0) {
                int mx = (adj[i].empty() ? 0 : *adj[i].rbegin());
                int need = (f[i] == 0 ? 0 : all[f[i] - 1]);
                if (max(mx, need) < a[i]) {
                    ans = min(ans, a[i]);
                }
            } else {
                int mx = (adj[i].empty() ? 0 : *adj[i].rbegin());
                int need = all[f[i]];
                int pos = lower_bound(all.begin(), all.end(), max(mx, need)) - all.begin();
                if (pos < all.size()) {
                    ans = min(ans, all[pos]);
                }
            }
        }
        cout << ans << endl;
        for (int i = 0; i <= n; i++) {
            adj[i].clear();
            f[i] = 0;
        }

    }
    return 0;
}
