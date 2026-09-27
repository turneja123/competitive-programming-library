//https://codeforces.com/contest/1218/problem/D
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1 << 17;
const long long M = 1e9 + 7;
const long long inv2 = (M + 1) / 2;

struct FWHT{
    int P1[N], P2[N];
    void wt(int *a, int n) {
        if (n == 0) {
            return;
        }
        int m = n / 2;
        wt(a, m);
        wt(a + m, m);
        for (int i = 0; i < m; i++) {
            int x = a[i], y = a[i + m];
            a[i] = (x + y) % M, a[i + m] = (x - y + M) % M;
        }
    }
    void iwt(int* a, int n) {
        if (n == 0) {
            return;
        }
        int m = n / 2;
        iwt(a, m);
        iwt(a + m, m);
        for (int i = 0; i < m; i++) {
            int x = a[i], y = a[i + m];
            a[i] = 1LL * (x + y) * inv2 % M, a[i + m] = 1LL * (x - y + M) * inv2 % M;
        }
    }
    vector<int> multiply(int n, vector<int> A, vector<int> B) {
        A.resize(n); B.resize(n);
        for (int i = 0; i < n; i++) {
            P1[i] = A[i];
        }
        for (int i = 0; i < n; i++) {
            P2[i] = B[i];
        }
        wt(P1, n);
        wt(P2, n);
        for (int i = 0; i < n; i++) {
            P1[i] = 1LL * P1[i] * P2[i] % M;
        }
        iwt(P1, n);
        return vector<int>(P1, P1 + n);
    }
}fwht;

vector<tuple<int, int, int>> adj[N];
vector<vector<int>> cyc;

pair<int, int> par[N];
vector<int> edges;
int vis[N];
int depth[N];

int bridges = 0;

void dfs(int u, int e) {
    vis[u] = 1;
    for (auto [v, E, wt] : adj[u]) {
        if (E == e) {
            continue;
        }
        if (!vis[v]) {
            par[v] = {u, E};
            depth[v] = depth[u] + 1;
            dfs(v, E);
        } else if (depth[u] - depth[v] > 1) {
            vector<int> cur;
            cur.push_back(edges[E]);
            int x = u;
            while (x != v) {
                int ed = par[x].second;
                cur.push_back(edges[ed]);
                x = par[x].first;
            }
            for (int val : cur) {
                bridges ^= val;
            }
            cyc.push_back(cur);
        }
    }
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        adj[u].push_back({v, i, wt});
        adj[v].push_back({u, i, wt});
        edges.push_back(wt);
        bridges ^= wt;
    }
    dfs(0, -1);
    vector<int> ans(N);
    vector<int> ans_exist(N);
    ans[bridges] = 1;
    ans_exist[bridges] = 1;
    for (auto c : cyc) {
        vector<int> cur(N);
        vector<int> cur_exist(N);
        int tot = 0;
        for (int x : c) {
            tot ^= x;
        }
        for (int x : c) {
            cur[tot ^ x]++;
            cur_exist[tot ^ x] = 1;
        }
        ans = fwht.multiply(N, ans, cur);
        ans_exist = fwht.multiply(N, ans_exist, cur_exist);
        for (int &x : ans_exist) {
            x = min(x, 1);
        }
    }
    int mn, ways;
    for (int i = 0; i < N; i++) {
        if (ans_exist[i] == 1) {
            mn = i;
            ways = ans[i];
            break;
        }
    }
    cout << mn << " " << ways;

    return 0;
}
