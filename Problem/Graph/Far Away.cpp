//https://qoj.ac/contest/2559/problem/14421
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;

mt19937 gen(3);
vector<int> adj[N];

int dist[N];
int sz[N];
int col[N];
string ans[N];
vector<pair<int, int>> queries;

int main() {
    IOS;
    int n, m, q;
    cin >> n >> m >> q;
    for (int i = 0; i < n; i++) {
        col[i] = -1;
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int c = 0;

    for (int i = 0; i < n; i++) {
        if (col[i] == -1) {
            col[i] = c;
            queue<int> qe;
            qe.push(i);
            while (qe.size()) {
                sz[c]++;
                int u = qe.front();
                qe.pop();
                for (int v : adj[u]) {
                    if (col[v] == -1) {
                        col[v] = c;
                        qe.push(v);
                    }
                }
            }
            c++;
        }
    }
    vector<int> roll;
    for (int i = 0; i < n; i++) {
        if (sz[col[i]] > 20001) {
            roll.push_back(i);
        }
    }
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        queries.push_back({u, v});
        ans[i] = "YES";
        if (col[u] == col[v] && sz[col[u]] <= 20001) {
            ans[i] = "NO";
        }
        if (u == v) {
            ans[i] = "NO";
        }
    }
    if (roll.size()) {
        for (int i = 0; i < 500; i++) {
            int u = roll[gen() % (roll.size())];
            for (int j = 0; j < n; j++) {
                dist[j] = 1e9;
            }
            dist[u] = 0;
            queue<int> qe;
            qe.push(u);
            while (qe.size()) {
                int u = qe.front();
                qe.pop();
                for (int v : adj[u]) {
                    if (dist[v] > dist[u] + 1) {
                        dist[v] = dist[u] + 1;
                        qe.push(v);
                    }
                }
            }
            for (int j = 0; j < q; j++) {
                auto [u, v] = queries[j];
                if (dist[u] + dist[v] <= 20000) {
                    ans[j] = "NO";
                }
            }
        }
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }

    return 0;
}
