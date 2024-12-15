//https://www.spoj.com/problems/DIVREL/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 405;
const long long INF = 1e18;

struct Edge {
    int v, u;
    long long cap, flow = 0;
    Edge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

vector<int> adj[N];
vector<int> tr_adj[N];

vector<Edge> edges;
int m = 0;
int s, t;
vector<int> level, ptr;
queue<int> q;

void add_edge(int v, int u, long long cap) {
    edges.emplace_back(v, u, cap);
    edges.emplace_back(u, v, 0);
    adj[v].push_back(m);
    adj[u].push_back(m + 1);
    m += 2;
}

bool bfs() {
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int id : adj[v]) {
            if (edges[id].cap - edges[id].flow < 1) {
                continue;
            }
            if (level[edges[id].u] != -1) {
                continue;
            }
            level[edges[id].u] = level[v] + 1;
            q.push(edges[id].u);
        }
    }
    return level[t] != -1;
}

long long dfs(int v, long long pushed) {
    if (pushed == 0) {
        return 0;
    }
    if (v == t) {
        return pushed;
    }
    for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
        int id = adj[v][cid];
        int u = edges[id].u;
        if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1) {
            continue;
        }
        long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
        if (tr == 0) {
            continue;
        }
        edges[id].flow += tr;
        edges[id ^ 1].flow -= tr;
        return tr;
    }
    return 0;
}

long long flow() {
    long long f = 0;
    while (true) {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        q.push(s);
        if (!bfs()) {
            break;
        }
        fill(ptr.begin(), ptr.end(), 0);
        while (long long pushed = dfs(s, INF)) {
            f += pushed;
        }
    }
    return f;
}

int main() {
    IOS;
    int n;
    cin >> n;
    set<int> seen;
    vector<int> a;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        auto it = seen.find(x);
        if (it == seen.end()) {
            a.push_back(x);
            seen.insert(x);
        }
    }
    n = a.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                continue;
            }
            if (a[i] % a[j] == 0) {
                tr_adj[j].push_back(i);
            }
        }
    }
    s = 0, t = 2 * n + 1;
    level.resize(t + 1);
    ptr.resize(t + 1);
    for (int i = 0; i < n; i++) {
        for (int v : tr_adj[i]) {
            add_edge(i + 1, v + n + 1, 1);
        }
    }
    for (int i = 0; i < n; i++) {
        add_edge(s, i + 1, 1);
        add_edge(i + 1 + n, t, 1);
    }
    cout << n - flow() << endl;
    vector<bool> matchedL(n, false), matchedR(n, false);
    for (int i = 0; i < edges.size(); i += 2) {
        int v = edges[i].v;
        int u = edges[i].u;
        if (v >= 1 && v <= n && u >= n + 1 && u <= 2 * n && edges[i].flow == 1) {
            matchedL[v - 1] = true;
            matchedR[u - (n + 1)] = true;
        }
    }
    vector<vector<int>> altL(n), altR(n);
    for (int i = 0; i < (int)edges.size(); i += 2) {
        int v = edges[i].v;
        int u = edges[i].u;
        if (v >= 1 && v <= n && u >= n + 1 && u <= 2 * n) {
            if (edges[i].flow == 1) {
                altR[u - (n + 1)].push_back(v - 1);
            } else {
                altL[v - 1].push_back(u - (n + 1));
            }
        }
    }

    vector<bool> visitedL(n,false), visitedR(n,false);
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (!matchedL[i]) {
            visitedL[i] = true;
            q.push(i);
        }
    }
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (auto r : altL[x]) {
            if (!visitedR[r]) {
                visitedR[r] = true;
                for (auto lf : altR[r]) {
                    if (!visitedL[lf]) {
                        visitedL[lf] = true;
                        q.push(lf);
                    }
                }
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (visitedL[i] && !visitedR[i]) {
            cout << a[i] << " ";
        }
    }
    return 0;
}
