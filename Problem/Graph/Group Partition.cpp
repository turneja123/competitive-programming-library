//https://www.spoj.com/problems/MPART/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2005;
const int INF = 1e9;

struct Edge {
    int v, u;
    int cap, flow = 0;
    Edge(int v, int u, int cap) : v(v), u(u), cap(cap) {}
};

vector<Edge> edges;
vector<vector<int>> adj;
int s, t, m = 0;
vector<int> level, ptr;
queue<int> q;
vector<int> graph[N];

void add_edge(int v, int u, int cap, int rep) {
    edges.emplace_back(v, u, cap);
    edges.emplace_back(u, v, 0);
    if (!rep) {
        adj[v].push_back(m);
        adj[u].push_back(m + 1);
        m += 2;
    }
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

int dfs(int v, int pushed) {
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
        int tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
        if (tr == 0) {
            continue;
        }
        edges[id].flow += tr;
        edges[id ^ 1].flow -= tr;
        return tr;
    }
    return 0;
}

int flow() {
    int f = 0;
    while (true) {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        q.push(s);
        if (!bfs()) {
            break;
        }
        fill(ptr.begin(), ptr.end(), 0);
        while (int pushed = dfs(s, INF)) {
            f += pushed;
        }
    }
    return f;
}
int main() {
    IOS;
    while (1) {
        string line;
        getline(cin, line);
        istringstream iss(line);
        int n, e;
        iss >> n; iss >> e;
        if (n == 0 && e == 0) {
            break;
        }

        s = 0, t = n + e + 1;
        for (int i = 0; i < n; i++) {
            string str;
            getline(cin, str);
            int j = 0;
            while (str[j] != ' ') {
                j++;
            }
            j++;
            while (j < str.size()) {
                while (j < str.size() && str[j] == ' ') {
                    j++;
                }
                if (j >= str.size()) {
                    break;
                }
                string temp = "";
                while (str[j] != ' ' && j != str.size()) {
                    temp += str[j];
                    j++;
                }
                j++;
                int v = stoi(temp);
                graph[i].push_back(v);

            }
        }
        int l = 1, r = n, ans = n;
        int rep = 0;
        adj.resize(n + e + 2);
        while (l <= r) {
            int mid = (l + r) / 2;
            level.resize(n + e + 2);
            ptr.resize(n + e + 2);
            for (int i = 0; i < n; i++) {
                add_edge(s, i + 1, 1, rep);
                for (int v : graph[i]) {
                    add_edge(i + 1, n + 1 + v, 1, rep);
                }

            }
            for (int i = 0; i < e; i++) {
                add_edge(n + 1 + i, t, mid, rep);
            }
            int f = flow();
            if (f == n) {
                r = mid - 1;
                ans = mid;
            } else {
                l = mid + 1;
            }
            level.clear();
            ptr.clear();
            edges.clear();
            rep = 1;
        }
        cout << ans << endl;
        adj.clear();
        for (int i = 0; i < N; i++) {
            graph[i].clear();
        }
        m = 0;

    }
    return 0;
}
