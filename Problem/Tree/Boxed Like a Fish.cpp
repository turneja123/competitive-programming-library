//https://codeforces.com/contest/2207/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;

int dp[N];
vector<int> adj[N];

void dfs(int u, int p, int k) {
    vector<int> child;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u, k);
            child.push_back(dp[v] + 1);
        }
    }
    if (child.size() == 0) {
        dp[u] = 0;
        return;
    }
    sort(child.begin(), child.end());
    if (child.size() == 1) {
        dp[u] = child[0];
    } else if (child[0] + child[1] - 1 <= k) {
        dp[u] = 0;
    } else {
        dp[u] = child[0];
    }
    return;
}


int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, k, root;
        cin >> n >> k >> root;
        root--;
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(root, root, k);
        if (!dp[root]) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }



    }


    return 0;
}
