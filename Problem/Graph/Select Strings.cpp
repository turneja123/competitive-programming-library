//https://atcoder.jp/contests/abc354/tasks/abc354_g
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 205;
const long long INF = 1e18;

struct Edge {
    int v, u;
    long long cap, flow = 0;
    Edge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

int a[N];
string st[N];
vector<int> adj[N];
vector<int> tr_adj[N];

vector<Edge> edges;
int m = 0;
int s, t;
vector<int> level, ptr;
queue<int> q;

void LPS(string &pat, int m, int lps[]) {
    int len = 0;
    int i = 1;
    lps[0] = 0;
    while (i < m) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = len;
                i++;
            }
        }
    }
}

int KMP(string &pat, string &txt) {
    int m = pat.length();
    int n = txt.length();
    if (m > n) {
        return 0;
    }
    int lps[m];
    int j = 0;
    LPS(pat, m, lps);
    int i = 0;
    int res = 0;
    while (i < n) {
        if (pat[j] == txt[i]) {
            j++;
            i++;
        }
        if (j == m) {
            j = lps[j - 1];
            res++;
        } else if (i < n && pat[j] != txt[i]) {
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i = i + 1;
            }
        }
    }
    return res;
}

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
    for (int i = 0; i < n; i++) {
        cin >> st[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    map<string, int> mp;
    for (int i = 0; i < n; i++) {
        auto it = mp.find(st[i]);
        if (it == mp.end()) {
            mp[st[i]] = a[i];
        } else {
            mp[st[i]] = max(mp[st[i]], a[i]);
        }
    }
    long long sum = 0;
    vector<pair<string, int>> x;
    for (auto y : mp) {
        x.push_back(y);
        sum += y.second;
    }
    n = x.size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                continue;
            }
            if (KMP(x[j].first, x[i].first)) {
                tr_adj[j].push_back(i);
            }
        }
    }
    s = 0, t = 2 * n + 1;
    level.resize(t + 1);
    ptr.resize(t + 1);
    for (int i = 0; i < n; i++) {
        for (int v : tr_adj[i]) {
            add_edge(i + 1, v + n + 1, INF);
        }
    }
    for (int i = 0; i < n; i++) {
        add_edge(s, i + 1, x[i].second);
        add_edge(i + 1 + n, t, x[i].second);
    }
    cout << sum - flow();


    return 0;
}
