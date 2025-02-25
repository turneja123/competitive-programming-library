//https://atcoder.jp/contests/abc394/tasks/abc394_f
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int dp[N][5];
vector<int> adj[N];

void dfs(int u, int p) {
    dp[u][0] = 1;
    multiset<int, greater<int>> st;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
            st.insert(max(dp[v][0], dp[v][3]));
            if (st.size() > 4) {
                st.erase(prev(st.end()));
            }
        }
    }
    if (st.size() < 3) {
        return;
    }
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        sum += *st.begin();
        st.erase(st.begin());
    }
    dp[u][3] = sum + 1;
    if (st.size()) {
        sum += *st.begin();
        dp[u][4] = sum + 1;
    } else {
        if (u != 0) {
            dp[u][4] = sum + 2;
        }
    }
}

int main() {
    IOS;
    int n;
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(0, 0);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans = max(ans, dp[i][4]);
    }
    if (ans == 0) {
        cout << -1;
    } else {
        cout << ans;
    }


    return 0;
}
