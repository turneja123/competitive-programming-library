//https://atcoder.jp/contests/abc291/tasks/abc291_e
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int deg[N];
int ans[N];
vector<int> adj[N];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        deg[v]++;
    }
    priority_queue<int, vector<int>, greater<int>> q;
    for (int i = 0; i < n; i++) {
        if (deg[i] == 0) {
            q.push(i);
        }
    }
    vector<int> sorted;
    bool can = true;
    while (q.size() && can) {
        int u = q.top();
        q.pop();
        if (q.size()) {
            can = false;
        }
        sorted.push_back(u);
        for (int v : adj[u]) {
            deg[v]--;
            if (deg[v] == 0) {
                q.push(v);
            }
        }
    }
    if (sorted.size() < n || !can) {
        cout << "No";
        return 0;
    }
    for (int i = 0; i < n; i++) {
        int u = sorted[i];
        ans[u] = i;
    }
    cout << "Yes" << endl;
    for (int i = 0; i < n; i++) {
        cout << ans[i] + 1 << " ";
    }
    return 0;
}
