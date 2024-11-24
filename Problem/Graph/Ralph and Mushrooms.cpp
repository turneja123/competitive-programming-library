//https://codeforces.com/problemset/problem/894/E
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e6 + 5;

vector<pair<int, int>> adj[N];
vector<pair<int, long long>> rev[N];
stack<int> s;

bool vis[N];
int parent[N];
int deg[N];
long long pref_arith[N];
long long self[N];
long long sum[N];
long long dp[N];
map<int, int> scc[N];

void fillStack(int v) {
    vis[v] = true;
    for (auto it = adj[v].begin(); it != adj[v].end(); ++it) {
        if (!vis[it->first]) {
            fillStack(it->first);
        }
    }
    s.push(v);
}

void dfs(int v, int j) {
    vis[v] = true;
    parent[v] = j;
    sum[j] += self[v];
    for (auto it = rev[v].begin(); it != rev[v].end(); ++it) {
        if (!vis[it->first]) {
            dfs(it->first, j);
            sum[j] += it->second;
        } else if (parent[it->first] == j) {
            sum[j] += it->second;
        }

    }
}

long long calc(long long n) {
    long long l = 0, r = n, ans = 0;
    while (l <= r) {
        long long mid = (l + r) / 2;
        long long ct = mid * (mid + 1) / 2;
        if (ct <= n) {
            ans = n * (mid + 1) - pref_arith[mid];
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return ans;
}

int main() {
    IOS;
    long long pref = 0, sum_arith = 0;
    for (int i = 1; i < N; i++) {
        pref += i;
        sum_arith += pref;
        pref_arith[i] = sum_arith;
        if (sum_arith > 1e16) {
            break;
        }
    }
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int a, b, wt;
        cin >> a >> b >> wt;
        a--, b--;
        if (a == b) {
            self[a] += calc(wt);
            continue;
        }
        adj[a].push_back(make_pair(b, wt));
        rev[b].push_back(make_pair(a, calc(wt)));
    }
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            fillStack(i);
        }
    }
    for (int i = 0; i < n; i++) {
        vis[i] = 0;
    }
    while (!s.empty()) {
        int v = s.top();
        s.pop();
        if (vis[v] == false) {
            dfs(v, v);
        }
    }
    for (int u = 0; u < n; u++) {
        for (pair<int, int> p : adj[u]) {
            int v = p.first, wt = p.second;
            if (parent[u] != parent[v]) {
                auto it = scc[parent[u]].find(parent[v]);
                if (it == scc[parent[u]].end()) {
                    scc[parent[u]][parent[v]] = wt;
                    deg[parent[v]]++;
                } else {
                    scc[parent[u]][parent[v]] = max(scc[parent[u]][parent[v]], wt);
                }
            }
        }
    }

    priority_queue<int, vector<int>, greater<int>> q;
    for (int i = 0; i < n; i++) {
        if (deg[i] == 0 && parent[i] == i) {
            q.push(i);
        }
    }
    vector<int> sorted;
    while (q.size()) {
        int u = q.top();
        q.pop();
        sorted.push_back(u);
        for (pair<int, int> p : scc[u]) {
            int v = p.first;
            deg[v]--;
            if (deg[v] == 0) {
                q.push(v);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (parent[i] == i) {
            dp[i] = -1;
        }
    }
    int start;
    cin >> start;
    start--;
    long long ans = sum[parent[start]];
    dp[parent[start]] = sum[parent[start]];
    for (int u : sorted) {
        if (dp[u] == -1) {
            continue;
        }
        for (pair<int, int> p : scc[u]) {
            int v = p.first, wt = p.second;
            dp[v] = max(dp[v], dp[u] + sum[v] + wt);
            ans = max(ans, dp[v]);
        }
    }
    cout << ans;


    return 0;
}
