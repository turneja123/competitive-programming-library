//https://qoj.ac/contest/2567/problem/14717
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 2e5 + 5;

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

int need[N];
int wildcards[N];
int a[N];
int b[N];
int parent[N];
vector<int> adj[N];
gp_hash_table<int, int, custom_hash> mpa[N];
gp_hash_table<int, int, custom_hash> mpb[N];
int ans[N];

int dsu_find(int p) {
    if (parent[p] == p) {
        return p;
    }
    parent[p] = dsu_find(parent[p]);
    return parent[p];
}

void dsu_merge(int a, int b) {
    if (mpa[a].size() + mpb[a].size() > mpa[b].size() + mpb[b].size()) {
        swap(a, b);
    }
    parent[a] = b;
    wildcards[b] += wildcards[a];

    for (auto [x, d] : mpa[a]) {
        int cta = mpa[b][x], ctb = mpb[b][x];
        if (ctb >= cta) {
            need[b] -= ctb - cta;
        }
        mpa[b][x] += d;
        cta = mpa[b][x], ctb = mpb[b][x];
        if (ctb >= cta) {
            need[b] += ctb - cta;
        }
    }
    for (auto [x, d] : mpb[a]) {
        int cta = mpa[b][x], ctb = mpb[b][x];
        if (ctb >= cta) {
            need[b] -= ctb - cta;
        }
        mpb[b][x] += d;
        cta = mpa[b][x], ctb = mpb[b][x];
        if (ctb >= cta) {
            need[b] += ctb - cta;
        }
    }
    mpa[a].clear();
    mpb[a].clear();
    return;
}

void dfs(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
    for (int v : adj[u]) {
        if (v != p) {
            int a = dsu_find(u), b = dsu_find(v);
            dsu_merge(a, b);
        }
    }
    int a = dsu_find(u);
    if (wildcards[a] >= need[a]) {
        ans[u] = 1;
    } else {
        ans[u] = 0;
    }

    return;
}

int main() {
    IOS;
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++) {
            cin >> b[i];
        }
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            if (b[i] != 0 && a[i] != b[i]) {
                need[i] = 1;
            } else {
                need[i] = 0;
            }

            if (a[i] == 0) {
                wildcards[i]++;
            } else {
                mpa[i][a[i]]++;
            }
            if (b[i] != 0) {
                mpb[i][b[i]]++;
            }

        }
        dfs(0, -1);
        for (int i = 0; i < n; i++) {
            cout << ans[i];
        }
        cout << endl;
        for (int i = 0; i < n; i++) {
            mpa[i].clear();
            mpb[i].clear();
            wildcards[i] = 0;
            need[i] = 0;
            adj[i].clear();
        }

    }

    return 0;
}
