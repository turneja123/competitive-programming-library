//https://www.spoj.com/problems/ADAPANEL/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;
const long long M = 1e9 + 7;

vector<int> adj[N];
vector<int> rev[N];
stack<int> s;

bool vis[N];

int sz = 0;

void fillStack(int v) {
    vis[v] = true;
    for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
        if (!vis[*it]) {
            fillStack(*it);
        }
    }
    s.push(v);
}

void dfs(int v) {
    vis[v] = true;
    sz++;
    for (auto it = rev[v].begin(); it != rev[v].end(); ++it) {
        if (!vis[*it]) {
            dfs(*it);
        }
    }
}

vector<pair<int, int>> g;

long long p[N];

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        rev[b].push_back(a);
    }
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            fillStack(i);
        }
    }
    for (int i = 0; i < n; i++) {
        vis[i] = 0;
    }
    int mx = 0;
    vector<int> w;
    while (!s.empty()) {
        int v = s.top();
        s.pop();
        if (vis[v] == false) {
            sz = 0;
            dfs(v);
            mx = max(mx, sz);
            w.push_back(sz);
        }
    }
    for (int i = 0; i <= mx; i++) {
        g.push_back(make_pair(i * (3 * i - 1) / 2, i % 2 == 1 ? 1 : -1));
        g.push_back(make_pair(i * (3 * i + 1) / 2, i % 2 == 1 ? 1 : -1));
        if (g[g.size() - 1].first > mx + 1) {
            break;
        }
    }

    p[0] = 1, p[1] = 1;
    for (int i = 2; i <= mx; i++) {
        for (int j = 0; j < g.size() && g[j].first <= i; j++) {
            p[i] = (p[i] + p[i - g[j].first] * g[j].second + M) % M;
        }
    }
    long long ans = 1;
    for (int x : w) {
        ans = ans * p[x] % M;
    }
    cout << ans;


    return 0;
}
