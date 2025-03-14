//https://atcoder.jp/contests/abc219/tasks/abc219_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int B = 450;

bool heavy[N];
vector<pair<int, int>> upd[N];
vector<pair<int, int>> upd_heavy[N];
vector<int> adj[N];
vector<int> adj_heavy[N];

int main() {
    IOS;
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        if (adj[i].size() > B) {
            heavy[i] = true;
        }
    }
    for (int i = 0; i < n; i++) {
        upd[i].push_back(make_pair(-1, i));
        for (int v : adj[i]) {
            if (heavy[v]) {
                adj_heavy[i].push_back(v);
            }
        }
    }
    for (int i = 0; i < q; i++) {
        int u;
        cin >> u;
        u--;
        if (!heavy[u]) {
            int c = upd[u].back().second, tim = upd[u].back().first;
            for (int v : adj_heavy[u]) {
                if (upd_heavy[v].empty()) {
                    continue;
                }
                if (upd_heavy[v].back().first > tim) {
                    tim = upd_heavy[v].back().first;
                    c = upd_heavy[v].back().second;
                }
            }
            upd[u].push_back(make_pair(i, c));
            for (int v : adj[u]) {
                upd[v].push_back(make_pair(i, c));
            }
        } else {
            int c = upd[u].back().second, tim = upd[u].back().first;
            for (int v : adj_heavy[u]) {
                if (upd_heavy[v].empty()) {
                    continue;
                }
                if (upd_heavy[v].back().first > tim) {
                    tim = upd_heavy[v].back().first;
                    c = upd_heavy[v].back().second;
                }
            }
            upd_heavy[u].push_back(make_pair(i, c));
        }
    }
    for (int i = 0; i < n; i++) {
        int c = upd[i].back().second, tim = upd[i].back().first;
        for (int v : adj_heavy[i]) {
            if (upd_heavy[v].empty()) {
                continue;
            }
            if (upd_heavy[v].back().first > tim) {
                tim = upd_heavy[v].back().first;
                c = upd_heavy[v].back().second;
            }
        }
        cout << c + 1 << " ";
    }
    return 0;
}
