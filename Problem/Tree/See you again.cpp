//solution for https://www.spoj.com/problems/DST/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

set<int> adj[N];
vector<int> ans;
char c[N];
int parent[N];
string s = "tareq&shawon";
int m = s.size();

void dfs(int v, int j) {
    int ct = 0;
    if (c[v] == s[j]) {
        j++;
    }
    for (int u : adj[v]) {
        if (u != parent[v]) {
            parent[u] = v;
            ct++;
            dfs(u, j);
        }
    }
    if (ct == 0 && j == m && ans.size() == 0) {
        while (v != 0) {
            ans.push_back(v);
            v = parent[v];
        }
        ans.push_back(0);
        reverse(ans.begin(), ans.end());
    }
}

int main() {
    IOS;
    int t;
    cin >> t;
    int k = 1;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n - 1; i++) {
            int a, b;
            cin >> a >> b;
            a--, b--;
            adj[a].insert(b);
            adj[b].insert(a);
        }
        for (int i = 0; i < n; i++) {
            cin >> c[i];
        }
        parent[0] = 0;
        dfs(0, 0);

        cout << "Case " << k << ": ";
        if (ans.size()) {
            cout << "YES" << endl;
            for (int i = 0; i < ans.size(); i++) {
                cout << ans[i] + 1 << " ";
            }
        } else {
            cout << "NO" << endl;
        }
        ans.clear();
        for (int i = 0; i < n; i++) {
            adj[i].clear();
        }
        k++;
    }
    return 0;
}
