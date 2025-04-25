//https://dmoj.ca/problem/nccc8s5
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int deg[N];
int id[N];
vector<int> adj[N];
vector<int> adj_id[N];

bool comp(int a, int b) {
    return deg[a] > deg[b];
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }
    vector<int> u(n);
    iota(u.begin(), u.end(), 0);
    sort(u.begin(), u.end(), comp);
    for (int i = 0; i < n; i++) {
        id[u[i]] = i;
    }
    for (int u = 0; u < n; u++) {
        for (int v : adj[u]) {
            adj_id[id[u]].push_back(id[v]);
        }
    }
    sort(adj_id[0].begin(), adj_id[0].end());
    int mex = 1;
    for (int v : adj_id[0]) {
        if (v != mex) {
            break;
        }
        mex++;
    }
    for (int i = 1; i < mex; i++) {
        sort(adj_id[i].begin(), adj_id[i].end());
        int cur = 0;
        for (int v : adj_id[i]) {
            if (cur == i) {
                cur++;
            }
            if (v != cur) {
                break;
            }
            cur++;
        }
        if (cur == i) {
            cur++;
        }
        mex = min(mex, cur);
    }
    int mx = 0;
    for (int i = n - 1; i >= mex; i--) {
        for (int v : adj_id[i]) {
            mx = max(mx, v);
        }
    }
    if (mx >= mex) {
        cout << 0 << endl;
        return 0;
    }
    int mn = n;
    for (int i = 0; i < mex; i++) {
        mn = min(mn, (int)adj_id[i].size());
    }
    if (mn >= mex) {
        cout << 1 << endl;
        return 0;
    }
    int ans = 1;
    for (int i = 0; i < n; i++) {
        if (adj_id[i].size() == mex - 1) {
            ans++;
        }
    }
    cout << ans << endl;
    return 0;
}
