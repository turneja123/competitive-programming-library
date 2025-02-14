//https://codeforces.com/problemset/problem/2004/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int INF = 1e9;

int a[N];
vector<string> v{"BG", "BR", "BY", "GR", "GY", "RY"};
map<string, int> mp;
vector<int> adj[N];
vector<int> pos[N];

int main() {
    IOS;
    int m = 0;
    for (string s : v) {
        mp[s] = m++;
    }
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            if (v[i][0] == v[j][0] || v[i][0] == v[j][1] || v[i][1] == v[j][0] || v[i][1] == v[j][1]) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int n, q;
        cin >> n >> q;
        for (int i = 0; i < n; i++) {
            string s;
            cin >> s;
            a[i] = mp[s];
            pos[a[i]].push_back(i);
        }
        for (int i = 0; i < q; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            if (u == v) {
                cout << 0 << endl;
                continue;
            }
            bool f = false;
            for (int x : adj[a[u]]) {
                if (x == a[v]) {
                    f = true;
                }
            }
            if (f || a[u] == a[v]) {
                cout << abs(u - v) << endl;
                continue;
            }
            int ans = INF;
            for (int x : adj[a[u]]) {
                if (pos[x].empty()) {
                    continue;
                }
                int l = lower_bound(pos[x].begin(), pos[x].end(), u) - pos[x].begin();
                for (int j = max(0, l - 3); j < min((int)pos[x].size(), l + 3); j++) {
                    ans = min(ans, abs(u - pos[x][j]) + abs(pos[x][j] - v));
                }
            }
            if (ans == INF) {
                cout << -1 << endl;
            } else {
                cout << ans << endl;
            }
        }
        for (int i = 0; i < m; i++) {
            pos[i].clear();
        }
    }
    return 0;
}
