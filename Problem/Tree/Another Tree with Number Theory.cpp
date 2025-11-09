//https://www.codechef.com/problems/ATWNT?tab=statement
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>

using namespace std;
using namespace __gnu_pbds;

#define endl "\n"
#define ll long long
#define IOS ios_base::sync_with_stdio(false); cin.tie(nullptr);

const int N = 1e5 + 5;
const int D = 1e6 + 5;

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

int parent[N];
vector<int> adj[N];
gp_hash_table<int, int, custom_hash> mp[N];

vector<pair<int, int>> queries[N];
int ans[N];

int spf[D];
bool is_prime[D];
int divs[D];
int idx = 0;

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

vector<int> factor(int n) {
    vector<int> factors;
    int last = -1, ct = 0, cnt = 1;
    while (n > 1) {
        int p = spf[n];
        factors.push_back(p);
        n = n / p;
    }
    return factors;
}

void get_divs(int i, int cur, vector<pair<int, int>> &f) {
    if (i == f.size()) {
        divs[idx++] = cur;
        return;
    }
    for (int j = 0; j <= f[i].second; j++) {
        get_divs(i + 1, cur, f);
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

    for (auto [x, d] : mp[a]) {
        mp[b][x] += d;
    }

    mp[a].clear();
    return;
}

void dfs(int u, int p) {
    int s = 0;
    for (int v : adj[u]) {
        if (v != p) {
            s++;
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
    if (s == 0) {
        mp[a][1]++;
    } else if (s > 1) {
        gp_hash_table<int, int, custom_hash> nw;
        for (auto [x, d] : mp[a]) {
            if ((ll)x * s < D) {
                nw[x * s] += d;
            }
        }
        mp[a] = nw;
    }
    for (auto [x, id] : queries[u]) {
        ans[id] = x;
        idx = 0;
        vector<int> factors = factor(x);
        vector<pair<int, int>> f;
        int i = 0, j = 0, m = factors.size();
        while (i < m) {
            int cur = factors[i];
            while (i < m && factors[i] == cur) {
                i++;
            }
            f.push_back(make_pair(factors[j], i - j));
            j = i;
        }

        get_divs(0, 1, f);
        for (int i = 0; i < idx; i++) {
            int d = divs[i];
            auto it = mp[a].find(d);
            if (it != mp[a].end()) {
                ans[id] -= (x / d) * it->second;
            }
        }
    }
    return;
}

int main() {
    IOS;
    sieve(D);
    int n;
    cin >> n;

    for (int i = 1; i < n; i++) {
        int u;
        cin >> u;
        u--;
        adj[u].push_back(i);
        adj[i].push_back(u);
    }
    for (int i = 0; i < n; i++) {
        parent[i] = i;

    }

    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int u, x;
        cin >> u >> x;
        u--;
        queries[u].push_back({x, i});
    }
    dfs(0, -1);
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }



    return 0;
}
