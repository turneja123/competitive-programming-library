//https://www.codechef.com/problems/QUERY1206
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;

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

int spf[N];
int ans[N];
bool is_prime[N];
vector<int> divs[N];
vector<int> factors;

vector<int> adj[N];
int parent[N];
gp_hash_table<int, int, custom_hash> mp[N];

void sieve(int n){
    for (int i = 1; i < n; i++) {
        spf[i] = i;
        is_prime[i] = true;
    }
    is_prime[1] = false;
    for (int i = 2; i < n; i++) {
        if (is_prime[i]) {
            for (int j = 2 * i; j < n; j += i) {
                is_prime[j] = false;
                spf[j] = min(spf[j], i);
            }
        }
    }
}

void factor(int n) {
    int last = -1, ct = 0, cnt = 1;
    while (n > 1) {
        int p = spf[n];
        factors.push_back(p);
        n = n / p;
    }
    return;
}

void get_divs(int i, int cur, int n, vector<pair<int, int>> &f) {
    if (i == f.size()) {
        divs[n].push_back(cur);
        return;
    }
    for (int j = 0; j <= f[i].second; j++) {
        get_divs(i + 1, cur, n, f);
        cur *= f[i].first;
    }
    return;
}

int dsu_find(int p) {
    if (parent[p] == p) {
        return p;
    }
    parent[p] = dsu_find(parent[p]);
    return parent[p];
}

void dsu_merge(int a, int b) {
    if (mp[a].size() > mp[b].size()) {
        swap(a, b);
    }
    parent[a] = b;
    for (auto it = mp[a].begin(); it != mp[a].end(); ++it) {
        auto f  = mp[b].find(it->first);
        if (f == mp[b].end()) {
            mp[b][it->first] = it->second;
        } else {
            f->second = min(f->second, it->second);
        }

    }
    return;
}

void dfs(int u, int p) {
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
    for (int d : divs[u + 1]) {
        mp[u][d] = u;
    }
    for (int v : adj[u]) {
        if (v != p) {
            int a = dsu_find(u), b = dsu_find(v);
            dsu_merge(a, b);
        }
    }
    int a = dsu_find(u);
    for (int d : divs[u + 1]) {
        auto it = mp[a].find(d);
        if (it->second < u) {
            ans[u] = max(ans[u], d);
        }
    }

    return;
}

int main() {
    IOS;
    sieve(N);
    for (int n = 1; n < N; n++) {
        factor(n);
        vector<pair<int, int>> f;
        int i = 0, j = 0, m = factors.size(), d = 1;
        while (i < m) {
            int cur = factors[i];
            while (i < m && factors[i] == cur) {
                i++;
            }
            f.push_back(make_pair(factors[j], i - j));
            d *= i - j + 1;
            j = i;
        }

        get_divs(0, 1, n, f);
        factors.clear();
    }
    int t;
    cin >> t;
    while (t--) {
        int root, n;
        cin >> n >> root;
        root--;
        for (int i = 0; i < n - 1; i++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            ans[i] = -1;
        }
        dfs(root, root);
        for (int i = 0; i < n; i++) {
            cout << ans[i] << " ";
        }
        cout << endl;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            mp[i].clear();
        }
    }

    return 0;
}
