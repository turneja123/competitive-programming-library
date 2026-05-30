//https://codeforces.com/contest/1991/problem/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
//#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

int vis[N];
vector<int> adj[N];

void dfs(int u) {
    for (int v : adj[u]) {
        if (vis[v] == -1) {
            vis[v] = vis[u] ^ 1;
            dfs(v);
        }
    }
}

int main() {
    //IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int i = 0; i < n; i++) {
            vis[i] = -1;
            adj[i].clear();
        }
        for (int i = 0; i < m; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        for (int i = 0; i < n; i++) {
            if (vis[i] == -1) {
                vis[i] = 0;
                dfs(i);
            }
        }
        int ok = 1;
        for (int i = 0; i < n; i++) {
            for (int j : adj[i]) {
                if (vis[i] == vis[j]) {
                    ok = 0;
                }
            }
        }
        if (ok == 0) {
            cout << "Alice" << endl;
            for (int i = 0; i < n; i++) {
                cout << "1 2" << endl;
                int u, c;
                cin >> u >> c;
            }
        } else {
            vector<int> a[2];
            int ptr[2] = {};
            for (int i = 0; i < n; i++) {
                a[vis[i] % 2].push_back(i);
            }
            cout << "Bob" << endl;
            for (int i = 0; i < n; i++) {
                int x, y;
                cin >> x >> y;
                x--, y--;
                if (x > y) {
                    swap(x, y);
                }
                if (y == 1) {
                    if (ptr[0] < a[0].size()) {
                        cout << a[0][ptr[0]] + 1 << " " << 1 << endl;
                        ptr[0]++;
                    } else {
                        cout << a[1][ptr[1]] + 1 << " " << 2 << endl;
                        ptr[1]++;
                    }
                } else {
                    if (ptr[x] < a[x].size()) {
                        cout << a[x][ptr[x]] + 1 << " " << x + 1 << endl;
                        ptr[x]++;
                    } else if (ptr[0] < a[0].size()) {
                        cout << a[0][ptr[0]] + 1 << " " << 3 << endl;
                        ptr[0]++;
                    } else {
                        cout << a[1][ptr[1]] + 1 << " " << 3 << endl;
                        ptr[1]++;
                    }
                }
            }
        }
    }

    return 0;
}
