//https://dmoj.ca/problem/dcc1p5
#pragma GCC optimize("Ofast,fast-math")
#pragma GCC target("popcnt")

#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3005;

bitset<N> mat[N];
bool vis[N];
int deg[N];
int ans[N][N];

vector<int> adj[N];
vector<vector<int>> comps;
vector<int> comp;


void dfs(int u) {
    comp.push_back(u);
    vis[u] = true;
    for (int v : adj[u]) {
        if (!vis[v]) {
            dfs(v);
        }
    }
}

void print(int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << ans[i][j];
        }
        cout << endl;
    }
}

int main() {
    IOS;
    int n, k;
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < n; j++) {
            bool b = s[j] == '1';
            if (b) {
                mat[i].set(j);
            }
            if (mat[i][j]) {
                adj[i].push_back(j);
                deg[i]++;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(i);
            comps.push_back(comp);
            comp.clear();
        }
    }
    if (k == 1) {
        if (comps.size() > 1) {
            cout << "POSSIBLE" << endl;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    ans[i][j] = mat[i][j];
                }
            }
            print(n);
        } else {
            for (int x : comps[0]) {
                if (deg[x] < comps[0].size() - 1) {
                    cout << "POSSIBLE" << endl;
                    for (int i = 0; i < n; i++) {
                        for (int j = 0; j < n; j++) {
                            if (mat[i][j]) {
                                if (i == x || j == x) {
                                    ans[i][j] = 2;
                                } else {
                                    ans[i][j] = 1;
                                }
                            }
                        }
                    }
                    print(n);
                    return 0;
                }
            }
            cout << "IMPOSSIBLE";
        }
    } else {
        if (comps.size() > 2) {
            cout << "POSSIBLE" << endl;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    ans[i][j] = mat[i][j];
                }
            }
            print(n);
        } else if (comps.size() == 2) {
            if (comps[0].size() > 1 && comps[1].size() > 1) {
                cout << "POSSIBLE" << endl;
                for (int i = 0; i < n; i++) {
                    for (int j = 0; j < n; j++) {
                        ans[i][j] = mat[i][j];
                    }
                }
                for (int x : comps[1]) {
                    for (int y : adj[x]) {
                        ans[x][y] = 2;
                    }
                }
                print(n);
            } else {
                if (comps[0].size() < comps[1].size()) {
                    swap(comps[0], comps[1]);
                }
                for (int x : comps[0]) {
                    if (deg[x] < comps[0].size() - 1) {
                        cout << "POSSIBLE" << endl;
                        for (int i = 0; i < n; i++) {
                            for (int j = 0; j < n; j++) {
                                if (mat[i][j]) {
                                    if (i == x || j == x) {
                                        ans[i][j] = 2;
                                    } else {
                                        ans[i][j] = 1;
                                    }
                                }
                            }
                        }
                        print(n);
                        return 0;
                    }
                }
                cout << "IMPOSSIBLE";
            }

        } else {
            for (int x = 0; x < n; x++) {
                for (int y = x + 1; y < n; y++) {
                    bitset<N> b = mat[x] | mat[y];
                    b.set(x);
                    b.set(y);
                    int ct = b.count();
                    if (ct + 2 <= n || ((ct + 1 <= n && (mat[x] & mat[y]).count() == 0 && !mat[x][y]))) {
                        cout << "POSSIBLE" << endl;
                        for (int i = 0; i < n; i++) {
                            for (int j = 0; j < n; j++) {
                                if (mat[i][j]) {
                                    if (i == x || j == x || i == y || j == y) {
                                        ans[i][j] = 2;
                                    } else {
                                        ans[i][j] = 1;
                                    }
                                }
                            }
                        }
                        print(n);
                        return 0;
                    }
                }
            }
            cout << "IMPOSSIBLE";
        }
    }

    return 0;
}
