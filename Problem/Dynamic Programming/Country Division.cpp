//https://ocpc2026w.eolymp.space/en/compete/9umgdpquih09n7lf096jj2cqvk/problem/3
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
        vector<int> deg(n);
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            deg[u]++;
            deg[v]--;
        }

        vector<int> dp(2 * m + 2, 0);
        vector<int> dp_nx(2 * m + 2, 0);
        vector<int> parent(2 * m + 2, 0);

        dp[m + deg[0]] = 1;
        dp_nx[m + deg[0]] = 1;
        parent[m + deg[0]] = -1;

        for (int i = 1; i < n - 1; i++) {

            vector<int> add;
            for (int j = 0; j < 2 * m + 2; j++) {
                if (dp[j] && j + deg[i] >= 0 && j + deg[i] < 2 * m + 2 && !dp_nx[j + deg[i]]) {
                    parent[j + deg[i]] = i;
                    dp_nx[j + deg[i]] = 1;
                    add.push_back(j + deg[i]);
                }
            }
            for (int j : add) {
                dp[j] = 1;
            }
        }
        if (dp[m] == 0) {
            cout << "NO" << endl;
            continue;
        }
        vector<int> ans(n, 1);
        ans[0] = 0;
        int cur = m;
        while (cur != m + deg[0]) {
            ans[parent[cur]] = 0;
            cur -= deg[parent[cur]];
        }
        cout << "YES" << endl;
        for (int i = 0; i < n; i++) {
            cout << ans[i] << " ";
        }
        cout << endl;

    }

    return 0;
}
