//https://csacademy.com/contest/archive/task/no-prime-sum/statement/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const int INF = 1e9;

vector<int> adj[N];
int pairU[N];
int pairV[N];
int dist[N];
int m, n;

int a[N];
int ind[N];
int valU[N];
int valV[N];

bool composite[N];

bool bfs() {
    queue <int> q;
    for (int u = 1; u <= m; u++) {
        if (pairU[u] == 0) {
            dist[u] = 0;
            q.push(u);
        } else {
            dist[u] = INF;
        }
    }
    dist[0] = INF;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (dist[u] < dist[0]) {
            for (auto it = adj[u].begin(); it != adj[u].end(); ++it) {
                int v = *it;
                if (dist[pairV[v]] == INF) {
                    dist[pairV[v]] = dist[u] + 1;
                    q.push(pairV[v]);
                }
            }
        }
    }
    return (dist[0] != INF);
}

bool dfs(int u) {
    if (u != 0) {
        for (auto it = adj[u].begin(); it!= adj[u].end(); ++it) {
            int v = *it;
            if (dist[pairV[v]] == dist[u] + 1) {
                if (dfs(pairV[v]) == true) {
                    pairV[v] = u;
                    pairU[u] = v;
                    return true;
                }
            }
        }
        dist[u] = INF;
        return false;
    }
    return true;
}

int bpm() {
    int res = 0;
    while (bfs()) {
        for (int u = 1; u <= m; u++) {
            if (pairU[u] == 0 && dfs(u)) {
                res++;
            }
        }
    }
    return res;
}

int main() {
    IOS;
    for (int i = 2; i < N; i++) {
        if (!composite[i]) {
            for (int j = 2 * i; j < N; j += i) {
                composite[j] = true;
            }
        }
    }

    int e;
    cin >> e;
    m = 0, n = 0;
    for (int i = 0; i < e; i++) {
        cin >> a[i];
        if (a[i] % 2 == 0) {
            m++;
            valU[m] = a[i];
            ind[i] = m;
        } else {
            n++;
            valV[n] = a[i];
            ind[i] = n;
        }
    }
    for (int i = 0; i < e; i++) {
        if (a[i] % 2 == 0) {
            for (int j = 0; j < e; j++) {
                if (!composite[a[i] + a[j]]) {
                    adj[ind[i]].push_back(ind[j] + m);
                }
            }
        }
    }

    cout << bpm() << endl;

    vector<bool> freeU(m + 1, false);
    for (int u = 1; u <= m; u++) {
        if (pairU[u] == 0) {
            freeU[u] = true;
        }
    }
    vector<bool> visitedU(m + 1, false);
    vector<bool> visitedV(n + 1, false);
    queue<int> q;

    for (int u = 1; u <= m; u++) {
        if (freeU[u]) {
            q.push(u);
            visitedU[u] = true;
        }
    }

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto v : adj[u]) {
            if (!visitedV[v - m]) {
                visitedV[v - m] = true;
                if (pairV[v] != 0 && !visitedU[pairV[v]]) {
                    visitedU[pairV[v]] = true;
                    q.push(pairV[v]);
                }
            }
        }
    }

    for (int u = 1; u <= m; u++) {
        if (!visitedU[u]) {
            cout << valU[u] << " ";
        }
    }

    for (int v = 1; v <= n; v++) {
        if (visitedV[v]) {
            cout << valV[v] << " ";
        }
    }
    return 0;

}
