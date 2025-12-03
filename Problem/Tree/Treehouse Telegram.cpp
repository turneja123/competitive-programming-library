//https://www.facebook.com/codingcompetitions/hacker-cup/2025/round-3/scoreboard
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

vector<int> adj[N];
vector<int> divs[N];
ll ans[N];
int parent[N];
int depth[N];
int divcnt[N];

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

gp_hash_table<int, ll, custom_hash> depth_sum[N];
gp_hash_table<int, ll, custom_hash> ct_sum[N];
set<int> st[N];


int dsu_find(int p) {
    if (parent[p] == p) {
        return p;
    }
    parent[p] = dsu_find(parent[p]);
    return parent[p];
}

void dsu_merge(int a, int b, int rem) {
    if (divcnt[a] > divcnt[b]) {
        swap(a, b);
    }
    parent[a] = b;
    for (int x : st[a]) {
        for (int d : divs[x]) {
            auto f = depth_sum[b].find(d);
            if (f == depth_sum[b].end()) {
                continue;
            }
            ll ds = f->second;
            ll cs = ct_sum[b][d];

            ans[d] += ds + cs * depth[x] - 2 * cs * rem;

        }
    }
    for (int x : st[a]) {
        divcnt[b] += divs[x].size();
        st[b].insert(x);
        for (int d : divs[x]) {
            depth_sum[b][d] += depth[x];
            ct_sum[b][d] += 1;
        }
    }

    st[a].clear();
    depth_sum[a].clear();
    ct_sum[a].clear();
    return;
}

void dfs(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }
    st[u].insert(u);
    divcnt[u] += divs[u].size();
    for (int d : divs[u]) {
        depth_sum[u][d] += depth[u];
        ct_sum[u][d] += 1;
    }

    for (int v : adj[u]) {
        if (v != p) {
            int a = dsu_find(u), b = dsu_find(v);
            dsu_merge(a, b, depth[u]);
        }
    }

    return;
}


//mt19937 gen(3);
int main() {
    IOS;
    for (int i = 1; i < N; i++) {
        for (int j = i; j < N; j += i) {
            divs[j].push_back(i);
        }
    }

    freopen("248.in", "r", stdin);
    freopen("248.out", "w", stdout);
    int t;
    cin >> t;
    for (int tt = 1; tt <= t; tt++) {
        int n;
        cin >> n;
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
        for (int i = 2; i <= n; i++) {
            int u, v;
            cin >> u >> v;
            //u = i;
            //v = 1 + gen() % (i - 1);
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        dfs(1, 1);
        for (int i = n; i >= 1; i--) {
            for (int j = 2 * i; j <= n; j += i) {
                ans[i] -= ans[j];
            }
        }
        cout << "Case #" << tt << ": ";
        for (int i = 1; i <= n; i++) {
            cout << ans[i] << " ";
            st[i].clear();
            depth_sum[i].clear();
            ct_sum[i].clear();
            adj[i].clear();
            ans[i] = 0;
            divcnt[i] = 0;
        }
        cout << endl;


    }
    return 0;
}
