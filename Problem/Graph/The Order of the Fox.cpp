//https://dmoj.ca/problem/year2019p7
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 3e5 + 5;
const int K = 450;
const long long M = 1e9 + 7;
long long ans = 0;
int lim;
int pos[N];
bool tab[K][N];
vector<int> graph[N];
vector<pair<int, int>> edges;
vector<int> large;
bool small[N];
bool vis[N];
int e[N];
int wt[N];

struct chash {
    long long operator()(pair<long long, long long> x) const { return x.first* N + x.second; }
};
gp_hash_table<pair<long long, long long>, int, chash> mp;


long long calc(int u, int v, long long w) {
    long long res = 0;
    if (graph[u].size() > graph[v].size()) {
        swap(u, v);
    }
    res += ((((long long)(graph[u].size() - 2) * (long long)(graph[v].size() - 2)) % M) * w) % M;

    if (graph[u].size() + graph[v].size() < graph[u].size() * log2(graph[v].size())) {
        int pu = 0, pv = 0;
        while (pu < graph[u].size() && pv < graph[v].size()) {
            if (graph[u][pu] < graph[v][pv]) {
                pu++;
            } else if (graph[u][pu] > graph[v][pv]) {
                pv++;
            } else {
                res -= w;
                pu++, pv++;
            }
        }

    } else {
        for (int x : graph[u]) {
            if (binary_search(graph[v].begin(), graph[v].end(), x)) {
                res -= w;
            }
        }
    }
    res += w;
    while (res < 0) {
        res += M;
    }
    res %= M;
    return res;
}

long long smalc(int u, int v, long long w, long long wt) {
    long long res = 0;
    res += ((long long)(graph[u].size() - 2) * (long long)(graph[v].size() - 2) * w - w * (wt - 1ll)) % M;
    res %= M;
    while (res < 0) {
        res += M;
    }
    return res;
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        graph[u].push_back(v);
        graph[v].push_back(u);
        edges.push_back(make_pair(u, v));
    }

    lim = sqrt(2 * n);

    for (int i = 0; i < n; i++) {
        sort(graph[i].begin(), graph[i].end());
        if (graph[i].size() >= lim) {
            large.push_back(i);
            pos[i] = large.size() - 1;
            for (int j = 0; j < graph[i].size(); j++) {
                tab[large.size() - 1][graph[i][j]] = true;
            }
        } else {
            small[i] = true;
        }
    }
    for (int j = 0; j < large.size(); j++) {
        int w = large[j];
        int p = pos[w];
        vector<int> ve(n, 0);
        for (int i = 0; i < m; i++) {
            int u = edges[i].first, v = edges[i].second;
            if (graph[u].size() > graph[v].size()) {
                swap(u, v);
            }
            if (u == w || v == w) {
                continue;
            }
            if (vis[u] || vis[v]) {
                continue;
            }
            if (tab[p][u] && tab[p][v]) {
                mp[make_pair(u, v)]++;
                ve[u]++;
                ve[v]++;

            }
        }
        vis[large[j]] = true;
        for (int i = 0; i < n; i++) {
            if (ve[i]) {
                ans += calc(i, w, ve[i]);
                ans %= M;
            }
        }
    }

    for (auto it = mp.begin(); it != mp.end(); ++it) {
        ans += calc((it->first).first, (it->first).second, it->second);
        ans %= M;
    }
    mp.clear();
    for (int i = 0; i < m; i++) {
        int u = edges[i].first, v = edges[i].second;
        if (graph[u].size() > graph[v].size()) {
            swap(u, v);
        }
        if (small[u] && small[v]) {
            int pu = 0, pv = 0;
            while (pu < graph[u].size() && pv < graph[v].size()) {
                if (graph[u][pu] < graph[v][pv]) {
                    pu++;
                } else if (graph[u][pu] > graph[v][pv]) {
                    pv++;
                } else {
                    int w = graph[u][pu];
                    if (small[w] && u != w && v != w) {
                        e[i]++;
                    }
                    wt[i]++;
                    pu++, pv++;
                }
            }
            long long res = 0;
            res += ((long long)(graph[u].size() - 2) * (long long)(graph[v].size() - 2) * e[i] - e[i] * (wt[i] - 1ll)) % M;
            res %= M;
            res += M;
            res %= M;
            ans += res;
            ans %= M;
        }
    }
    cout << ans << endl;
    return 0;
}
