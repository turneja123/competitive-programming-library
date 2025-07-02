//https://ocpc2025s.eolymp.space/en/compete/mdpvbmkn7129t7jclok5kktmig/problem/10
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 6e5 + 5;
const long long M = 998244353;

int parent[N];
int sz[N];
int ans[N];
int val[N];

vector<pair<int, int>> segtree[4 * N];
vector<tuple<int, int, int, int>> restore;

long long modPow(long long a, long long y) {
    long long res = 1;
    while(y > 0) {
        if(y % 2 != 0) {
            res = (res * a) % M;
        }
        y /= 2;
        a = (a * a) % M;
    }
    return res;
}

int dsu_find(int a) {
    if (parent[a] == a) {
        return a;
    }
    return dsu_find(parent[a]);
}

void dsu_unite(int a, int b) {
    if (sz[b] > sz[a]) {
        swap(a, b);
    }
    sz[a] += sz[b];
    parent[b] = a;
}

void upd(int l, int r, int lq, int rq, pair<int, int> edge, int node) {
    if (r < lq || l > rq) {
        return;
    }
    if (l >= lq && r <= rq) {
        segtree[node].push_back(edge);
        return;
    }
    int mid = (l + r) / 2;
    upd(l, mid, lq, rq, edge, 2 * node + 1);
    upd(mid + 1, r, lq, rq, edge, 2 * node + 2);
    return;
}

void dfs(int l, int r, int node, int n) {
    int ct = 0;

    for (auto [u, v] : segtree[node]) {
        int x = dsu_find(u), y = dsu_find(v);
        if (x != y) {
            restore.push_back(make_tuple(x, sz[x], y, sz[y]));
            dsu_unite(x, y);
            ct++;
        }
    }
    if (l == r) {
        int x = dsu_find(0), y = dsu_find(n - 1);
        if (x == y) {
            ans[l] = 0;
        } else {
            ans[l] = 1;
        }
    } else {
        int mid = (l + r) / 2;
        dfs(l, mid, 2 * node + 1, n);
        dfs(mid + 1, r, 2 * node + 2, n);
    }
    for (int i = 0; i < ct; i++) {
        auto [u, su, v, sv] = restore.back();
        parent[u] = u;
        parent[v] = v;
        sz[u] = su;
        sz[v] = sv;
        restore.pop_back();
    }
    return;
}

int main() {
    IOS;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        sz[i] = 1;
    }
    set<int> st;
    vector<tuple<int, int, int>> edges;
    for (int i = 0; i < m; i++) {
        int u, v, wt;
        cin >> u >> v >> wt;
        u--, v--;
        edges.push_back(make_tuple(wt, u, v));
        st.insert(wt);
    }
    map<int, int> mp;
    for (auto x : st) {
        val[mp.size()] = x;
        mp[x] = mp.size();
    }
    m = mp.size();
    sort(edges.begin(), edges.end());
    for (auto [wt, u, v] : edges) {
        wt = mp[wt];
        if (wt != 0) {
            upd(0, m - 1, 0, wt - 1, {u, v}, 0);
        }
        if (wt != m - 1) {
            upd(0, m - 1, wt + 1, m - 1, {u, v}, 0);
        }
    }
    dfs(0, m - 1, 0, n);
    long long sum = 0;
    for (int i = 0; i < m; i++) {
        if (ans[i]) {
            sum = (sum + modPow(2, val[i])) % M;
        }
    }
    cout << sum;
    return 0;
}
