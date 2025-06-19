//https://atcoder.jp/contests/abc410/tasks/abc410_d
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1050;

int seen[N][N];
vector<pair<int, int>> adj[N];


int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        adj[u].push_back({v, wt});
    }
    seen[0][0] = 1;
    queue<pair<int, int>> q;
    q.push({0, 0});
    while (q.size()) {
        auto [u, j] = q.front();
        q.pop();
        for (auto [v, wt] : adj[u]) {
            if (!seen[v][j ^ wt]) {
                seen[v][j ^ wt] = true;
                q.push({v, j ^ wt});
            }
        }
    }
    int ans = -1;
    for (int j = 0; j < N; j++) {
        if (seen[n - 1][j]) {
            ans = j;
            break;
        }
    }
    cout << ans;
    return 0;
}
