//https://codeforces.com/contest/1218/problem/I
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2005;

char a[N][N];
int b[N];

int must[4 * N];
vector<int> adj[4 * N], rev[4 * N];
int vis[4 * N];
int id[4 * N];

int n;

int other(int i) {
    if (i < n) {
        return i + n;
    }
    if (i < 2 * n) {
        return i - n;
    }
    if (i < 3 * n) {
        return i + n;
    }
    return i - n;
}

void add_edge(int u, int v) {
    adj[u].push_back(v);
    adj[other(v)].push_back(other(u));
    rev[v].push_back(u);
    rev[other(u)].push_back(other(v));
}

vector<int> ord;

void dfs(int u) {
    vis[u] = 1;
    for (int v : adj[u]) {
        if (!vis[v]) {
            dfs(v);
        }
    }
    ord.push_back(u);
}

void dfs_comp(int u, int j) {
    vis[u] = 1;
    id[u] = j;
    for (int v : rev[u]) {
        if (!vis[v]) {
            dfs_comp(v, j);
        }
    }
}

int main() {
    IOS;
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < n; j++) {
            if (s[j] == '1') {
                a[i][j] ^= 1;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < n; j++) {
            if (s[j] == '1') {
                a[i][j] ^= 1;
            }
        }
    }
    string s;
    cin >> s;
    for (int j = 0; j < n; j++) {
        if (s[j] == '1') {
            b[j] = 1;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            //ako uzmem red i
            int v = a[i][j] ^ b[j];
            if (v == 1) {
                if (b[i] == 1) {
                    add_edge(i, 2 * n + j);
                } else {
                    must[n + i] = 1;
                }
            } else {
                if (b[i] == 1) {
                    add_edge(i, 3 * n + j);
                }
            }

            //ako ne uzmem red i
            v = a[i][j];
            if (v == 1) {
                if (b[i] == 1) {
                    add_edge(n + i, 2 * n + j);
                } else {
                    must[i] = 1;
                }
            } else {
                if (b[i] == 1) {
                    add_edge(n + i, 3 * n + j);
                }
            }
        }
    }

    for (int i = 0; i < 4 * n; i++) {
        if (must[i] && must[other(i)]) {
            cout << -1;
            return 0;
        }
        if (must[i]) {
            add_edge(other(i), i);
        }
    }
    for (int i = 0; i < 4 * n; i++) {
        if (!vis[i]) {
            dfs(i);
        }
    }
    for (int i = 0; i < 4 * n; i++) {
        vis[i] = 0;
    }
    int j = 0;
    while (ord.size()) {
        int u = ord.back();
        ord.pop_back();
        if (!vis[u]) {
            dfs_comp(u, j++);
        }
    }
    for (int i = 0; i < 4 * n; i++) {
        if (id[i] == id[other(i)]) {
            cout << -1;
            return 0;
        }
    }
    vector<pair<int, int>> ans;
    for (int i = 0; i < n; i++) {
        if (id[i] > id[n + i]) {
            ans.push_back({0, i});
        }
    }
    for (int i = 0; i < n; i++) {
        if (id[2 * n + i] > id[3 * n + i]) {
            ans.push_back({1, i});
        }
    }
    cout << ans.size() << endl;
    for (auto [t, x] : ans) {
        if (t == 0) {
            cout << "row " << x << endl;
        } else {
            cout << "col " << x << endl;
        }
    }

    return 0;
}
