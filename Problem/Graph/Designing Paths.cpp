//https://www.facebook.com/codingcompetitions/hacker-cup/2025/round-2/problems/C/my-submissions
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 5e5 + 5;
const int INF = 1e9;

vector<pair<int, int>> appears[N];
int dist[N];

int main() {
    IOS;
    freopen("248.in", "r", stdin);
    freopen("248.out", "w", stdout);
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        int n, k, m;
        cin >> n >> k >> m;
        for (int i = 0; i < n; i++) {
            dist[i] = INF;
            appears[i].clear();
        }
        vector<vector<int>> go;
        vector<vector<int>> ed;
        for (int i = 0; i < m; i++) {
            int l;
            cin >> l;
            vector<int> go_cur(l + 1);
            iota(go_cur.begin(), go_cur.end(), 0);
            vector<int> v(l);
            for (int j = 0; j < l; j++) {
                cin >> v[j];
                v[j]--;
                appears[v[j]].push_back({i, j});
            }
            go.push_back(go_cur);
            ed.push_back(v);

        }

        auto ptr = [&](int i, int j) -> int {
            if (go[i][j] == j) {
                return j;
            }
            int p = j;
            while (go[i][j] != j) {
                j = go[i][j];
            }
            while (go[i][p] != p) {
                int tmp = go[i][p];
                go[i][p] = j;
                p = tmp;
            }
            return j;
        };


        auto rem = [&](int u) -> void {
            for (auto [i, j] : appears[u]) {
                go[i][j] = ptr(i, j + 1);
            }
        };
        queue<int> q;
        dist[0] = 0;
        rem(0);
        q.push(0);
        while (q.size()) {
            int u = q.front();
            q.pop();
            for (auto [i, j] : appears[u]) {
                int p = j;
                while (1) {
                    p = ptr(i, p);
                    if (p == go[i].size() - 1 || p - j > k) {
                        break;
                    }
                    int v = ed[i][p];
                    assert(dist[v] > dist[u] + 1);
                    dist[v] = dist[u] + 1;
                    rem(v);
                    q.push(v);
                }
            }
        }
        ll ans = 0;
        for (int i = 0; i < n; i++) {
            if (dist[i] == INF) {
                dist[i] = -1;
            }
            ans += (ll)dist[i] * (i + 1);
        }

        cout << "Case #" << tt << ": " << ans << endl;

    }
    return 0;
}
