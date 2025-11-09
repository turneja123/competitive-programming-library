//https://qoj.ac/contest/1452/problem/7932
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 40;

int needs[N][N];

int parent[N];
int sz[N];
int skip[N];
int deg[N];

vector<int> adj[N];

int dsu_find(int a) {
    if (parent[a] == a) {
        return a;
    }
    return parent[a] = dsu_find(parent[a]);
}

void dsu_unite(int a, int b) {
    if (sz[b] > sz[a]) {
        swap(a, b);
    }
    sz[a] += sz[b];
    parent[b] = a;
    for (int i = 0; i < N; i++) {
        int u = dsu_find(i);
        if (u != a && u != b) {
            if (needs[b][u]) {
                needs[a][u] = 1;
            }
            if (needs[u][b]) {
                needs[u][a] = 1;
            }
        }
    }
}

int main() {
    IOS;
    int n;
    cin >> n;
    vector<ll> a(n);
    ll or_sum = 0;
    ll and_sum = (1ll << N) - 1;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        or_sum |= a[i];
        and_sum &= a[i];
    }
    for (int j = 0; j < N; j++) {
        ll c = or_sum & (1ll << j);
        ll cc = and_sum & (1ll << j);
        if (!c || cc) {
            skip[j] = 1;
        }

    }

    for (int j = 0; j < N; j++) {
        if (!skip[j]) {
            ll and_sum = (1ll << N) - 1;
            ll or_sum = 0;
            for (int i = 0; i < n; i++) {
                ll c = a[i] & (1ll << j);
                if (c) {
                    and_sum &= a[i];
                } else {
                    or_sum |= a[i];
                }
            }
            for (int k = 0; k < N; k++) {
                if (skip[k] || k == j) {
                    continue;
                }
                ll c = and_sum & (1ll << k);
                if (c) {
                    needs[j][k] = 1; //if it has j it must have k
                }
                c = or_sum & (1ll << k);
                if (!c) {
                    needs[k][j] = 1; //if it doesnt have j it cant have k
                }
            }
        }
    }
    for (int i = 0; i < N; i++) {
        sz[i] = 1;
        parent[i] = i;
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (skip[i] || skip[j]) {
                continue;
            }
            int u = dsu_find(i), v = dsu_find(j);
            if (u == v) {
                continue;
            }
            if (needs[u][v] && needs[v][u]) {
                dsu_unite(u, v);
            }
        }
    }
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (skip[i] || skip[j]) {
                continue;
            }
            int u = dsu_find(i), v = dsu_find(j);
            if (i != u || j != v || u == v) {
                continue;
            }
            if (needs[u][v]) {
                adj[u].push_back(v);
                deg[v]++;
            }
        }
    }
    queue<int> q;
    for (int i = 0; i < N; i++) {
        if (deg[i] == 0 && !skip[i] && dsu_find(i) == i) {
            q.push(i);
        }
    }
    vector<int> sorted;
    while (q.size()) {
        int u = q.front();
        q.pop();
        sorted.push_back(u);
        for (int v : adj[u]) {
            deg[v]--;
            if (deg[v] == 0) {
                q.push(v);
            }
        }
    }
    if (sorted.size() == 0) {
        cout << 1;
        return 0;
    } else if (sorted.size() == 1) {
        cout << 2;
        return 0;
    }
    int m = sorted.size();
    vector<int> pos(N);
    for (int i = 0; i < m; i++) {
        pos[sorted[i]] = i;
    }


    vector<ll> poset(m);
    for (int i = m - 1; i >= 0; i--) {
        poset[i] |= 1ll << i;
        for (int j : adj[sorted[i]]) {
            poset[i] |= poset[pos[j]];
        }
    }
    vector<ll> dp(1 << (m - m / 2), 0);
    for (int i = 0; i < 1 << (m - m / 2); i++) {
        int can = 1; ll needs = 0;
        for (int j = m / 2; j < m; j++) {
            int c = i & (1 << (j - m / 2));
            if (c) {
                needs |= poset[j];
            }
        }
        needs >>= m / 2;
        int c = i | needs;
        if (i == c) {
            dp[i] = 1;
        } else {
            dp[i] = 0;
        }
    }
    for (int i = 0; i < m - m / 2; i++) {
        for (int j = 0; j < 1 << (m - m / 2); j++) {
            int c = j & (1 << i);
            if (!c) {
                dp[j] += dp[j ^ (1 << i)];
            }
        }
    }

    ll ans = 0;
    for (int i = 0; i < 1 << (m / 2); i++) {
        ll needs = 0;
        for (int j = 0; j < m / 2; j++) {
            int c = i & (1 << j);
            if (c) {
                needs |= poset[j];
            }
        }
        int can = 1;
        for (int j = 0; j < m / 2; j++) {
            int c = i & (1 << j);
            ll ca = needs & (1ll << j);
            if (!c && ca) {
                can = 0;
            }
        }
        if (!can) {
            continue;
        }
        needs >>= m / 2;
        ans += dp[needs];
    }
    cout << ans;



    return 0;
}
