//https://www.spoj.com/problems/TUPLEDIV/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e4 + 5;
const int K = 15;
const int INF = 1e9;

int a[N][K];
int grp[N];

int c[K];
int mn[K];
int par[K];
int from[K];
bool vis[K];

priority_queue<pair<int, int>> pq[K][K];

int get(int u, int v) {
    while (pq[u][v].size() && grp[pq[u][v].top().second] != u) {
        pq[u][v].pop();
    }
    return (pq[u][v].size() ? pq[u][v].top().first : -1);
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;
        for (int j = 0; j < m; j++) {
            cin >> c[j];
        }
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                cin >> a[i][j];
                pq[m][j].push(make_pair(a[i][j], i));
            }
            grp[i] = m;
        }
        for (int g = 0; g < m; g++) {
            int score = 0;
            for (int it = 0; it < c[g]; it++) {
                for (int j = 0; j < g; j++) {
                    vis[j] = false;
                }
                queue<int> q;
                q.push(m);
                while (q.size()) {
                    int u = q.front();
                    q.pop();
                    for (int v = 0; v < g; v++) {
                        if (c[v] > 0 && v != u && !vis[v] && get(u, v) == mn[v]) {
                            vis[v] = true;
                            par[v] = u;
                            from[v] = pq[u][v].top().second;
                            q.push(v);
                        }
                    }
                }
                int best = get(m, g), u = m;
                for (int v = 0; v < g; v++) {
                    if (vis[v]) {
                        int cur = get(v, g);
                        if (cur > best) {
                            best = cur;
                            u = v;
                        }
                    }
                }
                score += best;
                grp[pq[u][g].top().second] = g;
                while (u != m) {
                    int x = from[u];
                    grp[x] = u;
                    for (int j = 0; j < m; j++) {
                        if (j != u) {
                            pq[u][j].push(make_pair(a[x][j], x));
                        }
                    }
                    u = par[u];
                }
            }
            mn[g] = INF;
            for (int i = 0; i < n; i++) {
                if (grp[i] == g) {
                    mn[g] = min(mn[g], a[i][g]);
                }
            }
            for (int i = 0; i < n; i++) {
                if (grp[i] == g && a[i][g] == mn[g]) {
                    for (int j = 0; j < m; j++) {
                        if (j != g) {
                            pq[g][j].push(make_pair(a[i][j], i));
                        }
                    }
                }
            }
            cout << score << " ";
        }
        cout << endl;
        for (int i = 0; i <= m; i++) {
            for (int j = 0; j < m; j++) {
                while (pq[i][j].size()) {
                    pq[i][j].pop();
                }
            }
        }
    }
    return 0;
}
